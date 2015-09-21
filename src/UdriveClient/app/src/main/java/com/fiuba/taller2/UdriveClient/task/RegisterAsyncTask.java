package com.fiuba.taller2.UdriveClient.task;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.os.AsyncTask;
import android.widget.Toast;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.activity.HomeActivity;
import com.fiuba.taller2.UdriveClient.util.PropertyManager;

import org.json.JSONObject;

import java.net.URL;

public class RegisterAsyncTask extends AsyncTask<String, String, JSONObject> {

    private Activity activity;
    private Context context;
    private ProgressDialog dialog;

    public RegisterAsyncTask(Activity activity) {
        this.activity = activity;
        this.context = activity.getApplicationContext();
    }

    @Override
    protected JSONObject doInBackground(String... params) {
        PropertyManager propertyManager = new PropertyManager(context);
        String serverUrl = propertyManager.getProperty("url.server");
        String userUrl = propertyManager.getProperty("url.user");
        String urlString = serverUrl + userUrl;
        JSONObject response = null;
        try{
            URL url = new URL(urlString);
            String json = params[0];
            RestConnection restConnection = new RestConnection();
            response = restConnection.post(url, json);
        }catch (Exception ex){
            ex.printStackTrace();
        }
        return response;
    }

    @Override
    protected void onPreExecute() {
        dialog = new ProgressDialog(activity);
        dialog.setMessage(context.getString(R.string.register_waiting));
        dialog.setCancelable(false);
        dialog.show();
    }

    @Override
    protected void onPostExecute(JSONObject jsonObject) {
        dialog.dismiss();
        try {
            String result = (String) jsonObject.get("result");
            if (result.equals("ERROR")) {

                Integer errorCode =  (Integer) jsonObject.get("errorCode");
                switch (errorCode){
                    case 3:
                        Toast.makeText(context, context.getString(R.string.register_error_username_exists), Toast.LENGTH_SHORT).show();
                        break;
                    default:
                        Toast.makeText(context, context.getString(R.string.register_error), Toast.LENGTH_SHORT).show();
                        break;
                }
                return;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        Intent intent = new Intent(activity, HomeActivity.class);
        activity.startActivity(intent);
        Toast.makeText(context, context.getString(R.string.register_success), Toast.LENGTH_SHORT).show();
    }
}

