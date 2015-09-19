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

import org.json.JSONArray;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;

public class RegisterAsyncTask extends AsyncTask<String, String, JSONArray> {

    private Activity activity;
    private Context context;
    private ProgressDialog dialog;

    public RegisterAsyncTask(Activity activity) {
        this.activity = activity;
        this.context = activity.getApplicationContext();
    }

    public void register(String json) {
        PropertyManager propertyManager = new PropertyManager(context);
        String registerUrl = propertyManager.getProperty("url.register");
        this.execute(registerUrl, json);
    }

    @Override
    protected JSONArray doInBackground(String... params) {
        URL url;
        HttpURLConnection urlConnection = null;
        JSONArray response = new JSONArray();

        try {
            url = new URL(params[0]);
            urlConnection = (HttpURLConnection) url.openConnection();
            int responseCode = urlConnection.getResponseCode();

            if (responseCode == HttpURLConnection.HTTP_OK) {
                String responseString = readStream(urlConnection.getInputStream());
                response = new JSONArray(responseString);
            } else {
                response = new JSONArray("error");
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (urlConnection != null)
                urlConnection.disconnect();
        }
        return response;
    }

    private String readStream(InputStream in) {
        BufferedReader reader = null;
        StringBuffer response = new StringBuffer();
        try {
            reader = new BufferedReader(new InputStreamReader(in));
            String line = "";
            while ((line = reader.readLine()) != null) {
                response.append(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return response.toString();
    }


    @Override
    protected void onPreExecute() {
        dialog = new ProgressDialog(activity);
        dialog.setMessage(context.getString(R.string.register_waiting));
        dialog.setCancelable(false);
        dialog.show();
    }

    @Override
    protected void onPostExecute(JSONArray jsonArray) {
        if(jsonArray.equals("error")){
            Toast.makeText(context, "Ha ocurrido un error, intente luego", Toast.LENGTH_SHORT).show();
        }
        dialog.dismiss();

        Toast.makeText(context, context.getString(R.string.register_success) , Toast.LENGTH_SHORT).show();
        Intent intent = new Intent(activity, HomeActivity.class);
        activity.startActivity(intent);
    }
}

