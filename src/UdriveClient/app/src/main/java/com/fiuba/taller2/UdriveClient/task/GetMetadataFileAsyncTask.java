package com.fiuba.taller2.UdriveClient.task;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Environment;
import android.preference.PreferenceManager;
import android.util.Base64;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.FileResponseDTO;
import com.fiuba.taller2.UdriveClient.dto.RestConnectionDTO;
import com.fiuba.taller2.UdriveClient.exception.ConnectionException;
import com.fiuba.taller2.UdriveClient.util.PropertyManager;
import com.google.gson.Gson;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;

public class GetMetadataFileAsyncTask extends AsyncTask<String, String, JSONObject> {

    private Activity activity;
    private ProgressDialog dialog;
    private String errorMessage = "";

    public GetMetadataFileAsyncTask(Activity activity) {
        this.activity = activity;
    }

    @Override
    protected JSONObject doInBackground(String... params) {
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(activity);
        PropertyManager propertyManager = new PropertyManager(activity);
        String serverUrl = sharedPreferences.getString("serverUrl", propertyManager.getProperty("url.server"));
        String fileUrl = propertyManager.getProperty("url.file");
        String idFile = params[0];
        JSONObject response = null;
        RestConnectionDTO restConnectionDTO = new RestConnectionDTO();
        String username = sharedPreferences.getString("username", "null");
        String token = sharedPreferences.getString("token", "null");
        try {
            URL url = new URL(serverUrl + fileUrl + "/" + idFile);
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

            Gson gson = new Gson();
            Log.d("jsonObjetc", jsonObject.get("data").toString());
            FileResponseDTO fileResponseDTO = gson.fromJson(jsonObject.get("data").toString(), FileResponseDTO.class);

            LayoutInflater li = LayoutInflater.from(activity);
            View promptsView = li.inflate(R.layout.dialog_view_metadata, null);

            AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
                    activity).setTitle(R.string.view_metadata_title);
            TextView nameText = (TextView) promptsView
                    .findViewById(R.id.metadataNameValue);
            nameText.setText(fileResponseDTO.getName() + "." + fileResponseDTO.getExtension());

            TextView ownText = (TextView) promptsView
                    .findViewById(R.id.metadataOwnValue);
            ownText.setText(fileResponseDTO.getOwner());

            String textLastModified = fileResponseDTO.getLastModified();
            if(textLastModified.isEmpty()){
                textLastModified = "-";
            }
            TextView lastModifiedText = (TextView) promptsView
                    .findViewById(R.id.metadataLastModifiedValue);
            lastModifiedText.setText(textLastModified);


            String textLastUser= fileResponseDTO.getLastUser();
            if(textLastUser.isEmpty()){
                textLastUser = "-";
            }
            TextView lastUserText = (TextView) promptsView
                    .findViewById(R.id.metadataLastUserValue);
            lastUserText.setText(textLastUser);

            TextView versionText = (TextView) promptsView
                    .findViewById(R.id.metadataVersionValue);
            versionText.setText(fileResponseDTO.getVersion());

            String textLabels = "-";
            if(!fileResponseDTO.getLabels().isEmpty()){
                textLabels = fileResponseDTO.getLabels().toString();
            }
            TextView labelsText = (TextView) promptsView
                    .findViewById(R.id.metadataLabelsValue);
            labelsText.setText(textLabels);

            String textPermissions= "-";
            if(!fileResponseDTO.getUsers().isEmpty()){
                textPermissions = fileResponseDTO.getUsers().toString();
            }
            TextView permissionsText = (TextView) promptsView
                    .findViewById(R.id.metadataPermissionsValue);
            permissionsText.setText(textPermissions);

            alertDialogBuilder.setView(promptsView);
            alertDialogBuilder
                    .setCancelable(false)
                    .setNegativeButton(R.string.close,
                            new DialogInterface.OnClickListener() {
                                public void onClick(DialogInterface dialog, int id) {
                                    dialog.cancel();
                                }
                            });
            AlertDialog alertDialog = alertDialogBuilder.create();
            alertDialog.show();


        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

}

