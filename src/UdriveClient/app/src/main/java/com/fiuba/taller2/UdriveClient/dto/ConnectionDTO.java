package com.fiuba.taller2.UdriveClient.dto;

import java.net.URL;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by jscialabba on 04/10/15.
 */
public class ConnectionDTO {
    URL url;
    String json;
    String requestMethod;
    Map<String, String> attributesHeader;

    public ConnectionDTO() {
        json = "";
        attributesHeader = new HashMap<>();
    }

    public URL getUrl() {
        return url;
    }

    public void setUrl(URL url) {
        this.url = url;
    }

    public String getJson() {
        return json;
    }

    public void setJson(String json) {
        this.json = json;
    }

    public Map<String, String> getAttributesHeader() {
        return attributesHeader;
    }

    public void addAttributeHeader(String key, String value){
        attributesHeader.put(key, value);
    }

    public String getRequestMethod() {
        return requestMethod;
    }

    public void setRequestMethod(String requestMethod) {
        this.requestMethod = requestMethod;
    }
}
