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
import com.fiuba.taller2.UdriveClient.dto.UserRequestDTO;
import com.fiuba.taller2.UdriveClient.exception.ConnectionException;
import com.fiuba.taller2.UdriveClient.util.PropertyManager;
import com.google.gson.Gson;

import org.json.JSONException;
import org.json.JSONObject;

import java.net.MalformedURLException;
import java.net.URL;

public class RegisterAsyncTask extends AsyncTask<String, String, JSONObject> {

    private Activity activity;
    private ProgressDialog dialog;
    private String errorMessage = "";

    public RegisterAsyncTask(Activity activity) {
        this.activity = activity;
    }

    @Override
    protected JSONObject doInBackground(String... params) {
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(activity);
        PropertyManager propertyManager = new PropertyManager(activity);
        String serverUrl = sharedPreferences.getString("serverUrl", propertyManager.getProperty("url.server"));
        String userUrl = propertyManager.getProperty("url.user");
        JSONObject response = null;
        RestConnectionDTO restConnectionDTO = new RestConnectionDTO();
        try{
            URL url = new URL(serverUrl + userUrl);
            String json = params[0];
            restConnectionDTO.setUrl(url);
            restConnectionDTO.setJson(json);
            restConnectionDTO.setRequestMethod("POST");
            restConnectionDTO.addAttributeHeader("Content-Type","application/json; charset=UTF-8");
            RestConnection restConnection = new RestConnection();
            response = restConnection.execute(restConnectionDTO);
        }
        catch (MalformedURLException ex){
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
        dialog.setMessage(activity.getString(R.string.register_waiting));
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
                    case 3:
                        Toast.makeText(activity, activity.getString(R.string.register_error_username_exists), Toast.LENGTH_SHORT).show();
                        break;
                    default:
                        Toast.makeText(activity, activity.getString(R.string.register_error), Toast.LENGTH_SHORT).show();
                        break;
                }
                return;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
      try {
            Gson gson = new Gson();
            UserRequestDTO userRequestDTO = gson.fromJson(jsonObject.get("data").toString(), UserRequestDTO.class);
            SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(activity);
            SharedPreferences.Editor editor = sharedPreferences.edit();
            editor.putString("name", userRequestDTO.getName());
            editor.putString("username", userRequestDTO.getUsername());
            editor.putString("mail", userRequestDTO.getMail());
            editor.putString("profilePicture", userRequestDTO.getProfilePicture());
            editor.putString("token", userRequestDTO.getToken());
            editor.putBoolean("logged", true);
            editor.remove("homeCycleLevel");
            editor.apply();
        } catch (JSONException e) {
            e.printStackTrace();
        }

        Intent intent = new Intent(activity, HomeActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK);
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        activity.startActivity(intent);
        Toast.makeText(activity, activity.getString(R.string.register_success), Toast.LENGTH_SHORT).show();
    }
}

