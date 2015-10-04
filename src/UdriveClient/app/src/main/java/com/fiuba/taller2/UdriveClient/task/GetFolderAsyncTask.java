/*package com.fiuba.taller2.UdriveClient.task;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.preference.PreferenceManager;
import android.widget.Toast;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.activity.HomeActivity;
import com.fiuba.taller2.UdriveClient.dto.UserDTO;
import com.fiuba.taller2.UdriveClient.exception.ConnectionException;
import com.fiuba.taller2.UdriveClient.util.PropertyManager;
import com.google.gson.Gson;

import org.json.JSONException;
import org.json.JSONObject;

import java.net.MalformedURLException;
import java.net.URL;

public class GetFolderAsyncTask extends AsyncTask<String, String, JSONObject> {

    private Activity activity;
    private ProgressDialog dialog;
    private String errorMessage = "";

    public GetFolderAsyncTask(Activity activity) {
        this.activity = activity;
    }

   /* Bundle extras = getIntent().getExtras();
    DocumentDTO documentDTO = null;
    documents = getDocuments();
    if (extras != null) {
        documentDTO = (DocumentDTO) extras.get("document");
    } else {

        documentDTO = documents.get("F0");
    }
    setTitle(documentDTO.getName());

    final ArrayList<DocumentChildDTO> documentChildDTOs = documentDTO.getChildren();

    final DocumentAdapter adapter = new DocumentAdapter(this,
            R.layout.listview_item_document, documentChildDTOs);

    ListView documentList = (ListView) findViewById(R.id.documentList);

    documentList.setAdapter(adapter);
    documentList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
        public void onItemClick(AdapterView<?> arg0, View v, int position, long arg3) {
            DocumentChildDTO documentChildSelected = documentChildDTOs.get(position);
            if(documentChildSelected.getType().equals("folder")){
                DocumentDTO currentDocument = documents.get(documentChildSelected.getId());
                Intent intent = new Intent(getApplicationContext(), HomeActivity.class);
                intent.putExtra("document", currentDocument);
                startActivity(intent);
                overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);
            }else{
                Toast.makeText(getApplicationContext(), "Abro el archivo", Toast.LENGTH_SHORT).show();
            }
        }
    });


    @Override
    protected JSONObject doInBackground(String... params) {
        PropertyManager propertyManager = new PropertyManager(activity);
        String serverUrl = propertyManager.getProperty("url.server");
        String folderUrl = propertyManager.getProperty("url.folder");
        String urlString = serverUrl + folderUrl;
        String idFolder = params[0];

        JSONObject response = null;
        try {
            URL url = new URL(urlString);
            RestConnection restConnection = new RestConnection();
            response = restConnection.get(url, json, header);
        } catch (ConnectionException ex) {
            ex.printStackTrace();
            errorMessage = context.getString(R.string.connection_error);
        } catch (MalformedURLException ex) {
            errorMessage = context.getString(R.string.malformed_url_error);
            ex.printStackTrace();
        }
        return response;
    }

    @Override
    protected void onPreExecute() {
        dialog = new ProgressDialog(activity);
        dialog.setMessage(context.getString(R.string.login_waiting));
        dialog.setCancelable(false);
        dialog.show();
    }

    @Override
    protected void onPostExecute(JSONObject jsonObject) {
        dialog.dismiss();
        if (!errorMessage.isEmpty()) {
            Toast.makeText(context, errorMessage, Toast.LENGTH_SHORT).show();
            return;
        }
        try {
            String result = (String) jsonObject.get("result");
            if (result.equals("ERROR")) {

                Integer errorCode = (Integer) jsonObject.get("errorCode");
                switch (errorCode) {
                    case 2:
                        Toast.makeText(context, context.getString(R.string.login_error_bad_credentials), Toast.LENGTH_SHORT).show();
                        break;
                    case 7:
                        Toast.makeText(context, context.getString(R.string.login_error_bad_credentials), Toast.LENGTH_SHORT).show();
                        break;
                    default:
                        Toast.makeText(context, context.getString(R.string.login_error), Toast.LENGTH_SHORT).show();
                        break;
                }
                return;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        try {
            Gson gson = new Gson();
            UserDTO userDTO = gson.fromJson(jsonObject.get("data").toString(), UserDTO.class);
            SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(context);
            SharedPreferences.Editor editor = sharedPreferences.edit();
            editor.putString("name", userDTO.getName());
            editor.putString("username", userDTO.getUsername());
            editor.putString("mail", userDTO.getMail());
            editor.putString("token", userDTO.getToken());
            editor.apply();
        } catch (JSONException e) {
            e.printStackTrace();
        }
        Intent intent = new Intent(activity, HomeActivity.class);
        activity.startActivity(intent);
    }








}

*/