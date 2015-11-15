package com.fiuba.taller2.UdriveClient.dto;

import java.io.Serializable;
import java.util.ArrayList;

public class FolderUpdateRequestDTO implements Serializable {

    private String name;
    private ArrayList<UserPermissionRequestDTO> users;

    public FolderUpdateRequestDTO() {
        users = new ArrayList<>();
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public ArrayList<UserPermissionRequestDTO> getUsers() {
        return users;
    }

    public void setUsers(ArrayList<UserPermissionRequestDTO> users) {
        this.users = users;
    }
}
