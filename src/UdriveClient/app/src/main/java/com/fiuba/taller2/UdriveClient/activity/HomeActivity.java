package com.fiuba.taller2.UdriveClient.activity;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.Toast;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.DocumentChildDTO;
import com.fiuba.taller2.UdriveClient.dto.DocumentDTO;
import com.fiuba.taller2.UdriveClient.util.DocumentAdapter;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class HomeActivity extends AppCompatActivity {

    private Map<String, DocumentDTO> documents;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home);
        initViewList();

    }

    private void initViewList(){
       /* SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        String username = sharedPreferences.getString("username", "null");
        String token = sharedPreferences.getString("token", "null");
        Log.d("Username", username);
        Log.d("Token", token);
*/
        Bundle extras = getIntent().getExtras();
        DocumentDTO documentDTO = null;
        documents = getDocuments();
        if (extras != null) {
            documentDTO = (DocumentDTO) extras.get("document");
        } else {

            documentDTO = documents.get("F0");
        }
        setTitle(documentDTO.getName());

        final ArrayList<DocumentChildDTO> documentChildDTOs = documentDTO.getChildren();

        final DocumentAdapter adapter = new DocumentAdapter(this,
                R.layout.listview_item_document, documentChildDTOs);

        ListView documentList = (ListView) findViewById(R.id.documentList);

        documentList.setAdapter(adapter);
        documentList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            public void onItemClick(AdapterView<?> arg0, View v, int position, long arg3) {
                DocumentChildDTO documentChildSelected = documentChildDTOs.get(position);
                if(documentChildSelected.getType().equals("folder")){
                    DocumentDTO currentDocument = documents.get(documentChildSelected.getId());
                    Intent intent = new Intent(getApplicationContext(), HomeActivity.class);
                    intent.putExtra("document", currentDocument);
                    startActivity(intent);
                    overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);
                }else{
                    Toast.makeText(getApplicationContext(), "Abro el archivo", Toast.LENGTH_SHORT).show();
                }
            }
        });
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

    private Map<String, DocumentDTO> getDocuments() {
        documents = new HashMap<>();

        DocumentDTO rootFolderDTO = new DocumentDTO();
        rootFolderDTO.setId("F0");
        rootFolderDTO.setName("Principal");

        DocumentDTO firstFileDTO = new DocumentDTO();
        firstFileDTO.setId("File1");
        firstFileDTO.setName("File 1");

        DocumentDTO firstFolderDTO = new DocumentDTO();
        firstFolderDTO.setId("Folder1");
        firstFolderDTO.setName("Folder 1");

        DocumentDTO secondFileDTO = new DocumentDTO();
        secondFileDTO.setId("File2");
        secondFileDTO.setName("File 2");

        DocumentDTO thirdFileDTO = new DocumentDTO();
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
