package com.fiuba.taller2.UdriveClient.activity;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.FolderDTO;
import com.fiuba.taller2.UdriveClient.task.GetFolderAsyncTask;
import com.fiuba.taller2.UdriveClient.task.LogoutAsyncTask;

import java.util.Map;

public class HomeActivity extends AppCompatActivity {

    private Map<String, FolderDTO> documents;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home);
        initViewList();

    }

    private void initViewList() {
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        Bundle extras = getIntent().getExtras();
        String idFolder = "";
        if (extras != null) {
            idFolder = (String) extras.get("idFolder");
        } else {
            idFolder = sharedPreferences.getString("username", "");
        }
        increaseCycleLevel();
        GetFolderAsyncTask folderAsyncTask = new GetFolderAsyncTask(this);
        folderAsyncTask.execute(idFolder);

    }

    @Override
    public void onBackPressed() {
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        int cycleLevel = sharedPreferences.getInt("homeCycleLevel", 0);
        if(cycleLevel <= 1){
            moveTaskToBack(true);
            finish();
            super.onBackPressed();
        }else{
            reduceCycleLevel();
            super.onBackPressed();
            overridePendingTransition(R.anim.slide_in_left, R.anim.slide_out_right);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_home, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        if (id == R.id.action_logout) {
            onLogoutAction();
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    private void onLogoutAction(){
        LogoutAsyncTask logoutAsyncTask = new LogoutAsyncTask(this);
        logoutAsyncTask.execute();
    }

    private void increaseCycleLevel(){
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        int cycleLevel = sharedPreferences.getInt("homeCycleLevel", 0) + 1;
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putInt("homeCycleLevel", cycleLevel);
        editor.apply();
    }

    private void reduceCycleLevel(){
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        int cycleLevel = sharedPreferences.getInt("homeCycleLevel", 0) - 1;
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putInt("homeCycleLevel", cycleLevel);
        editor.apply();
    }
}
