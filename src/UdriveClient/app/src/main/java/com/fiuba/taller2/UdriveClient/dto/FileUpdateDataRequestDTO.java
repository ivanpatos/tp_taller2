package com.fiuba.taller2.UdriveClient.dto;

import java.io.Serializable;
import java.util.ArrayList;

public class FileUpdateDataRequestDTO implements Serializable {

    private String data;


    public String getData() {
        return data;
    }

    public void setData(String data) {
        this.data = data;
    }
}
