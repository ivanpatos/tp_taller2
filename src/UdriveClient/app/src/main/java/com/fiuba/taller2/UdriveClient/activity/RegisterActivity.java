package com.fiuba.taller2.UdriveClient.activity;

import android.content.Intent;
import android.graphics.Typeface;
import android.net.Uri;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.method.PasswordTransformationMethod;
import android.util.Base64;
import android.view.Menu;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.RegisterRequestDTO;
import com.fiuba.taller2.UdriveClient.task.RegisterAsyncTask;
import com.fiuba.taller2.UdriveClient.validator.RegisterValidator;
import com.google.gson.Gson;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.util.concurrent.ExecutionException;

public class RegisterActivity extends AppCompatActivity {

    private String profilePicture = "";
    private static final int RESULT_LOAD_IMAGE = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);
        EditText password = (EditText) findViewById(R.id.registerTextPassword);
        password.setTypeface(Typeface.DEFAULT);
        password.setTransformationMethod(new PasswordTransformationMethod());
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        return true;
    }

    public void onClickRegisterButton(View view) throws ExecutionException, InterruptedException {
        RegisterAsyncTask registerAsyncTask = new RegisterAsyncTask(this);
        String username = ((TextView) findViewById(R.id.registerTextUsername)).getText().toString();
        String name = ((TextView) findViewById(R.id.registerTextName)).getText().toString();
        String mail = ((TextView) findViewById(R.id.registerTextEmail)).getText().toString();
        String password = ((TextView) findViewById(R.id.registerTextPassword)).getText().toString();
        RegisterRequestDTO registerRequestDTO = new RegisterRequestDTO();
        registerRequestDTO.setName(name);
        registerRequestDTO.setUsername(username.trim());
        registerRequestDTO.setMail(mail);
        registerRequestDTO.setPassword(password);
        registerRequestDTO.setProfilePicture(profilePicture);
        RegisterValidator registerValidator = new RegisterValidator(this);
        if (registerValidator.validate(registerRequestDTO)) {
            Gson gson = new Gson();
            String json = gson.toJson(registerRequestDTO);
            registerAsyncTask.execute(json);
        }
    }

    public void onClickRegisterPicture(View view){
        Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        intent.setType("image/*");
        startActivityForResult(intent, RESULT_LOAD_IMAGE);
    }

    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        try {
            if (resultCode == RESULT_OK) {
                switch (requestCode) {
                    case RESULT_LOAD_IMAGE:
                        if (data != null) {
                            Uri uri = data.getData();
                            ((ImageView) findViewById(R.id.registerPicture)).setImageURI(uri);
                            InputStream inputStream = getContentResolver().openInputStream(uri);
                            byte[] buffer = new byte[8192];
                            int bytesRead;
                            ByteArrayOutputStream output = new ByteArrayOutputStream();
                            while ((bytesRead = inputStream.read(buffer)) != -1) {
                                output.write(buffer, 0, bytesRead);
                            }
                            byte[] fbytesFile = output.toByteArray();
                            profilePicture = Base64.encodeToString(fbytesFile, Base64.DEFAULT);
                        }
                }
            }
        } catch (Exception e) {
            Toast.makeText(this, getString(R.string.error_save_file), Toast.LENGTH_LONG)
                    .show();
        }
    }

}