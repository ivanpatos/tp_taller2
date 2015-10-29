package com.fiuba.taller2.UdriveClient.activity;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.task.GetFolderAsyncTask;
import com.fiuba.taller2.UdriveClient.task.LogoutAsyncTask;
import com.fiuba.taller2.UdriveClient.util.PropertyManager;

public class ConfigServerActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_config);
        loadFields();
    }

    public void loadFields(){
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        PropertyManager propertyManager = new PropertyManager(this);
        String serverUrl = sharedPreferences.getString("serverUrl", propertyManager.getProperty("url.server"));
        ((TextView) findViewById(R.id.inputUrlServer)).setText(serverUrl);
    }

    public void onClickSaveButton(View view){
        String urlServer = ((TextView) findViewById(R.id.inputUrlServer)).getText().toString();
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putString("serverUrl", urlServer);
        editor.apply();
        Toast.makeText(this, getString(R.string.config_save_success), Toast.LENGTH_SHORT).show();
        Intent intent = new Intent(this, MainActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TASK);
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        startActivity(intent);
    }
}
