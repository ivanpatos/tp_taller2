package com.fiuba.taller2.UdriveClient.activity;

import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Typeface;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.text.method.PasswordTransformationMethod;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.RegisterRequestDTO;
import com.fiuba.taller2.UdriveClient.task.RegisterAsyncTask;
import com.fiuba.taller2.UdriveClient.validator.RegisterValidator;
import com.google.gson.Gson;

import java.util.concurrent.ExecutionException;

public class RegisterActivity extends AppCompatActivity {

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
        registerRequestDTO.setUsername(username);
        registerRequestDTO.setMail(mail);
        registerRequestDTO.setPassword(password);
        RegisterValidator registerValidator = new RegisterValidator(this);
        if (registerValidator.validate(registerRequestDTO)) {
            Gson gson = new Gson();
            String json = gson.toJson(registerRequestDTO);
            registerAsyncTask.execute(json);
        }
    }

}