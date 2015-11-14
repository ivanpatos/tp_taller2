package com.fiuba.taller2.UdriveClient.validator;

import android.content.Context;
import android.widget.Toast;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.UserRequestDTO;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class UpdateProfileValidator {
    private Context context;

    public UpdateProfileValidator(Context context) {
        this.context = context;
    }

    public boolean validate(UserRequestDTO userRequestDTO) {
        if (!isValidText(userRequestDTO.getName())) {
            Toast.makeText(context, context.getString(R.string.register_error_name) , Toast.LENGTH_SHORT).show();
            return false;
        }
        if(!isValidEmail(userRequestDTO.getMail())){
            Toast.makeText(context,  context.getString(R.string.register_error_email), Toast.LENGTH_SHORT).show();
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
    private boolean isValidEmail(String email) {
        String EMAIL_PATTERN = "^[_A-Za-z0-9-\\+]+(\\.[_A-Za-z0-9-]+)*@"
                + "[A-Za-z0-9-]+(\\.[A-Za-z0-9]+)*(\\.[A-Za-z]{2,})$";

        Pattern pattern = Pattern.compile(EMAIL_PATTERN);
        Matcher matcher = pattern.matcher(email);
        return matcher.matches();
    }
}