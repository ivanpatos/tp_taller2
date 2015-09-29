package com.fiuba.taller2.UdriveClient.dto;

import java.io.Serializable;

/**
 * Created by jscialabba on 29/09/15.
 */
public class DocumentChildDTO implements Serializable {

    private String id;
    private String name;
    private String type;
    private String extension;

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
}
