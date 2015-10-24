package com.fiuba.taller2.UdriveClient.util;

import android.app.Activity;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.DocumentChildResponseDTO;

import java.util.ArrayList;

public class DocumentAdapter extends ArrayAdapter<DocumentChildResponseDTO> {

    Context context;
    int layoutResourceId;
    ArrayList<DocumentChildResponseDTO> data = null;

    public DocumentAdapter(Context context, int layoutResourceId, ArrayList<DocumentChildResponseDTO> data) {
        super(context, layoutResourceId, data);
        this.layoutResourceId = layoutResourceId;
        this.context = context;
        this.data = data;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        View row = convertView;
        DocumentHolder holder;

        if(row == null)
        {
            LayoutInflater inflater = ((Activity)context).getLayoutInflater();
            row = inflater.inflate(layoutResourceId, parent, false);

            holder = new DocumentHolder();
            holder.documentName = (TextView)row.findViewById(R.id.documentName);
            holder.documentType = (ImageView)row.findViewById(R.id.documentType);
            row.setTag(holder);
        }
        else
        {
            holder = (DocumentHolder)row.getTag();
        }

        DocumentChildResponseDTO Document = data.get(position);
        holder.documentName.setText(Document.getName());
        String uri = "drawable/".concat(Document.getType());
        int imageResource = context.getResources().getIdentifier(uri, null, context.getPackageName());
        holder.documentType.setImageResource(imageResource);
        return row;
    }

    static class DocumentHolder
    {
        ImageView documentType;
        TextView documentName;
    }
}

