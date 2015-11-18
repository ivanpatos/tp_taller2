package com.fiuba.taller2.UdriveClient.util;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.preference.PreferenceManager;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.DocumentChildResponseDTO;
import com.fiuba.taller2.UdriveClient.dto.FileUpdateRequestDTO;
import com.fiuba.taller2.UdriveClient.dto.LabelDTO;
import com.fiuba.taller2.UdriveClient.dto.UserPermissionRequestDTO;
import com.fiuba.taller2.UdriveClient.dto.VersionDTO;
import com.fiuba.taller2.UdriveClient.task.DeleteFileAsyncTask;
import com.fiuba.taller2.UdriveClient.task.GetFileAsyncTask;
import com.fiuba.taller2.UdriveClient.task.GetMetadataFileAsyncTask;
import com.fiuba.taller2.UdriveClient.task.UpdateFileAsyncTask;
import com.fiuba.taller2.UdriveClient.validator.AddLabelValidator;
import com.fiuba.taller2.UdriveClient.validator.AddUserPermissionValidator;
import com.google.gson.Gson;

import java.util.ArrayList;

/**
 * Created by jscialabba on 18/11/15.
 */
public class FileActionService {
    Activity activity;


    public FileActionService(Activity activity) {
        this.activity = activity;
    }

    public void execute(DocumentChildResponseDTO file, int eventId){
        switch (eventId) {
            case R.id.view_metadata:
                GetMetadataFileAsyncTask getMetadataFileAsyncTask = new GetMetadataFileAsyncTask(activity);
                getMetadataFileAsyncTask.execute(file.getId());
                break;
            case R.id.modify_name:
                actionOnUpdateNameFile(file);
                break;
            case R.id.add_new_version:
                actionOnAddNewVersion(file);
                break;
            case R.id.download_version:
                actionOnDownloadVersion(file);
                break;
            case R.id.add_tags:
                actionOnAddTagsFile(file);
                break;
            case R.id.invite_users:
                actionOnUpdateUsersFile(file);
                break;
            case R.id.delete:
                DeleteFileAsyncTask deleteFileAsyncTask = new DeleteFileAsyncTask(activity, file);
                deleteFileAsyncTask.execute();
                break;
            case R.id.recover:
                actionOnRecoverFile(file);
                break;
        }
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
        final View promptsView = li.inflate(R.layout.dialog_add_tags_file, null);

        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
                activity).setTitle(R.string.add_tag_file_title);

        alertDialogBuilder.setView(promptsView);

        final ArrayList<LabelDTO> labelsList = new ArrayList<>();
        for(LabelDTO label: documentChildSelected.getLabels()){
            labelsList.add(label);
        }
        final LabelAdapter adapter = new LabelAdapter(activity,
                R.layout.listview_item_label, labelsList);

        final ListView labelListView = (ListView) promptsView.findViewById(R.id.tagsList);

        labelListView.setAdapter(adapter);

        alertDialogBuilder
                .setCancelable(false)
                .setPositiveButton(R.string.confirm,
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {

                                FileUpdateRequestDTO fileUpdateRequestDTO = new FileUpdateRequestDTO();
                                fileUpdateRequestDTO.setName(documentChildSelected.getName());
                                fileUpdateRequestDTO.setExtension(documentChildSelected.getExtension());
                                fileUpdateRequestDTO.setDeleted(documentChildSelected.getDeleted());
                                fileUpdateRequestDTO.setUsers(documentChildSelected.getUsers());
                                fileUpdateRequestDTO.setLabels(labelsList);
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

        final Button addTagButton = (Button) promptsView.findViewById(R.id.btnAddTag);
        addTagButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                final TextView labelView = (TextView) promptsView.findViewById(R.id.tagInput);
                LabelDTO labelDTO = new LabelDTO(labelView.getText().toString());
                AddLabelValidator addTagValidator = new AddLabelValidator(activity, labelsList);
                if(addTagValidator.validate(labelDTO)){
                    labelsList.add(labelDTO);
                    adapter.notifyDataSetChanged();
                    labelView.setText("");
                }
            }

        });
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
        addUserButton.setOnClickListener(new View.OnClickListener() {
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

    private void actionOnAddNewVersion(DocumentChildResponseDTO documentChildSelected) {
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


    private void actionOnDownloadVersion(final DocumentChildResponseDTO documentChildSelected) {

        final Integer version = Integer.valueOf(documentChildSelected.getVersion());
        LayoutInflater li = LayoutInflater.from(activity);
        final View promptsView = li.inflate(R.layout.dialog_versions_file, null);

        AlertDialog.Builder alertDialogBuilder = new AlertDialog.Builder(
                activity).setTitle(R.string.download_file_versions_title);

        alertDialogBuilder.setView(promptsView);

        final ArrayList<VersionDTO> versionsList = new ArrayList<>();
        for(int i = version; i >= 1; i--){
            VersionDTO versionRequest = new VersionDTO();
            versionRequest.setVersion(String.valueOf(i));
            versionsList.add(versionRequest);
        }
        final VersionAdapter adapter = new VersionAdapter(activity,
                R.layout.listview_item_version, versionsList);

        final ListView versionsListView = (ListView) promptsView.findViewById(R.id.versionsList);

        versionsListView.setAdapter(adapter);



        alertDialogBuilder
                .setCancelable(true);
        final AlertDialog alertDialog = alertDialogBuilder.create();
        alertDialog.show();


        versionsListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            public void onItemClick(AdapterView<?> arg0, View v, int position, long arg3) {
                VersionDTO versionSelected = versionsList.get(position);
                String idFileSelected = documentChildSelected.getId();
                GetFileAsyncTask getFileAsyncTask = new GetFileAsyncTask(activity);
                getFileAsyncTask.execute(idFileSelected, versionSelected.getVersion());
                alertDialog.hide();
            }
        });
    }



}
