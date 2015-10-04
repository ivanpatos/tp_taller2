package com.fiuba.taller2.UdriveClient.activity;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;

import com.fiuba.taller2.UdriveClient.R;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);

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

    public void onClickRegisterButton(View view){
        Button button = (Button) findViewById(R.id.buttonRegister);
        Intent intent = new Intent(this, RegisterActivity.class);
        startActivity(intent);

    }

    public void onClickLoginButton(View view){
        Button button = (Button) findViewById(R.id.buttonRegister);
        Intent intent = new Intent(this, LoginActivity.class);
        startActivity(intent);

    }
}
