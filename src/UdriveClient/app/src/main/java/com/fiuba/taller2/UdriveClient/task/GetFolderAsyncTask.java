package com.fiuba.taller2.UdriveClient.task;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.Toast;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.activity.HomeActivity;
import com.fiuba.taller2.UdriveClient.dto.ConnectionDTO;
import com.fiuba.taller2.UdriveClient.dto.DocumentChildDTO;
import com.fiuba.taller2.UdriveClient.dto.FolderDTO;
import com.fiuba.taller2.UdriveClient.exception.ConnectionException;
import com.fiuba.taller2.UdriveClient.util.DocumentAdapter;
import com.fiuba.taller2.UdriveClient.util.PropertyManager;
import com.google.gson.Gson;

import org.json.JSONException;
import org.json.JSONObject;

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
        PropertyManager propertyManager = new PropertyManager(activity);
        String serverUrl = propertyManager.getProperty("url.server");
        String folderUrl = propertyManager.getProperty("url.folder");
        String idFolder = params[0];
        JSONObject response = null;
        ConnectionDTO connectionDTO = new ConnectionDTO();
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(activity);
        String username = sharedPreferences.getString("username", "null");
        String token = sharedPreferences.getString("token", "null");
        try {
            URL url = new URL(serverUrl + folderUrl + "/" + idFolder);
            connectionDTO.setUrl(url);
            connectionDTO.setRequestMethod("GET");
            connectionDTO.addAttributeHeader("Content-Type", "application/json; charset=UTF-8");
            connectionDTO.addAttributeHeader("username", username);
            connectionDTO.addAttributeHeader("token", token);
            RestConnection restConnection = new RestConnection();
            response = restConnection.execute(connectionDTO);
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
        dialog.setMessage(activity.getString(R.string.login_waiting));
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
            FolderDTO folderDTO = gson.fromJson(jsonObject.get("data").toString(), FolderDTO.class);
            refreshViewActivity(folderDTO);

        } catch (JSONException e) {
            e.printStackTrace();
            }
    }


    private void refreshViewActivity(FolderDTO folderDTO) {
        activity.setTitle(folderDTO.getName());

        final ArrayList<DocumentChildDTO> documentChildDTOs = folderDTO.getChildren();

        final DocumentAdapter adapter = new DocumentAdapter(activity,
                R.layout.listview_item_document, documentChildDTOs);

        ListView documentList = (ListView) activity.findViewById(R.id.documentList);

        documentList.setAdapter(adapter);
        documentList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            public void onItemClick(AdapterView<?> arg0, View v, int position, long arg3) {
                DocumentChildDTO documentChildSelected = documentChildDTOs.get(position);
                if (documentChildSelected.getType().equals("folder")) {
                    String idFolderSelected = documentChildSelected.getId();
                    Intent intent = new Intent(activity, HomeActivity.class);
                    intent.putExtra("idFolder", idFolderSelected);
                    activity.startActivity(intent);
                    activity.overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);
                } else {
                    Toast.makeText(activity, "Abro el archivo", Toast.LENGTH_SHORT).show();
                }
            }
        });


    }

}

