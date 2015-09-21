package com.fiuba.taller2.UdriveClient.validator;

import android.content.Context;
import android.widget.Toast;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.LoginDTO;
import com.fiuba.taller2.UdriveClient.dto.RegisterDTO;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by jscialabba on 19/09/15.
 */
public class LoginValidator {
    private Context context;

    public LoginValidator(Context context) {
        this.context = context;
    }

    public boolean validate(LoginDTO loginDTO) {
        if (!isValidText(loginDTO.getUsername())) {
            Toast.makeText(context, context.getString(R.string.login_error_username) , Toast.LENGTH_SHORT).show();
            return false;
        }
        if(!isValidPassword(loginDTO.getPassword())){
            Toast.makeText(context, context.getString(R.string.login_error_password), Toast.LENGTH_SHORT).show();
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

    private boolean isValidPassword(String pass) {
        if (pass != null && pass.length() > 6) {
            return true;
        }
        return false;
    }
}
