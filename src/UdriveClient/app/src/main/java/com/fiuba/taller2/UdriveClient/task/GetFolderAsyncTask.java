package com.fiuba.taller2.UdriveClient.task;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.preference.PreferenceManager;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.cocosw.bottomsheet.BottomSheet;
import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.activity.HomeActivity;
import com.fiuba.taller2.UdriveClient.dto.DocumentChildResponseDTO;
import com.fiuba.taller2.UdriveClient.dto.FolderRequestDTO;
import com.fiuba.taller2.UdriveClient.dto.FolderResponseDTO;
import com.fiuba.taller2.UdriveClient.dto.RestConnectionDTO;
import com.fiuba.taller2.UdriveClient.exception.ConnectionException;
import com.fiuba.taller2.UdriveClient.util.DocumentAdapter;
import com.fiuba.taller2.UdriveClient.util.PropertyManager;
import com.google.gson.Gson;

import org.json.JSONException;
import org.json.JSONObject;
import org.w3c.dom.Text;

import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;

public class GetFolderAsyncTask extends AsyncTask<String, String, JSONObject> {

    private Activity activity;
    private ProgressDialog dialog;
    private String errorMessage = "";

    public GetFolderAsyncTask(Activity activity) {
        this.activity = activity;
    }

    @Override
    protected JSONObject doInBackground(String... params) {
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(activity);
        PropertyManager propertyManager = new PropertyManager(activity);
        String serverUrl = sharedPreferences.getString("serverUrl", propertyManager.getProperty("url.server"));
        String folderUrl = propertyManager.getProperty("url.folder");
        String idFolder = params[0];
        JSONObject response = null;
        RestConnectionDTO restConnectionDTO = new RestConnectionDTO();
        String username = sharedPreferences.getString("username", "null");
        String token = sharedPreferences.getString("token", "null");
        try {
            URL url = new URL(serverUrl + folderUrl + "/" + idFolder);
            restConnectionDTO.setUrl(url);
            restConnectionDTO.setRequestMethod("GET");
            restConnectionDTO.addAttributeHeader("Content-Type", "application/json; charset=UTF-8");
            restConnectionDTO.addAttributeHeader("username", username);
            restConnectionDTO.addAttributeHeader("token", token);
            RestConnection restConnection = new RestConnection();
            response = restConnection.execute(restConnectionDTO);
        } catch (ConnectionException ex) {
            ex.printStackTrace();
            errorMessage = activity.getString(R.string.connection_error);
        } catch (MalformedURLException ex) {
            errorMessage = activity.getString(R.string.malformed_url_error);
            ex.printStackTrace();
        }
        return response;
    }

    @Override
    protected void onPreExecute() {
        dialog = new ProgressDialog(activity);
        dialog.setMessage(activity.getString(R.string.loading));
        dialog.setCancelable(false);
        dialog.show();
    }

    @Override
    protected void onPostExecute(JSONObject jsonObject) {
        dialog.dismiss();
        if (!errorMessage.isEmpty()) {
            Toast.makeText(activity, errorMessage, Toast.LENGTH_SHORT).show();
            return;
        }


        try {
            String result = (String) jsonObject.get("result");
            if (result.equals("ERROR")) {
                Toast.makeText(activity, activity.getString(R.string.connection_error), Toast.LENGTH_SHORT).show();
                return;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        try {
            Gson gson = new Gson();
            FolderResponseDTO folderResponseDTO = gson.fromJson(jsonObject.get("data").toString(), FolderResponseDTO.class);
            increaseCycleLevel();
            refreshViewActivity(folderResponseDTO);

        } catch (JSONException e) {
            e.printStackTrace();
            }
    }


    private void refreshViewActivity(FolderResponseDTO folderResponseDTO) {
        activity.setTitle(folderResponseDTO.getName());

        final ArrayList<DocumentChildResponseDTO> documentChildResponseDTOs = folderResponseDTO.getChildren();

        final DocumentAdapter adapter = new DocumentAdapter(activity,
                R.layout.listview_item_document, documentChildResponseDTOs);

        final ListView documentList = (ListView) activity.findViewById(R.id.documentList);

        documentList.setAdapter(adapter);
        documentList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            public void onItemClick(AdapterView<?> arg0, View v, int position, long arg3) {
                DocumentChildResponseDTO documentChildSelected = documentChildResponseDTOs.get(position);
                if (documentChildSelected.getType().equals("folder")) {
                    String idFolderSelected = documentChildSelected.getId();
                    Intent intent = new Intent(activity, HomeActivity.class);
                    intent.putExtra("idFolder", idFolderSelected);
                    activity.startActivity(intent);
                    activity.overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);
                } else {
                    String idFileSelected = documentChildSelected.getId();
                    GetFileAsyncTask getFileAsyncTask = new GetFileAsyncTask(activity);

                    // Cuando implementemos la version, no va hardcodeada
                    String version = "1";
                    getFileAsyncTask.execute(idFileSelected, version);
                }
            }
        });
        documentList.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            public boolean onItemLongClick(AdapterView<?> arg0, View v, int position, long arg3) {
                final DocumentChildResponseDTO documentChildSelected = documentChildResponseDTOs.get(position);
                if(documentChildSelected.getType().equals("file")){
                    new BottomSheet.Builder(activity).title(R.string.home_menu_bottom_title).sheet(R.menu.menu_actions_item_file).listener(new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            switch (which) {
                                case R.id.view_metadata:
                                    GetMetadataFileAsyncTask getMetadataFileAsyncTask = new GetMetadataFileAsyncTask(activity);
                                    getMetadataFileAsyncTask.execute(documentChildSelected.getId());
                                case R.id.modify_name:
                                    Toast.makeText(activity, "Modificar nombre", Toast.LENGTH_SHORT).show();
                                    break;
                                case R.id.invite_users:
                                    Toast.makeText(activity,  "Invitar usuarios", Toast.LENGTH_SHORT).show();
                                    break;
                                case R.id.delete:
                                    DeleteFileAsyncTask deleteFileAsyncTask = new DeleteFileAsyncTask(activity, documentChildSelected);
                                    deleteFileAsyncTask.execute();
                                    break;
                            }
                        }
                    }).show();
                }else{
                    new BottomSheet.Builder(activity).title(R.string.home_menu_bottom_title).sheet(R.menu.menu_actions_item_folder).listener(new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            switch (which) {

                                case R.id.modify_name:
                                    Toast.makeText(activity, "Modificar nombre", Toast.LENGTH_SHORT).show();
                                    break;
                                case R.id.invite_users:
                                    Toast.makeText(activity, "Invitar usuarios", Toast.LENGTH_SHORT).show();
                                    break;
                                case R.id.delete:
                                    DeleteFolderAsyncTask deleteFolderAsyncTask = new DeleteFolderAsyncTask(activity, documentChildSelected);
                                    deleteFolderAsyncTask.execute();
                                    break;
                            }
                        }
                    }).show();
                }
                return true;
            }
        });


    }

    private void increaseCycleLevel(){
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(activity);
        int cycleLevel = sharedPreferences.getInt("homeCycleLevel", 0) + 1;
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putInt("homeCycleLevel", cycleLevel);
        editor.apply();
    }
}

