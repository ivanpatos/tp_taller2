package com.fiuba.taller2.UdriveClient.dto;

import java.io.Serializable;
import java.util.ArrayList;

public class FolderUpdateRequestDTO implements Serializable {

    private String name;
    private ArrayList<String> users;

    public FolderUpdateRequestDTO() {
        users = new ArrayList<>();
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public ArrayList<String> getUsers() {
        return users;
    }

    public void setUsers(ArrayList<String> users) {
        this.users = users;
    }
}
