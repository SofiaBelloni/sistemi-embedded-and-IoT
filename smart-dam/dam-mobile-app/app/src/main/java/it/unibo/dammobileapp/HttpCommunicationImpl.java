package it.unibo.dammobileapp;

import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONException;
import org.json.JSONObject;

public class HttpCommunicationImpl implements HttpCommunication {

    private RequestQueue queue;
    private String URL;
    private DamManager damManager;

    public HttpCommunicationImpl(Context context, String URL, DamManager damManager) {
        this.queue = Volley.newRequestQueue(context);
        this.URL = URL;
        this.damManager = damManager;
    }

    /*
    Send Http request
     */
    @Override
    public void sendRequest(JSONObject body) {
        JsonObjectRequest jsonObjectRequest = new JsonObjectRequest(
                Request.Method.POST,
                this.URL,
                body,
                //response listener, this is called when a response is received
                response -> {
                    try {
                        damManager.interpretMessage(response);
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                },
                //error listener, this is called if you receive a response with an error
                error -> Log.e("HttpCommunicationImpl", error.toString()));
        //the request is added in a queue
        this.queue.add(jsonObjectRequest);
    }
}
