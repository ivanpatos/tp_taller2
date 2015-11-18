package com.fiuba.taller2.UdriveClient.util;

import android.app.Activity;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.VersionDTO;

import java.util.ArrayList;

public class VersionAdapter extends ArrayAdapter<VersionDTO> {

    Context context;
    int layoutResourceId;
    ArrayList<VersionDTO> data = null;

    public VersionAdapter(Context context, int layoutResourceId, ArrayList<VersionDTO> data) {
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
            holder.version = (TextView) row.findViewById(R.id.version);

            row.setTag(holder);
        }
        else
        {
            holder = (UserHolder)row.getTag();
        }

        VersionDTO version = data.get(position);
        holder.version.setText(version.getVersion());
        return row;
    }



    static class UserHolder
    {
        TextView version;
    }
}

