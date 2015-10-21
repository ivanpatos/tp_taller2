package com.fiuba.taller2.UdriveClient.task;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.preference.PreferenceManager;
import android.widget.Toast;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.activity.HomeActivity;
import com.fiuba.taller2.UdriveClient.dto.RestConnectionDTO;
import com.fiuba.taller2.UdriveClient.dto.FolderResponseDTO;
import com.fiuba.taller2.UdriveClient.exception.ConnectionException;
import com.fiuba.taller2.UdriveClient.util.PropertyManager;
import com.google.gson.Gson;

import org.json.JSONException;
import org.json.JSONObject;

import java.net.MalformedURLException;
import java.net.URL;

public class AddFolderAsyncTask extends AsyncTask<String, String, JSONObject> {

    private Activity activity;
    private ProgressDialog dialog;
    private String errorMessage = "";

    public AddFolderAsyncTask(Activity activity) {
        this.activity = activity;
    }

    @Override
    protected JSONObject doInBackground(String... params) {
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(activity);
        PropertyManager propertyManager = new PropertyManager(activity);
        String serverUrl = sharedPreferences.getString("serverUrl", propertyManager.getProperty("url.server"));
        String folderUrl = propertyManager.getProperty("url.folder");
        JSONObject response = null;
        RestConnectionDTO restConnectionDTO = new RestConnectionDTO();
        String username = sharedPreferences.getString("username", "null");
        String token = sharedPreferences.getString("token", "null");
        String json = params[0];
        try {
            URL url = new URL(serverUrl + folderUrl);
            restConnectionDTO.setUrl(url);
            restConnectionDTO.setRequestMethod("POST");
            restConnectionDTO.setJson(json);
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
        dialog.setMessage(activity.getString(R.string.creating_folder));
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
                Integer errorCode =  (Integer) jsonObject.get("errorCode");
                switch (errorCode){
                    case 9:
                        Toast.makeText(activity, activity.getString(R.string.folder_already_exists), Toast.LENGTH_SHORT).show();
                        break;
                    default:
                        Toast.makeText(activity, activity.getString(R.string.connection_error), Toast.LENGTH_SHORT).show();
                        break;
                }
                return;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        try {
            Gson gson = new Gson();
            FolderResponseDTO folderResponseDTO = gson.fromJson(jsonObject.get("data").toString(), FolderResponseDTO.class);
            String idFolderSelected = folderResponseDTO.getId();
            Intent intent = new Intent(activity, HomeActivity.class);
            intent.putExtra("idFolder", idFolderSelected);
            activity.startActivity(intent);
            activity.overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);


        } catch (JSONException e) {
            e.printStackTrace();
            }
    }

}

