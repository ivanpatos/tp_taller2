package com.fiuba.taller2.UdriveClient.activity;

import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.util.Base64;
import android.view.Menu;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.UserRequestDTO;
import com.fiuba.taller2.UdriveClient.task.UpdateProfileAsyncTask;
import com.fiuba.taller2.UdriveClient.validator.UpdateProfileValidator;
import com.google.gson.Gson;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.util.concurrent.ExecutionException;

public class UpdateProfileActivity extends AppCompatActivity {

    private String profilePicture;
    private static final int RESULT_LOAD_IMAGE = 1;

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
        String picture = sharedPreferences.getString("profilePicture", "null");
        if (picture != "") {
            byte[] decodedPicture = Base64.decode(picture, Base64.DEFAULT);
            Bitmap decodedBytes = BitmapFactory.decodeByteArray(decodedPicture, 0, decodedPicture.length);
            ((ImageView) findViewById(R.id.updateProfilePicture)).setImageBitmap(decodedBytes);
            profilePicture = picture;
        }
        else
            ((ImageView)findViewById(R.id.updateProfilePicture)).setImageResource(R.drawable.profile_image);
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
        userRequestDTO.setProfilePicture(profilePicture);
        UpdateProfileValidator uploadProfileValidator = new UpdateProfileValidator(this);
        if (uploadProfileValidator.validate(userRequestDTO)) {
            Gson gson = new Gson();
            String json = gson.toJson(userRequestDTO);
            updateProfileAsyncTask.execute(json);
        }
    }

    public void onClickUpdateProfilePicture(View view){
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
                            ((ImageView) findViewById(R.id.updateProfilePicture)).setImageURI(uri);
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
