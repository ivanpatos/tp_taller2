package com.fiuba.taller2.UdriveClient.dto;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collection;

public class FolderDTO implements Serializable {

    private String id;
    private String name;
    private ArrayList<DocumentChildDTO> children;


    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public ArrayList<DocumentChildDTO> getChildren() {
        return children;
    }

    public void setChildren(ArrayList<DocumentChildDTO> children) {
        this.children = children;
    }
}
