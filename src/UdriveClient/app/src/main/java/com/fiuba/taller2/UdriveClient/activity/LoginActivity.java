package com.fiuba.taller2.UdriveClient.activity;

import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Typeface;
import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.method.PasswordTransformationMethod;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.LoginRequestDTO;
import com.fiuba.taller2.UdriveClient.task.LoginAsyncTask;
import com.fiuba.taller2.UdriveClient.validator.LoginValidator;
import com.google.gson.Gson;

import java.util.concurrent.ExecutionException;

public class LoginActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_login);
        EditText password = (EditText) findViewById(R.id.loginTextPassword);
        password.setTypeface(Typeface.DEFAULT);
        password.setTransformationMethod(new PasswordTransformationMethod());
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        return true;
    }

    public void onClickLoginButton(View view) throws ExecutionException, InterruptedException {
        LoginAsyncTask loginAsyncTask = new LoginAsyncTask(this);
        String username = ((TextView) findViewById(R.id.loginTextUsername)).getText().toString();
        String password = ((TextView) findViewById(R.id.loginTextPassword)).getText().toString();
        LoginRequestDTO loginRequestDTO = new LoginRequestDTO();
        loginRequestDTO.setUsername(username.trim());
        loginRequestDTO.setPassword(password);
        LoginValidator loginValidator = new LoginValidator(this);
        if (loginValidator.validate(loginRequestDTO)) {
            Gson gson = new Gson();
            String json = gson.toJson(loginRequestDTO);
            loginAsyncTask.execute(json);
        }
    }

}
