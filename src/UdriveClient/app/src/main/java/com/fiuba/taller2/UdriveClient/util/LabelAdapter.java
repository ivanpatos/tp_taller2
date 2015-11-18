package com.fiuba.taller2.UdriveClient.util;

import android.app.Activity;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.TextView;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.LabelDTO;
import com.fiuba.taller2.UdriveClient.dto.VersionDTO;

import java.util.ArrayList;

public class LabelAdapter extends ArrayAdapter<LabelDTO> {

    Context context;
    int layoutResourceId;
    ArrayList<LabelDTO> data = null;

    public LabelAdapter(Context context, int layoutResourceId, ArrayList<LabelDTO> data) {
        super(context, layoutResourceId, data);
        this.layoutResourceId = layoutResourceId;
        this.context = context;
        this.data = data;
    }

    @Override
    public View getView(final int position, View convertView, ViewGroup parent) {
        View row = convertView;
        LabelHolder holder;

        if(row == null)
        {
            LayoutInflater inflater = ((Activity)context).getLayoutInflater();
            row = inflater.inflate(layoutResourceId, parent, false);

            holder = new LabelHolder();
            holder.label = (TextView) row.findViewById(R.id.label);
            holder.deleteBtn = (Button) row.findViewById(R.id.deleteBtn);
            row.setTag(holder);
        }
        else
        {
            holder = (LabelHolder)row.getTag();
        }

        LabelDTO label = data.get(position);
        holder.label.setText(label.getDescription());
        holder.deleteBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                data.remove(position);
                notifyDataSetChanged();
            }
        });
        return row;
    }



    static class LabelHolder
    {
        TextView label;
        Button deleteBtn;
    }
}

