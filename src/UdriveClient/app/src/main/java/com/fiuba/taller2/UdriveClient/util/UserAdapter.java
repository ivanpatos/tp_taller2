package com.fiuba.taller2.UdriveClient.util;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.DocumentChildResponseDTO;
import com.fiuba.taller2.UdriveClient.dto.UserPermissionRequestDTO;

import org.w3c.dom.Text;

import java.util.ArrayList;

public class UserAdapter extends ArrayAdapter<UserPermissionRequestDTO> {

    Context context;
    int layoutResourceId;
    ArrayList<UserPermissionRequestDTO> data = null;

    public UserAdapter(Context context, int layoutResourceId, ArrayList<UserPermissionRequestDTO> data) {
        super(context, layoutResourceId, data);
        this.layoutResourceId = layoutResourceId;
        this.context = context;
        this.data = data;
    }

    @Override
    public View getView(final int position, View convertView, ViewGroup parent) {
        View row = convertView;
        UserHolder holder;

        if(row == null)
        {
            LayoutInflater inflater = ((Activity)context).getLayoutInflater();
            row = inflater.inflate(layoutResourceId, parent, false);

            holder = new UserHolder();
            holder.username = (TextView) row.findViewById(R.id.username);
            holder.deleteBtn = (Button) row.findViewById(R.id.deleteBtn);

            row.setTag(holder);
        }
        else
        {
            holder = (UserHolder)row.getTag();
        }

        UserPermissionRequestDTO document = data.get(position);
        holder.username.setText(document.getUsername());
        holder.deleteBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                data.remove(position);
                notifyDataSetChanged();
            }
        });

        return row;
    }



    static class UserHolder
    {
        TextView username;
        Button deleteBtn;
    }
}

