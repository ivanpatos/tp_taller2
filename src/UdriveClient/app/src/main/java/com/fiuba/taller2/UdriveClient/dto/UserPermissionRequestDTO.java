package com.fiuba.taller2.UdriveClient.dto;

import java.io.Serializable;

public class UserPermissionRequestDTO implements Serializable {

    private String username;

    public UserPermissionRequestDTO(String username) {
        this.username = username;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    @Override
    public String toString() {
        return username;
    }
}
