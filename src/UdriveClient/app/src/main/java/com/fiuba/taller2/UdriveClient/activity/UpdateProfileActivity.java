package com.fiuba.taller2.UdriveClient.activity;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.View;
import android.widget.TextView;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.UserRequestDTO;
import com.fiuba.taller2.UdriveClient.task.UpdateProfileAsyncTask;
import com.fiuba.taller2.UdriveClient.validator.UpdateProfileValidator;
import com.google.gson.Gson;

import java.util.concurrent.ExecutionException;

public class UpdateProfileActivity extends AppCompatActivity {

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_update_profile);
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        String username = sharedPreferences.getString("username", "null");
        setTitle(username);
        loadFields();
    }

    public void loadFields(){
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        String name = sharedPreferences.getString("name", "null");
        ((TextView) findViewById(R.id.updateProfileTextName)).setText(name);
        String mail = sharedPreferences.getString("mail", "null");
        ((TextView) findViewById(R.id.updateProfileTextEmail)).setText(mail);
    }

    public boolean onCreateOptionsMenu(Menu menu) {
        return true;
    }

    public void onClickUpdateProfileButton(View view) throws ExecutionException, InterruptedException {
        UpdateProfileAsyncTask updateProfileAsyncTask = new UpdateProfileAsyncTask(this);
        String name = ((TextView) findViewById(R.id.updateProfileTextName)).getText().toString();
        String mail = ((TextView) findViewById(R.id.updateProfileTextEmail)).getText().toString();
        UserRequestDTO userRequestDTO = new UserRequestDTO();
        userRequestDTO.setName(name);
        userRequestDTO.setMail(mail);
        UpdateProfileValidator uploadProfileValidator = new UpdateProfileValidator(this);
        if (uploadProfileValidator.validate(userRequestDTO)) {
            Gson gson = new Gson();
            String json = gson.toJson(userRequestDTO);
            updateProfileAsyncTask.execute(json);
        }
    }
}
