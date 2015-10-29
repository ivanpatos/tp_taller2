package com.fiuba.taller2.UdriveClient.task;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Environment;
import android.preference.PreferenceManager;
import android.util.Base64;
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

public class GetFileAsyncTask extends AsyncTask<String, String, JSONObject> {

    private Activity activity;
    private ProgressDialog dialog;
    private String errorMessage = "";

    public GetFileAsyncTask(Activity activity) {
        this.activity = activity;
    }

    @Override
    protected JSONObject doInBackground(String... params) {
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(activity);
        PropertyManager propertyManager = new PropertyManager(activity);
        String serverUrl = sharedPreferences.getString("serverUrl", propertyManager.getProperty("url.server"));
        String folderUrl = propertyManager.getProperty("url.file");
        String idFile = params[0];
        String version = params[1];

        JSONObject response = null;
        RestConnectionDTO restConnectionDTO = new RestConnectionDTO();
        String username = sharedPreferences.getString("username", "null");
        String token = sharedPreferences.getString("token", "null");
        try {
            URL url = new URL(serverUrl + folderUrl + "/" + idFile + "?version=" + version);
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
            FileResponseDTO fileResponseDTO = gson.fromJson(jsonObject.get("data").toString(), FileResponseDTO.class);

            File dir = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS);
            if (!dir.exists()) {
               dir.mkdirs();
            }

            String filename = fileResponseDTO.getName();
            String extension = fileResponseDTO.getExtension();

            File file = new File(dir.getAbsolutePath(), filename + "." + extension);
            if (!file.exists()) {
               file.createNewFile();
            }
            FileOutputStream fop = new FileOutputStream(file);

            String fileBase64 = fileResponseDTO.getData();
            byte[] contentInBytes = Base64.decode(fileBase64, Base64.DEFAULT);
            fop.write(contentInBytes);
            fop.flush();
            fop.close();

            Intent intent = new Intent(Intent.ACTION_VIEW);
            String type = "*/*";
            if(extension.equals("pdf")){
                type = "application/pdf";
            }
            if(extension.equals("jpg") || extension.equals("png") || extension.equals("jpeg") ){
                type = "image/*";

            }
            intent.setDataAndType(Uri.fromFile(file), type);
            activity.startActivity(intent);


        } catch (JSONException | IOException e) {
            Toast.makeText(activity, activity.getString(R.string.error_open_file), Toast.LENGTH_SHORT).show();
            e.printStackTrace();
        }
    }

}

