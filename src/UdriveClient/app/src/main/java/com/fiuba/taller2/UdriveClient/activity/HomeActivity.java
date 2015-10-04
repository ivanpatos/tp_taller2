package com.fiuba.taller2.UdriveClient.activity;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.view.Menu;
import android.view.MenuItem;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.DocumentChildDTO;
import com.fiuba.taller2.UdriveClient.dto.FolderDTO;
import com.fiuba.taller2.UdriveClient.task.GetFolderAsyncTask;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class HomeActivity extends AppCompatActivity {

    private Map<String, FolderDTO> documents;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home);
        initViewList();

    }

    private void initViewList() {
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        Bundle extras = getIntent().getExtras();
        String idFolder = "";
        if (extras != null) {
            idFolder = (String) extras.get("idFolder");
        } else {
            idFolder = sharedPreferences.getString("username", "");
        }
        GetFolderAsyncTask folderAsyncTask = new GetFolderAsyncTask(this);
        folderAsyncTask.execute(idFolder);
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        overridePendingTransition(R.anim.slide_in_left, R.anim.slide_out_right);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_home, menu);
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

    private Map<String, FolderDTO> getDocuments() {
        documents = new HashMap<>();

        FolderDTO rootFolderDTO = new FolderDTO();
        rootFolderDTO.setId("F0");
        rootFolderDTO.setName("Principal");

        FolderDTO firstFileDTO = new FolderDTO();
        firstFileDTO.setId("File1");
        firstFileDTO.setName("File 1");

        FolderDTO firstFolderDTO = new FolderDTO();
        firstFolderDTO.setId("Folder1");
        firstFolderDTO.setName("Folder 1");

        FolderDTO secondFileDTO = new FolderDTO();
        secondFileDTO.setId("File2");
        secondFileDTO.setName("File 2");

        FolderDTO thirdFileDTO = new FolderDTO();
        thirdFileDTO.setId("File3");
        thirdFileDTO.setName("File 3");

        documents.put(rootFolderDTO.getId(), rootFolderDTO);
        documents.put(firstFileDTO.getId(), firstFileDTO);
        documents.put(firstFolderDTO.getId(), firstFolderDTO);
        documents.put(secondFileDTO.getId(), secondFileDTO);
        documents.put(thirdFileDTO.getId(), thirdFileDTO);

        DocumentChildDTO firstFileChildDTO = new DocumentChildDTO();
        firstFileChildDTO.setName(firstFileDTO.getName());
        firstFileChildDTO.setId(firstFileDTO.getId());
        firstFileChildDTO.setType("file");

        DocumentChildDTO firstFolderChildDTO = new DocumentChildDTO();
        firstFolderChildDTO.setName(firstFolderDTO.getName());
        firstFolderChildDTO.setId(firstFolderDTO.getId());
        firstFolderChildDTO.setType("folder");

        DocumentChildDTO secondFileChildDTO = new DocumentChildDTO();
        secondFileChildDTO.setName(secondFileDTO.getName());
        secondFileChildDTO.setId(secondFileDTO.getId());
        secondFileChildDTO.setType("file");

        DocumentChildDTO thirdFileChildDTO = new DocumentChildDTO();
        thirdFileChildDTO.setName(thirdFileDTO.getName());
        thirdFileChildDTO.setId(thirdFileDTO.getId());
        thirdFileChildDTO.setType("file");


        ArrayList<DocumentChildDTO> children = new ArrayList<>();
        children.add(firstFileChildDTO);
        children.add(firstFolderChildDTO);
        children.add(secondFileChildDTO);


        ArrayList<DocumentChildDTO> children2 = new ArrayList<>();
        children2.add(thirdFileChildDTO);


        rootFolderDTO.setChildren(children);
        firstFileDTO.setChildren(new ArrayList<DocumentChildDTO>());
        firstFolderDTO.setChildren(children2);
        secondFileDTO.setChildren(new ArrayList<DocumentChildDTO>());
        thirdFileDTO.setChildren(new ArrayList<DocumentChildDTO>());


        return documents;
    }


}
