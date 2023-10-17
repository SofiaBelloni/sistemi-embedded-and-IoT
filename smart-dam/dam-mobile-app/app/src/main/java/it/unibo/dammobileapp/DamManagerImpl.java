package it.unibo.dammobileapp;

import android.app.Activity;
import android.util.Log;
import android.widget.Switch;
import android.widget.TextView;

import androidx.appcompat.widget.SwitchCompat;

import org.json.JSONException;
import org.json.JSONObject;

public class DamManagerImpl implements DamManager {

    private Activity activity;
    private EnumDamState previousState;

    public DamManagerImpl(Activity activity) {
        this.activity = activity;
        this.previousState = EnumDamState.NORMAL;
    }

    /*
    After you send a request, you receive a response. this method interpret the response.
     */
    public void interpretMessage(JSONObject response) throws JSONException {
        switch (response.keys().next()) {
            case "water_level":
                this.updateState(EnumDamState.valueOf(response.getString("state")), response.getDouble("water_level"));
                break;
            case "dam_opening":
                //if is in ALARM show the dam opening percentage
                if(this.previousState == EnumDamState.ALARM) {
                    ((TextView) this.activity.findViewById(R.id.actualDamOpening)).setText(String.valueOf(response.getDouble("dam_opening"))+" %");
                }
                break;
            default:
                Log.e("DamManagerImpl", "command not recognized");
        }
    }

    private void updateState(EnumDamState newState, double water_level) {

        //write the new state in the TextView
        ((TextView) this.activity.findViewById(R.id.actualState)).setText(newState.toString());

        //if the new state is in ALARM
        if(newState.equals(EnumDamState.ALARM)){
            //enable the switch to switch to manual mode
            this.activity.findViewById(R.id.mode).setEnabled(true);
            //write the water level
            ((TextView) this.activity.findViewById(R.id.actualWaterLevel)).setText(String.valueOf(water_level)+" CM");
        } else {
            //if the previous state was Alarm. now we are not in Alarm
            if(this.previousState.equals(EnumDamState.ALARM)){
                //put the switch in auto mode
                ((SwitchCompat) this.activity.findViewById(R.id.mode)).setChecked(false);
                //disable the switch to switch to manual mode
                this.activity.findViewById(R.id.mode).setEnabled(false);
                //write ND in the actualDamOpening textbox
                ((TextView) this.activity.findViewById(R.id.actualDamOpening)).setText("ND");
            }
            //if the new state is PREALARM
            if (newState.equals(EnumDamState.PREALARM)) {
                //write the water level
                ((TextView) this.activity.findViewById(R.id.actualWaterLevel)).setText(String.valueOf(water_level)+" CM");
            }
            //if the new state is NORMAL
            if (newState.equals(EnumDamState.NORMAL)){
                //write ND in water level
                ((TextView) this.activity.findViewById(R.id.actualWaterLevel)).setText("ND");
            }
        }
        this.previousState = newState;
    }
}
