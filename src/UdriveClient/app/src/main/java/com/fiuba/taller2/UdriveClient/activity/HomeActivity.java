package com.fiuba.taller2.UdriveClient.activity;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.provider.OpenableColumns;
import android.support.v7.app.AppCompatActivity;
import android.util.Base64;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import com.cocosw.bottomsheet.BottomSheet;
import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.FileRequestDTO;
import com.fiuba.taller2.UdriveClient.dto.FolderRequestDTO;
import com.fiuba.taller2.UdriveClient.task.AddFileAsyncTask;
import com.fiuba.taller2.UdriveClient.task.AddFolderAsyncTask;
import com.fiuba.taller2.UdriveClient.task.GetFolderAsyncTask;
import com.fiuba.taller2.UdriveClient.task.LogoutAsyncTask;
import com.google.gson.Gson;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.util.ArrayList;

public class HomeActivity extends AppCompatActivity {

    private String idFolder;
    private Activity context;
    private static final int RESULT_LOAD_FILE = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home);
        context = this;
        initViewList();

    }

    @Override
    public void onResume(){
        super.onResume();
        initViewList();
    }

    private void initViewList() {
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        Bundle extras = getIntent().getExtras();
        idFolder = "";
        if (extras != null) {
            idFolder = (String) extras.get("idFolder");
        } else {
            idFolder = sharedPreferences.getString("username", "");

        }
        GetFolderAsyncTask getFolderAsyncTask = new GetFolderAsyncTask(this);
        getFolderAsyncTask.execute(idFolder);

    }

    @Override
    public void onBackPressed() {
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        int cycleLevel = sharedPreferences.getInt("homeCycleLevel", 0);

        if(cycleLevel <= 1){
            resetCycleLevel();
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
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    private void onLogoutAction(){
        LogoutAsyncTask logoutAsyncTask = new LogoutAsyncTask(this);
        logoutAsyncTask.execute();
    }

    public void onFloatingMenuAction(final View view){
        new BottomSheet.Builder(this).title(R.string.home_menu_bottom_title).sheet(R.menu.menu_bottom).listener(new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                switch (which) {
                    case R.id.new_folder:
                        actionOnCreateFolder();
                        break;
                    case R.id.new_file:
                        actionOnCreateFile();
                        break;
                }
            }
        }).show();
    }

    private void actionOnCreateFolder() {
        LayoutInflater li = LayoutInflater.from(context);
        View promptsView = li.inflate(R.layout.dialog_add_folder, null);

        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
                context).setTitle(R.string.add_folder_title);

        alertDialogBuilder.setView(promptsView);
        final EditText userInput = (EditText) promptsView
                .findViewById(R.id.folderNameInput);

        alertDialogBuilder
                .setCancelable(false)
                .setPositiveButton(R.string.confirm,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog,int id) {
                                FolderRequestDTO folderRequestDTO = new FolderRequestDTO();
                                folderRequestDTO.setName(userInput.getText().toString());
                                folderRequestDTO.setIdParent(idFolder);
                                Gson gson = new Gson();
                                String json = gson.toJson(folderRequestDTO);
                                AddFolderAsyncTask addFolderAsyncTask = new AddFolderAsyncTask(context);
                                addFolderAsyncTask.execute(json);
                            }
                        })
                .setNegativeButton(R.string.cancel,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                dialog.cancel();
                            }
                        });
        AlertDialog alertDialog = alertDialogBuilder.create();
        alertDialog.show();

    }


    private void actionOnCreateFile(){
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        intent.setType("*/*");
        startActivityForResult(intent, RESULT_LOAD_FILE);

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        try {
            if(resultCode == RESULT_OK){
                switch (requestCode){
                    case RESULT_LOAD_FILE:
                        if(data != null){
                            Uri uri = data.getData();

                            String fileName = "";
                            Cursor cursor = getContentResolver().query(uri, null, null, null, null, null);
                            try {
                                if (cursor != null && cursor.moveToFirst()) {
                                    fileName = cursor.getString(
                                            cursor.getColumnIndex(OpenableColumns.DISPLAY_NAME));

                                }
                            } finally {
                                cursor.close();
                            }
                            InputStream inputStream = getContentResolver().openInputStream(uri);
                            byte[] buffer = new byte[8192];
                            int bytesRead;
                            ByteArrayOutputStream output = new ByteArrayOutputStream();
                            while ((bytesRead = inputStream.read(buffer)) != -1)
                            {
                                output.write(buffer, 0, bytesRead);
                            }
                            byte[] fbytesFile = output.toByteArray();

                            String fileEncoded = Base64.encodeToString(fbytesFile, Base64.DEFAULT);
                            int pos = fileName.lastIndexOf(".");
                            String filenameWithoutExtension = "";
                            String extension = "";
                            if (pos > 0) {
                                filenameWithoutExtension = fileName.substring(0,pos);
                                extension = fileName.substring(pos + 1);
                            }

                            FileRequestDTO fileRequestDTO = new FileRequestDTO();
                            fileRequestDTO.setName(filenameWithoutExtension);
                            fileRequestDTO.setExtension(extension);
                            fileRequestDTO.setLabels(new ArrayList<String>());
                            fileRequestDTO.setIdFolder(idFolder);
                            fileRequestDTO.setData(fileEncoded);
                            Gson gson = new Gson();
                            String json = gson.toJson(fileRequestDTO);
                            AddFileAsyncTask addFileAsyncTask = new AddFileAsyncTask(context);
                            addFileAsyncTask.execute(json);
                        }
                }

            }
        } catch (Exception e) {
            Toast.makeText(this, getString(R.string.error_save_file), Toast.LENGTH_LONG)
                    .show();
        }

    }

    private void reduceCycleLevel(){
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        int cycleLevel = sharedPreferences.getInt("homeCycleLevel", 0) - 1;
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putInt("homeCycleLevel", cycleLevel);
        editor.apply();
    }

    private void resetCycleLevel(){
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.remove("homeCycleLevel");
        editor.apply();
    }





}
