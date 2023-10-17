package it.unibo.dammobileapp;

import org.json.JSONObject;

public interface HttpCommunication {

    void sendRequest(JSONObject body);
}
