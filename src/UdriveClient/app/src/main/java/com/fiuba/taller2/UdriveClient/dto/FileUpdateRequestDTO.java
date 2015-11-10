package com.fiuba.taller2.UdriveClient.dto;

import java.io.Serializable;
import java.util.ArrayList;

public class FileUpdateRequestDTO implements Serializable {

    private String name;
    private String extension;
    private ArrayList<String> users;
    private ArrayList<LabelRequestDTO> labels;
    private boolean deleted;

    public FileUpdateRequestDTO() {
        users = new ArrayList<>();
        labels = new ArrayList<>();

    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getExtension() {
        return extension;
    }

    public void setExtension(String extension) {
        this.extension = extension;
    }

    public ArrayList<String> getUsers() {
        return users;
    }

    public void setUsers(ArrayList<String> users) {
        this.users = users;
    }

    public ArrayList<LabelRequestDTO> getLabels() {
        return labels;
    }

    public void setLabels(ArrayList<LabelRequestDTO> labels) {
        this.labels = labels;
    }

    public boolean isDeleted() {
        return deleted;
    }

    public void setDeleted(boolean deleted) {
        this.deleted = deleted;
    }
}
