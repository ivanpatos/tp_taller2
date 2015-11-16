package com.fiuba.taller2.UdriveClient.validator;

import android.content.Context;
import android.widget.Toast;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.UserPermissionRequestDTO;
import com.fiuba.taller2.UdriveClient.dto.UserRequestDTO;

import java.util.Collection;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class AddUserPermissionValidator {
    private Context context;
    Collection<UserPermissionRequestDTO> listUsers;

    public AddUserPermissionValidator(Context context, Collection<UserPermissionRequestDTO> listUsers) {
        this.context = context;
        this.listUsers = listUsers;
    }

    public boolean validate(UserPermissionRequestDTO userPermission) {
        if (!isValidText(userPermission.getUsername())) {
            Toast.makeText(context, context.getString(R.string.user_permission_invalid_user) , Toast.LENGTH_SHORT).show();
            return false;
        }
        if(existInList(listUsers, userPermission.getUsername())){
            Toast.makeText(context,  context.getString(R.string.user_permission_existent_user), Toast.LENGTH_SHORT).show();
            return false;
        }
        return true;
    }


    private boolean isValidText(String text) {
        if (text != null && !text.isEmpty())  {
            return true;
        }
        return false;
    }

    // validating email id
    private boolean existInList(Collection<UserPermissionRequestDTO> listUsers, String username) {
        for(UserPermissionRequestDTO user : listUsers){
            if(user.getUsername().equals(username)) return true;
        }
        return false;

    }
}