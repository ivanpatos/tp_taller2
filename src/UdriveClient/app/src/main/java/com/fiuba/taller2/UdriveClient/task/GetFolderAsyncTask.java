package com.fiuba.taller2.UdriveClient.task;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.preference.PreferenceManager;
import android.view.LayoutInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.cocosw.bottomsheet.BottomSheet;
import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.activity.HomeActivity;
import com.fiuba.taller2.UdriveClient.dto.DocumentChildResponseDTO;
import com.fiuba.taller2.UdriveClient.dto.FileUpdateRequestDTO;
import com.fiuba.taller2.UdriveClient.dto.FolderResponseDTO;
import com.fiuba.taller2.UdriveClient.dto.FolderUpdateRequestDTO;
import com.fiuba.taller2.UdriveClient.dto.LabelRequestDTO;
import com.fiuba.taller2.UdriveClient.dto.RestConnectionDTO;
import com.fiuba.taller2.UdriveClient.dto.UserPermissionRequestDTO;
import com.fiuba.taller2.UdriveClient.exception.ConnectionException;
import com.fiuba.taller2.UdriveClient.util.DocumentAdapter;
import com.fiuba.taller2.UdriveClient.util.PropertyManager;
import com.fiuba.taller2.UdriveClient.util.UserAdapter;
import com.fiuba.taller2.UdriveClient.validator.AddUserPermissionValidator;
import com.google.gson.Gson;

import org.json.JSONException;
import org.json.JSONObject;

import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Set;

public class GetFolderAsyncTask extends AsyncTask<String, String, JSONObject> {

    private Activity activity;
    private ProgressDialog dialog;
    private String errorMessage = "";
    private DocumentChildResponseDTO documentChildSelected;
    public GetFolderAsyncTask(Activity activity) {
        this.activity = activity;
    }

    @Override
    protected JSONObject doInBackground(String... params) {
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(activity);
        PropertyManager propertyManager = new PropertyManager(activity);
        String serverUrl = sharedPreferences.getString("serverUrl", propertyManager.getProperty("url.server"));
        String folderUrl = propertyManager.getProperty("url.folder");
        String idFolder = params[0];
        JSONObject response = null;
        RestConnectionDTO restConnectionDTO = new RestConnectionDTO();
        String username = sharedPreferences.getString("username", "null");
        String token = sharedPreferences.getString("token", "null");
        try {
            URL url = new URL(serverUrl + folderUrl + "/" + idFolder);
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
        } catch (Exception e) {
            e.printStackTrace();
        }

        try {
            Gson gson = new Gson();
            FolderResponseDTO folderResponseDTO = gson.fromJson(jsonObject.get("data").toString(), FolderResponseDTO.class);
            increaseCycleLevel();
            refreshViewActivity(folderResponseDTO);

        } catch (JSONException e) {
            e.printStackTrace();
            }
    }


    private void refreshViewActivity(FolderResponseDTO folderResponseDTO) {
        activity.setTitle(folderResponseDTO.getName());

        final ArrayList<DocumentChildResponseDTO> documentChildResponseDTOs = folderResponseDTO.getChildren();
        final DocumentAdapter adapter = new DocumentAdapter(activity,
                R.layout.listview_item_document, documentChildResponseDTOs);

        final ListView documentList = (ListView) activity.findViewById(R.id.documentList);


        for(DocumentChildResponseDTO document : documentChildResponseDTOs){
            if(document.getType().equals("file")){
                LoadMetadataFileAsyncTask loadMetadataFileAsyncTask = new LoadMetadataFileAsyncTask(activity, document);
                loadMetadataFileAsyncTask.execute(document.getId());
            }
        }

        documentList.setAdapter(adapter);
        documentList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            public void onItemClick(AdapterView<?> arg0, View v, int position, long arg3) {
                documentChildSelected = documentChildResponseDTOs.get(position);

                if (documentChildSelected.getType().equals("folder")) {
                    String idFolderSelected = documentChildSelected.getId();
                    Intent intent = new Intent(activity, HomeActivity.class);
                    intent.putExtra("idFolder", idFolderSelected);
                    activity.startActivity(intent);
                    activity.overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);

                } else {
                    String idFileSelected = documentChildSelected.getId();
                    GetFileAsyncTask getFileAsyncTask = new GetFileAsyncTask(activity);

                    // Cuando implementemos la version, no va hardcodeada
                    String version = documentChildSelected.getVersion();
                    getFileAsyncTask.execute(idFileSelected, version);
                }
            }
        });
        documentList.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            public boolean onItemLongClick(AdapterView<?> arg0, View v, int position, long arg3) {
                documentChildSelected = documentChildResponseDTOs.get(position);
                if (documentChildSelected.getType().equals("file")) {
                    BottomSheet.Builder builder = new BottomSheet.Builder(activity).title(R.string.home_menu_bottom_title).sheet(R.menu.menu_actions_item_file);
                    BottomSheet sheet = builder.build();

                    SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(activity);
                    Set<String> notPermissionsFile = sharedPreferences.getStringSet("notPermissionsFile", null);
                    if (notPermissionsFile != null) {
                        for (String id : notPermissionsFile) {
                            Integer idInt = Integer.parseInt(id);
                            MenuItem item = sheet.getMenu().findItem(idInt);
                            item.setVisible(false);
                        }

                    }

                    builder.listener(new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialog, int which) {
                            switch (which) {
                                case R.id.view_metadata:
                                    GetMetadataFileAsyncTask getMetadataFileAsyncTask = new GetMetadataFileAsyncTask(activity);
                                    getMetadataFileAsyncTask.execute(documentChildSelected.getId());
                                    break;
                                case R.id.modify_name:
                                    actionOnUpdateNameFile(documentChildSelected);
                                    break;
                                case R.id.add_new_version:
                                    actionOnAddNewVersion();
                                    break;
                                case R.id.add_tags:
                                    actionOnAddTagsFile(documentChildSelected);
                                    break;
                                case R.id.invite_users:
                                    actionOnUpdateUsersFile(documentChildSelected);
                                    break;
                                case R.id.delete:
                                    DeleteFileAsyncTask deleteFileAsyncTask = new DeleteFileAsyncTask(activity, documentChildSelected);
                                    deleteFileAsyncTask.execute();
                                    break;
                                case R.id.recover:
                                    actionOnRecoverFile(documentChildSelected);
                                    break;
                            }
                        }
                    }).show();
                } else {
                    if (!isSpecialFolder(documentChildSelected)) {

                        BottomSheet.Builder builder = new BottomSheet.Builder(activity).title(R.string.home_menu_bottom_title).sheet(R.menu.menu_actions_item_folder);
                        BottomSheet sheet = builder.build();


                        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(activity);
                        Set<String> notPermissionsFolder = sharedPreferences.getStringSet("notPermissionsFolder", null);
                        if (notPermissionsFolder != null) {
                            for (String id : notPermissionsFolder) {
                                Integer idInt = Integer.parseInt(id);
                                MenuItem item = sheet.getMenu().findItem(idInt);
                                item.setVisible(false);
                            }

                        }

                        builder.listener(new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                switch (which) {

                                    case R.id.modify_name:
                                        actionOnUpdateNameFolder(documentChildSelected);
                                        break;
                                    case R.id.invite_users:
                                        actionOnUpdateUsersFolder(documentChildSelected);
                                        break;
                                    case R.id.delete:
                                        DeleteFolderAsyncTask deleteFolderAsyncTask = new DeleteFolderAsyncTask(activity, documentChildSelected);
                                        deleteFolderAsyncTask.execute();
                                        break;
                                }
                            }
                        }).show();
                    }

                }
                return true;
            }
        });


    }

    private void increaseCycleLevel(){
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(activity);
        int cycleLevel = sharedPreferences.getInt("homeCycleLevel", 0) + 1;
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putInt("homeCycleLevel", cycleLevel);
        editor.apply();
    }


    private void actionOnUpdateNameFolder(final DocumentChildResponseDTO documentChildSelected) {
        LayoutInflater li = LayoutInflater.from(activity);
        View promptsView = li.inflate(R.layout.dialog_update_name_folder, null);

        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
                activity).setTitle(R.string.update_folder_name_title);

        alertDialogBuilder.setView(promptsView);
        final EditText nameFolder = (EditText) promptsView
                .findViewById(R.id.folderNameInput);
        nameFolder.setText(documentChildSelected.getName());
        alertDialogBuilder
                .setCancelable(false)
                .setPositiveButton(R.string.confirm,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog,int id) {
                                String name = nameFolder.getText().toString();
                                FolderUpdateRequestDTO folderUpdateRequestDTO = new FolderUpdateRequestDTO();
                                folderUpdateRequestDTO.setName(name);
                                folderUpdateRequestDTO.setUsers(documentChildSelected.getUsers());
                                Gson gson = new Gson();
                                String json = gson.toJson(folderUpdateRequestDTO);
                                UpdateFolderAsyncTask updateFolderAsyncTask = new UpdateFolderAsyncTask(activity, documentChildSelected);
                                updateFolderAsyncTask.execute(json, documentChildSelected.getId());
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

    private void actionOnUpdateNameFile(final DocumentChildResponseDTO documentChildSelected) {
        LayoutInflater li = LayoutInflater.from(activity);
        View promptsView = li.inflate(R.layout.dialog_update_name_file, null);

        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
                activity).setTitle(R.string.update_file_name_title);

        alertDialogBuilder.setView(promptsView);
        final EditText nameFile = (EditText) promptsView
                .findViewById(R.id.fileNameInput);
        nameFile.setText(documentChildSelected.getName());

        alertDialogBuilder
                .setCancelable(false)
                .setPositiveButton(R.string.confirm,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog,int id) {
                                String name = nameFile.getText().toString();
                                FileUpdateRequestDTO fileUpdateRequestDTO = new FileUpdateRequestDTO();
                                fileUpdateRequestDTO.setName(name);
                                fileUpdateRequestDTO.setExtension(documentChildSelected.getExtension());
                                fileUpdateRequestDTO.setDeleted(documentChildSelected.getDeleted());
                                fileUpdateRequestDTO.setUsers(documentChildSelected.getUsers());
                                fileUpdateRequestDTO.setLabels(documentChildSelected.getLabels());
                                Gson gson = new Gson();
                                String json = gson.toJson(fileUpdateRequestDTO);
                                UpdateFileAsyncTask updateFileAsyncTask = new UpdateFileAsyncTask(activity, documentChildSelected);
                                updateFileAsyncTask.execute(json, documentChildSelected.getId());
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

    private void actionOnAddTagsFile(final DocumentChildResponseDTO documentChildSelected){
        LayoutInflater li = LayoutInflater.from(activity);
        View promptsView = li.inflate(R.layout.dialog_add_tags_file, null);

        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
                activity).setTitle(R.string.add_tag_file_title);

        alertDialogBuilder.setView(promptsView);
        final EditText nameTag = (EditText) promptsView
                .findViewById(R.id.tagInput);
        nameTag.setText(android.text.TextUtils.join(",", documentChildSelected.getLabels()));

        alertDialogBuilder
                .setCancelable(false)
                .setPositiveButton(R.string.confirm,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                String tags = nameTag.getText().toString();
                                ArrayList<String> items = new ArrayList<String>(Arrays.asList(tags.split(",")));
                                ArrayList<LabelRequestDTO> labels = new ArrayList<LabelRequestDTO>();
                                for (String item : items) {
                                    LabelRequestDTO labelRequestDTO = new LabelRequestDTO();
                                    labelRequestDTO.setDescription(item);
                                    labels.add(labelRequestDTO);
                                }
                                FileUpdateRequestDTO fileUpdateRequestDTO = new FileUpdateRequestDTO();
                                fileUpdateRequestDTO.setName(documentChildSelected.getName());
                                fileUpdateRequestDTO.setExtension(documentChildSelected.getExtension());
                                fileUpdateRequestDTO.setDeleted(documentChildSelected.getDeleted());
                                fileUpdateRequestDTO.setUsers(documentChildSelected.getUsers());
                                fileUpdateRequestDTO.setLabels(labels);
                                Gson gson = new Gson();
                                String json = gson.toJson(fileUpdateRequestDTO);
                                UpdateFileAsyncTask updateFileAsyncTask = new UpdateFileAsyncTask(activity, documentChildSelected);
                                updateFileAsyncTask.execute(json, documentChildSelected.getId());
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

    private void actionOnUpdateUsersFile(final DocumentChildResponseDTO documentChildSelected) {
        LayoutInflater li = LayoutInflater.from(activity);
        final View promptsView = li.inflate(R.layout.dialog_update_users, null);

        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
                activity).setTitle(R.string.update_file_users_title);

        alertDialogBuilder.setView(promptsView);

        final ArrayList<UserPermissionRequestDTO> usersList = new ArrayList<>();
        for(UserPermissionRequestDTO user : documentChildSelected.getUsers()){
            usersList.add(user);
        }
        final UserAdapter adapter = new UserAdapter(activity,
                R.layout.listview_item_user, usersList);

        final ListView userPermissionListView = (ListView) promptsView.findViewById(R.id.userPermissionList);

        userPermissionListView.setAdapter(adapter);



        alertDialogBuilder
                .setCancelable(false)
                .setPositiveButton(R.string.confirm,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                FileUpdateRequestDTO fileUpdateRequestDTO = new FileUpdateRequestDTO();
                                fileUpdateRequestDTO.setName(documentChildSelected.getName());
                                fileUpdateRequestDTO.setExtension(documentChildSelected.getExtension());
                                fileUpdateRequestDTO.setDeleted(documentChildSelected.getDeleted());
                                fileUpdateRequestDTO.setUsers(usersList);
                                fileUpdateRequestDTO.setLabels(documentChildSelected.getLabels());
                                Gson gson = new Gson();
                                String json = gson.toJson(fileUpdateRequestDTO);
                                UpdateFileAsyncTask updateFileAsyncTask = new UpdateFileAsyncTask(activity, documentChildSelected);
                                updateFileAsyncTask.execute(json, documentChildSelected.getId());
                            }
                        })
                .setNegativeButton(R.string.cancel,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                dialog.cancel();
                            }
                        });
        AlertDialog alertDialog = alertDialogBuilder.create();

        final Button addUserButton = (Button) promptsView.findViewById(R.id.btnAddUser);
        addUserButton.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                final TextView usernameView = (TextView) promptsView.findViewById(R.id.userNameInput);
                UserPermissionRequestDTO userPermissionRequestDTO = new UserPermissionRequestDTO(usernameView.getText().toString());
                AddUserPermissionValidator addUserPermissionValidator = new AddUserPermissionValidator(activity, usersList);
                if(addUserPermissionValidator.validate(userPermissionRequestDTO)){
                    usersList.add(userPermissionRequestDTO);
                    adapter.notifyDataSetChanged();
                    usernameView.setText("");
                }
            }
        });


        alertDialog.show();
    }


    private void actionOnUpdateUsersFolder(final DocumentChildResponseDTO documentChildSelected) {
        LayoutInflater li = LayoutInflater.from(activity);
        final View promptsView = li.inflate(R.layout.dialog_update_users, null);

        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
                activity).setTitle(R.string.update_folder_users_title);

        alertDialogBuilder.setView(promptsView);

        final ArrayList<UserPermissionRequestDTO> usersList = new ArrayList<>();

        final UserAdapter adapter = new UserAdapter(activity,
                R.layout.listview_item_user, usersList);

        final ListView userPermissionListView = (ListView) promptsView.findViewById(R.id.userPermissionList);

        userPermissionListView.setAdapter(adapter);

        alertDialogBuilder
                .setCancelable(false)
                .setPositiveButton(R.string.confirm,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                FolderUpdateRequestDTO folderUpdateRequestDTO = new FolderUpdateRequestDTO();
                                folderUpdateRequestDTO.setName(documentChildSelected.getName());
                                folderUpdateRequestDTO.setUsers(usersList);
                                Gson gson = new Gson();
                                String json = gson.toJson(folderUpdateRequestDTO);
                                UpdateFolderAsyncTask updateFolderAsyncTask = new UpdateFolderAsyncTask(activity, documentChildSelected);
                                updateFolderAsyncTask.execute(json, documentChildSelected.getId());
                            }
                        })
                .setNegativeButton(R.string.cancel,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                dialog.cancel();
                            }
                        });
        AlertDialog alertDialog = alertDialogBuilder.create();

        final Button addUserButton = (Button) promptsView.findViewById(R.id.btnAddUser);
        addUserButton.setOnClickListener(new OnClickListener() {
            public void onClick(View v) {
                final TextView usernameView = (TextView) promptsView.findViewById(R.id.userNameInput);
                UserPermissionRequestDTO userPermissionRequestDTO = new UserPermissionRequestDTO(usernameView.getText().toString());
                AddUserPermissionValidator addUserPermissionValidator = new AddUserPermissionValidator(activity, usersList);
                if (addUserPermissionValidator.validate(userPermissionRequestDTO)) {
                    usersList.add(userPermissionRequestDTO);
                    adapter.notifyDataSetChanged();
                    usernameView.setText("");
                }
            }
        });


        alertDialog.show();
    }



    private void actionOnRecoverFile(final DocumentChildResponseDTO documentChildSelected) {
        FileUpdateRequestDTO fileUpdateRequestDTO = new FileUpdateRequestDTO();
        fileUpdateRequestDTO.setName(documentChildSelected.getName());
        fileUpdateRequestDTO.setExtension(documentChildSelected.getExtension());
        fileUpdateRequestDTO.setDeleted(false);
        fileUpdateRequestDTO.setUsers(documentChildSelected.getUsers());
        fileUpdateRequestDTO.setLabels(documentChildSelected.getLabels());
        Gson gson = new Gson();
        String json = gson.toJson(fileUpdateRequestDTO);
        UpdateFileAsyncTask updateFileAsyncTask = new UpdateFileAsyncTask(activity, documentChildSelected);
        updateFileAsyncTask.execute(json, documentChildSelected.getId());
        ListView documentList = (ListView) activity.findViewById(R.id.documentList);
        DocumentAdapter adapter = (DocumentAdapter) documentList.getAdapter();
        adapter.remove(documentChildSelected);
        adapter.notifyDataSetChanged();
    }


    private boolean isSpecialFolder(DocumentChildResponseDTO documentChildSelected){
        String sharedWithCode = "sharedwith";
        String trashCode = "trash";
        String recoveredCode = "recovered";
        String id = documentChildSelected.getId();
        if(id.startsWith(sharedWithCode) || id.startsWith(trashCode) || id.startsWith(recoveredCode)){
            return true;
        }
        return false;

    }


    private void actionOnAddNewVersion() {
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        intent.setType("*/*");
        intent.putExtra("idFile", documentChildSelected.getId());
        Integer RESULT_UPDATE_FILE = 2;
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(activity);
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putString("idFile", documentChildSelected.getId());
        editor.apply();
        activity.startActivityForResult(intent, RESULT_UPDATE_FILE);
    }


}

