package com.mcs.robot;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatDialogFragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Spinner;

import java.util.ArrayList;
import java.util.List;

public class AddSound extends AppCompatDialogFragment implements View.OnClickListener {

    private List choice;
    private NewSound NewSound;

    public void setCallback(NewSound NewSound) {
        this.NewSound = NewSound;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        final View layout = inflater.inflate(R.layout.fragment_addannonce, container, false);
        getDialog().setCanceledOnTouchOutside(false);
        choice = new ArrayList();
        getDialog().setTitle(R.string.TitreDuDialogSoundAnnonce);
        choice.add(TypeAction.ARRETE_TOI.toString());
        choice.add(TypeAction.ATTERISSAGE.toString());
        choice.add(TypeAction.AVANCE.toString());
        choice.add(TypeAction.DECOLLAGE.toString());
        choice.add(TypeAction.DROITE.toString());
        choice.add(TypeAction.ETAT_URGENCE.toString());
        choice.add(TypeAction.FLIP.toString());
        choice.add(TypeAction.GAUCHE.toString());
        choice.add(TypeAction.PLUS_BAS.toString());
        choice.add(TypeAction.PLUS_HAUT.toString());
        choice.add(TypeAction.RECULE.toString());
        choice.add(TypeAction.TOURNE_DROITE.toString());
        choice.add(TypeAction.TOURNE_GAUCHE.toString());

        ArrayAdapter adapter = new ArrayAdapter(getContext(), android.R.layout.simple_spinner_item, choice);
        adapter.setDropDownViewResource(R.layout.support_simple_spinner_dropdown_item);
        ((Spinner) layout.findViewById(R.id.spinner)).setAdapter(adapter);
        layout.findViewById(R.id.btnValidate).setOnClickListener(this);
        layout.findViewById(R.id.btnCancel).setOnClickListener(this);
        return layout;
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btnCancel: {
                dismiss();
                break;
            }
            case R.id.btnValidate: {
                String tmp = (String) ((Spinner) getView().findViewById(R.id.spinner)).getSelectedItem();
                NewSound.itemWasCreated(convertToTypeAction(tmp));
                dismiss();
                break;
            }
        }
    }

    private TypeAction convertToTypeAction(String action) {
        if (action.equals(TypeAction.ARRETE_TOI.toString()))
            return TypeAction.ARRETE_TOI;
        if (action.equals(TypeAction.ATTERISSAGE.toString()))
            return TypeAction.ATTERISSAGE;
        if (action.equals(TypeAction.AVANCE.toString()))
            return TypeAction.AVANCE;
        if (action.equals(TypeAction.DECOLLAGE.toString()))
            return TypeAction.DECOLLAGE;
        if (action.equals(TypeAction.DROITE.toString()))
            return TypeAction.DROITE;
        if (action.equals(TypeAction.ETAT_URGENCE.toString()))
            return TypeAction.ETAT_URGENCE;
        if (action.equals(TypeAction.FLIP.toString()))
            return TypeAction.FLIP;
        if (action.equals(TypeAction.GAUCHE.toString()))
            return TypeAction.GAUCHE;
        if (action.equals(TypeAction.PLUS_BAS.toString()))
            return TypeAction.PLUS_BAS;
        if (action.equals(TypeAction.PLUS_HAUT.toString()))
            return TypeAction.PLUS_HAUT;
        if (action.equals(TypeAction.RECULE.toString()))
            return TypeAction.RECULE;
        if (action.equals(TypeAction.TOURNE_DROITE.toString()))
            return TypeAction.TOURNE_DROITE;
        else
            return TypeAction.TOURNE_GAUCHE;
    }

    public interface NewSound {
        void itemWasCreated(TypeAction action);
    }
}
