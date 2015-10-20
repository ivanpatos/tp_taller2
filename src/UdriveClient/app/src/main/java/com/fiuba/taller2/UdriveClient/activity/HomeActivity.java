package com.fiuba.taller2.UdriveClient.activity;

import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Toast;

import com.cocosw.bottomsheet.BottomSheet;
import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.task.GetFolderAsyncTask;
import com.fiuba.taller2.UdriveClient.task.LogoutAsyncTask;

public class HomeActivity extends AppCompatActivity {

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

        switch (id){
            case R.id.action_logout:
                onLogoutAction();
                return true;
            case R.id.action_config:
                onConfigAction();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    private void onLogoutAction(){
        LogoutAsyncTask logoutAsyncTask = new LogoutAsyncTask(this);
        logoutAsyncTask.execute();
    }

    private void onConfigAction(){
        Intent intent = new Intent(this, ConfigActivity.class);
        startActivity(intent);
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

    public void onFloatingMenuAction(final View view){
        new BottomSheet.Builder(this).title(R.string.home_menu_bottom_title).sheet(R.menu.menu_bottom).listener(new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                switch (which) {
                    case R.id.new_folder:
                        Toast.makeText(view.getContext(), "Agrego carpeta", Toast.LENGTH_SHORT).show();
                        Log.d("Folder", "New Folder");
                        break;
                    case R.id.new_file:
                        Toast.makeText(view.getContext(), "Agrego archivo", Toast.LENGTH_SHORT).show();
                        Log.d("File", "New File");
                        break;
                }
            }
        }).show();
    }


}
