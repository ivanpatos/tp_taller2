package com.fiuba.taller2.UdriveClient.dto;

import java.io.Serializable;
import java.util.ArrayList;

public class FileUpdateRequestDTO implements Serializable {

    private String name;
    private String extension;
    private ArrayList<UserPermissionRequestDTO> users;
    private ArrayList<LabelDTO> labels;
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

    public ArrayList<UserPermissionRequestDTO> getUsers() {
        return users;
    }

    public void setUsers(ArrayList<UserPermissionRequestDTO> users) {
        this.users = users;
    }

    public ArrayList<LabelDTO> getLabels() {
        return labels;
    }

    public void setLabels(ArrayList<LabelDTO> labels) {
        this.labels = labels;
    }

    public boolean isDeleted() {
        return deleted;
    }

    public void setDeleted(boolean deleted) {
        this.deleted = deleted;
    }
}
