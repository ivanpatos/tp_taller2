package com.fiuba.taller2.UdriveClient.dto;

import java.io.Serializable;
import java.util.ArrayList;

/**
 * Created by jscialabba on 29/09/15.
 */
public class DocumentChildResponseDTO implements Serializable {

    private String id;
    private String name;
    private String type;
    private String extension;
    private boolean deleted;
    private String lastModified;
    private String lastUser;
    private ArrayList<LabelDTO> labels;
    private String owner;
    private ArrayList<UserPermissionRequestDTO> users;
    private String version;

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

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getExtension() {
        return extension;
    }

    public void setExtension(String extension) {
        this.extension = extension;
    }

    public boolean getDeleted() {
        return deleted;
    }

    public void setDeleted(boolean deleted) {
        this.deleted = deleted;
    }

    public String getLastModified() {
        return lastModified;
    }

    public void setLastModified(String lastModified) {
        this.lastModified = lastModified;
    }

    public String getLastUser() {
        return lastUser;
    }

    public void setLastUser(String lastUser) {
        this.lastUser = lastUser;
    }

    public ArrayList<LabelDTO> getLabels() {
        return labels;
    }

    public void setLabels(ArrayList<LabelDTO> labels) {
        this.labels = labels;
    }

    public String getOwner() {
        return owner;
    }

    public void setOwner(String owner) {
        this.owner = owner;
    }

    public ArrayList<UserPermissionRequestDTO> getUsers() {
        return users;
    }

    public void setUsers(ArrayList<UserPermissionRequestDTO> users) {
        this.users = users;
    }

    public String getVersion() {
        return version;
    }

    public void setVersion(String version) {
        this.version = version;
    }
}
