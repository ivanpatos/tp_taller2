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
import com.fiuba.taller2.UdriveClient.dto.ConnectionDTO;
import com.fiuba.taller2.UdriveClient.dto.UserDTO;
import com.fiuba.taller2.UdriveClient.exception.ConnectionException;
import com.fiuba.taller2.UdriveClient.util.PropertyManager;
import com.google.gson.Gson;

import org.json.JSONException;
import org.json.JSONObject;

import java.net.MalformedURLException;
import java.net.URL;

public class LoginAsyncTask extends AsyncTask<String, String, JSONObject> {

    private Activity activity;
    private ProgressDialog dialog;
    private String errorMessage = "";

    public LoginAsyncTask(Activity activity) {
        this.activity = activity;
    }

    @Override
    protected JSONObject doInBackground(String... params) {
        PropertyManager propertyManager = new PropertyManager(activity);
        String serverUrl = propertyManager.getProperty("url.server");
        String loginUrl = propertyManager.getProperty("url.login");
        JSONObject response = null;
        ConnectionDTO connectionDTO = new ConnectionDTO();
        try{
            URL url = new URL(serverUrl + loginUrl);
            String json = params[0];
            connectionDTO.setUrl(url);
            connectionDTO.setJson(json);
            connectionDTO.setRequestMethod("POST");
            connectionDTO.addAttributeHeader("Content-Type","application/json; charset=UTF-8");
            RestConnection restConnection = new RestConnection();
            response = restConnection.execute(connectionDTO);
        }catch (MalformedURLException ex){
            ex.printStackTrace();
            errorMessage = activity.getString(R.string.malformed_url_error);
        }
        catch (ConnectionException ex){
            ex.printStackTrace();
            errorMessage = activity.getString(R.string.connection_error);
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
        if(!errorMessage.isEmpty()){
            Toast.makeText(activity, errorMessage, Toast.LENGTH_SHORT).show();
            return;
        }
        try {
            String result = (String) jsonObject.get("result");
            if (result.equals("ERROR")) {

                Integer errorCode =  (Integer) jsonObject.get("errorCode");
                switch (errorCode){
                    case 2:
                        Toast.makeText(activity, activity.getString(R.string.login_error_bad_credentials), Toast.LENGTH_SHORT).show();
                        break;
                    case 7:
                        Toast.makeText(activity, activity.getString(R.string.login_error_bad_credentials), Toast.LENGTH_SHORT).show();
                        break;
                    default:
                        Toast.makeText(activity, activity.getString(R.string.login_error), Toast.LENGTH_SHORT).show();
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
            SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(activity);
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

