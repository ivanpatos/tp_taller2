package com.fiuba.taller2.UdriveClient.util;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.DocumentChildResponseDTO;
import com.fiuba.taller2.UdriveClient.dto.FolderUpdateRequestDTO;
import com.fiuba.taller2.UdriveClient.dto.UserPermissionRequestDTO;
import com.fiuba.taller2.UdriveClient.task.DeleteFolderAsyncTask;
import com.fiuba.taller2.UdriveClient.task.UpdateFolderAsyncTask;
import com.fiuba.taller2.UdriveClient.validator.AddUserPermissionValidator;
import com.google.gson.Gson;

import java.util.ArrayList;

/**
 * Created by jscialabba on 18/11/15.
 */
public class FolderActionService {
    Activity activity;


    public FolderActionService(Activity activity) {
        this.activity = activity;
    }

    public void execute(DocumentChildResponseDTO file, int eventId){
        switch (eventId) {
            case R.id.modify_name:
                actionOnUpdateNameFolder(file);
                break;
            case R.id.invite_users:
                actionOnUpdateUsersFolder(file);
                break;
            case R.id.delete:
                DeleteFolderAsyncTask deleteFolderAsyncTask = new DeleteFolderAsyncTask(activity, file);
                deleteFolderAsyncTask.execute();
                break;
        }
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
        addUserButton.setOnClickListener(new View.OnClickListener() {
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


}
