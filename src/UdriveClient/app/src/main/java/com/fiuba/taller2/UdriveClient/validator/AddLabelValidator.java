package com.fiuba.taller2.UdriveClient.validator;

import android.content.Context;
import android.widget.Toast;

import com.fiuba.taller2.UdriveClient.R;
import com.fiuba.taller2.UdriveClient.dto.LabelDTO;
import com.fiuba.taller2.UdriveClient.dto.UserPermissionRequestDTO;

import java.util.Collection;

public class AddLabelValidator {
    private Context context;
    Collection<LabelDTO> listLabels;

    public AddLabelValidator(Context context, Collection<LabelDTO> listLabels) {
        this.context = context;
        this.listLabels = listLabels;
    }

    public boolean validate(LabelDTO label) {
        if (!isValidText(label.getDescription())) {
            Toast.makeText(context, context.getString(R.string.label_invalid) , Toast.LENGTH_SHORT).show();
            return false;
        }
        if(existInList(listLabels, label.getDescription())){
            Toast.makeText(context,  context.getString(R.string.label_existent), Toast.LENGTH_SHORT).show();
            return false;
        }
        return true;
    }


    private boolean isValidText(String text) {
        if (text != null && !text.isEmpty())  {
            return true;
        }
        return false;
    }

    private boolean existInList(Collection<LabelDTO> listLabels, String description) {
        for(LabelDTO label : listLabels){
            if(label.getDescription().equals(description)) return true;
        }
        return false;

    }
}