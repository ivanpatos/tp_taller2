package com.fiuba.taller2.UdriveClient.task;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.preference.PreferenceManager;
import android.widget.ListView;
import android.widget.Toast;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.DocumentChildResponseDTO;
import com.fiuba.taller2.UdriveClient.dto.FileResponseDTO;
import com.fiuba.taller2.UdriveClient.dto.FolderResponseDTO;
import com.fiuba.taller2.UdriveClient.dto.RestConnectionDTO;
import com.fiuba.taller2.UdriveClient.exception.ConnectionException;
import com.fiuba.taller2.UdriveClient.util.DocumentAdapter;
import com.fiuba.taller2.UdriveClient.util.PropertyManager;
import com.google.gson.Gson;

import org.json.JSONException;
import org.json.JSONObject;

import java.net.MalformedURLException;
import java.net.URL;

public class UpdateFileAsyncTask extends AsyncTask<String, String, JSONObject> {

    private Activity activity;
    private ProgressDialog dialog;
    private String errorMessage = "";
    private DocumentChildResponseDTO documentUpdate;

    public UpdateFileAsyncTask(Activity activity, DocumentChildResponseDTO documentUpdate) {
        this.activity = activity;
        this.documentUpdate = documentUpdate;

    }

    @Override
    protected JSONObject doInBackground(String... params) {

        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(activity);
        PropertyManager propertyManager = new PropertyManager(activity);
        String serverUrl = sharedPreferences.getString("serverUrl", propertyManager.getProperty("url.server"));
        String fileUrl = propertyManager.getProperty("url.file");
        JSONObject response = null;
        RestConnectionDTO restConnectionDTO = new RestConnectionDTO();
        String username = sharedPreferences.getString("username", "null");
        String token = sharedPreferences.getString("token", "null");
        String json = params[0];
        String idFolder = params[1];

        try {
            URL url = new URL(serverUrl + fileUrl + "/" + idFolder);
            restConnectionDTO.setUrl(url);
            restConnectionDTO.setRequestMethod("PUT");
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
            FileResponseDTO fileResponseDTO = gson.fromJson(jsonObject.get("data").toString(), FileResponseDTO.class);
            ListView documentList = (ListView) activity.findViewById(R.id.documentList);
            DocumentAdapter adapter = (DocumentAdapter) documentList.getAdapter();
            documentUpdate.setName(fileResponseDTO.getName());
            adapter.notifyDataSetChanged();
        } catch (JSONException e) {
            e.printStackTrace();
            }
    }

}

