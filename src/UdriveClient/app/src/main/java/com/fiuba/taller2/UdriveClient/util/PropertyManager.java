package com.fiuba.taller2.UdriveClient.util;

import android.content.Context;
import android.content.res.AssetManager;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class PropertyManager {
    Context context;

    public PropertyManager(Context context) {
        this.context = context;
    }

    public String getProperty(String name){
        Properties props = new Properties();
        String propertyValue = "";
        try {
            AssetManager assetManager = context.getAssets();
            InputStream inputStream = assetManager.open("app.properties");
            props.load(inputStream);
            propertyValue = props.getProperty(name);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return propertyValue;
    }

}
