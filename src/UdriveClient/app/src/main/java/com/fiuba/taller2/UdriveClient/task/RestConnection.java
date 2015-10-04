package com.fiuba.taller2.UdriveClient.task;

import com.fiuba.taller2.UdriveClient.dto.ConnectionDTO;
import com.fiuba.taller2.UdriveClient.exception.ConnectionException;

import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Map;


public class RestConnection {

    JSONObject execute(ConnectionDTO connectionDTO) throws ConnectionException{
        URL url = connectionDTO.getUrl();
        String json = connectionDTO.getJson();
        String requestMethod = connectionDTO.getRequestMethod();
        Map<String, String> attributesHeader = connectionDTO.getAttributesHeader();
        HttpURLConnection conn = null;
        JSONObject response = new JSONObject();
        try {
            conn = (HttpURLConnection) url.openConnection();
            conn.setDoOutput(true);
            conn.setUseCaches(false);
            conn.setRequestMethod(requestMethod);
            for (Map.Entry<String, String> attribute : attributesHeader.entrySet())
            {
                conn.setRequestProperty(attribute.getKey(), attribute.getValue());
            }
            OutputStream os = conn.getOutputStream();
            os.write(json.getBytes("UTF-8"));
            os.close();
            int responseCode = conn.getResponseCode();
            if (responseCode == HttpURLConnection.HTTP_OK) {
                String responseString = readStream(conn.getInputStream());
                response = new JSONObject(responseString);
            }
        }
        catch (Exception ex) {
            throw new ConnectionException(ex.getMessage());
        }
        finally {
            if (conn != null)
                conn.disconnect();
        }
        return response;
    }


    private String readStream(InputStream in) {
        BufferedReader reader = null;
        StringBuffer response = new StringBuffer();
        try {
            reader = new BufferedReader(new InputStreamReader(in));
            String line = "";
            while ((line = reader.readLine()) != null) {
                response.append(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
        return response.toString();
    }
}
