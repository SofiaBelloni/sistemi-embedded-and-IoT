package com.company;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.function.Consumer;

public class ConnectionManager extends Thread{
    private final String ADDRESS = "https://a0f92722a02a.ngrok.io/api/data";
    private final String GET_MODE = "{\"command\":\"get_mode\"}";
    private final String GET_ALL_DETECTIONS = "{\"command\":\"get_all_detections\"}";
    private final String GET_LAST_DETECTION = "{\"command\":\"get_last_detection\"}";
    private final String GET_DAM_OPENING = "{\"command\":\"get_dam_opening\"}";
    private Controller controller;
    private boolean stop;

    public ConnectionManager() {
        this.stop = false;
    }

    /**
     * @param controller
     * Set the controller of this connection manager
     */
    public void setController(final Controller controller){
        this.controller = controller;
    }

    /**
     * Stop the thread used to communicate with Dam Service
     */
    public void stopThread(){
        this.stop = true;
    }

    @Override
    public void run() {
        while(!this.stop){
            try {
                sendRequest(GET_MODE, this::parseModeResponse);
                sendRequest(GET_LAST_DETECTION, this::parseLastDetectionResponse);
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * @param message
     * @return HttpRequest
     * Build new HttpRequest based on the given message
     */
    private HttpRequest buildRequest(final String message){
        return HttpRequest.newBuilder(URI.create(ADDRESS))
                .header("Content-Type", "application/json")
                .POST(HttpRequest.BodyPublishers.ofString(message))
                .build();
    }

    /**
     * @param message
     * @param accept
     * Send new HttpClient asynchronous request with message as body
     * When the response is received the Consumer accept is executed
     */
    private void sendRequest(final String message, final Consumer<String> accept){
        this.log("Sending: " + message);
        HttpClient.newHttpClient()
                .sendAsync(buildRequest(message), HttpResponse.BodyHandlers.ofString()) // Define the response body as a string
                .thenApply(HttpResponse::body) // define the argument passed to accept (response body in this case)
                .thenAccept(accept); // Define the method to be executed when the response is received
    }

    /**
     * @param response
     * Parse a response containig last detection
     * If the system state is PREALARM GET_ALL_DETECTIONS request is sent
     * If the state is ALARM GET_ALL_DETECTIONS and GET_DAM_OPENING requests are sent
     */
    private void parseLastDetectionResponse(final String response) {
        this.log("Received: " + response);
        JsonObject jsonObject = new JsonParser().parse(response).getAsJsonObject();
        if (jsonObject.get("state") != null){
            this.controller.setSystemState(jsonObject.get("state").getAsString());
            if(jsonObject.get("state").getAsString().equals("NORMAL")){
                this.controller.resetDetections();
                this.controller.resetDamOpening();
            }
            if(jsonObject.get("state").getAsString().equals("PREALARM")){
                this.controller.resetDamOpening();
                this.sendRequest(GET_ALL_DETECTIONS, this::parseAllDetectionsResponse);
            }
            if(jsonObject.get("state").getAsString().equals("ALARM")){
                this.sendRequest(GET_ALL_DETECTIONS, this::parseAllDetectionsResponse);
                this.sendRequest(GET_DAM_OPENING, this::parseDamOpening);
            }
        }
    }

    /**
     * @param response
     * Parse a response containig dam opening
     */
    private void parseDamOpening(final String response) {
        this.log("Received: " + response);
        JsonObject jsonObject = new JsonParser().parse(response).getAsJsonObject();
        if (jsonObject.get("dam_opening") != null){
            this.controller.setDamOpening(jsonObject.get("dam_opening").getAsInt());
        }
    }

    /**
     * @param response
     * Parse a response containig all detections
     */
    private void parseAllDetectionsResponse(final String response) {
        this.log("Received: " + response);
        this.controller.resetDetections();
        JsonObject jsonObject = new JsonParser().parse(response).getAsJsonObject();
        jsonObject.keySet().forEach(key -> {
            JsonObject detection = jsonObject.get(key).getAsJsonObject();
            this.controller.addDetection(detection.get("time").getAsLong(), detection.get("water_level").getAsFloat());
        });
    }

    /**
     * @param response
     * Parse a response containig system mode
     */
    private void parseModeResponse(final String response){
        this.log("Received: " + response);
        JsonObject jsonObject = new JsonParser().parse(response).getAsJsonObject();
        if (jsonObject.get("mode") != null){
            this.controller.setSystemMode(jsonObject.get("mode").getAsString());
        }
    }

    private void log(final Object text){
        System.out.println(text.toString());
    }
}
