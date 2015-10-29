package com.fiuba.taller2.UdriveClient.dto;

import java.io.Serializable;
import java.util.ArrayList;

public class FileResponseDTO implements Serializable {

    private String id;
    private String name;
    private ArrayList<DocumentChildResponseDTO> children;


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

    public ArrayList<DocumentChildResponseDTO> getChildren() {
        return children;
    }

    public void setChildren(ArrayList<DocumentChildResponseDTO> children) {
        this.children = children;
    }
}
