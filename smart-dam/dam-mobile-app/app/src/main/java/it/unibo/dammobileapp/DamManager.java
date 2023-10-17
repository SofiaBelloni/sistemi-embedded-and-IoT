package it.unibo.dammobileapp;

import org.json.JSONException;
import org.json.JSONObject;

public interface DamManager {

    void interpretMessage(JSONObject response) throws JSONException;

}
