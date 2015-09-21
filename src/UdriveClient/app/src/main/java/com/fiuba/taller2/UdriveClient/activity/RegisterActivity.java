package com.fiuba.taller2.UdriveClient.activity;

import android.graphics.Typeface;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.method.PasswordTransformationMethod;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.RegisterDTO;
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
        getMenuInflater().inflate(R.menu.menu_register, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    public void onClickRegisterButton(View view) throws ExecutionException, InterruptedException {
        Button button = (Button) findViewById(R.id.buttonRegister);
        RegisterAsyncTask registerAsyncTask = new RegisterAsyncTask(this);
        String username = ((TextView) findViewById(R.id.registerTextUsername)).getText().toString();
        String name = ((TextView) findViewById(R.id.registerTextName)).getText().toString();
        String mail = ((TextView) findViewById(R.id.registerTextEmail)).getText().toString();
        String password = ((TextView) findViewById(R.id.registerTextPassword)).getText().toString();
        RegisterDTO registerDTO = new RegisterDTO();
        registerDTO.setName(name);
        registerDTO.setUsername(username);
        registerDTO.setMail(mail);
        registerDTO.setPassword(password);
        RegisterValidator registerValidator = new RegisterValidator(this.getBaseContext());
        if (registerValidator.validate(registerDTO)) {
            Gson gson = new Gson();
            String json = gson.toJson(registerDTO);
            registerAsyncTask.execute(json);
        }
    }

}