package com.fiuba.taller2.UdriveClient.dto;

import java.io.Serializable;
import java.util.List;

public class LabelDTO implements Serializable {

    private String description;

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public LabelDTO(String description) {
        this.description = description;
    }

    @Override
    public String toString() {
        return description;
    }
}
