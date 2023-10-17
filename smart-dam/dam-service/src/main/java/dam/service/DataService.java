package dam.service;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Optional;

public class DataService extends AbstractVerticle {

    private int port;
    // This map connects a command to his corresponding action
    private Map<String, HttpAction> commandsToActions;
    

    public DataService(int port) {
        this.port = port;
    }

    @Override
    public void start() {
        this.commandsToActions = new HashMap<>();
        // now it is possible to define the action that correspond to each command (defining the Action.startAction() method body)
        this.commandsToActions.put("add_detection",
                (msg, response) -> {
                    Actions.getSingletonInstance().addDetection(Math.round(msg.getFloat("water_level")), DamState.valueOf(msg.getString("state")), System.currentTimeMillis());
                    response.setStatusCode(200).end();
                });
        this.commandsToActions.put("get_mode",
                (msg, response) -> {
                    Optional<DamMode> damMode = Actions.getSingletonInstance().getMode();
                    if(this.checkOptionalPresence(response, damMode)) {
                        response.send("{\"mode\":\"" + damMode.get().toString() + "\"}");
                    }
                });
        this.commandsToActions.put("get_last_detection",
                (msg, response) -> {
                    Optional<DataPoint> dataPoint = Actions.getSingletonInstance().getLastDetection();
                    if(this.checkOptionalPresence(response, dataPoint)) {
                        response.send(dataPoint.get().getDetectionAsJson());
                    }
                });
        this.commandsToActions.put("get_dam_opening",
                (msg, response) -> {
                    Optional<Float> damOpening = Actions.getSingletonInstance().getDamOpeningPercentage();
                    if(this.checkOptionalPresence(response, damOpening)) {
                        response.send("{\"dam_opening\":" + String.valueOf(damOpening.get()) + "}");
                    }
                });
        this.commandsToActions.put("get_all_detections",
                (msg, response) -> {
                    LinkedList<DataPoint> detections = Actions.getSingletonInstance().getAllDetections();
                    if(detections.isEmpty()) {
                        response.setStatusCode(400).end();
                    } else {
                        response.send(this.getAllDetectionsAsJsonString(detections));
                    }
                });

        // Il router riceve le richieste da un HttpServer
        Router router = Router.router(vertx);
        // BodyHandler legge il corpo del messaggio
        router.route().handler(BodyHandler.create());
        router.post("/api/data").handler(this::handleAddNewData);
        //router.get("/api/data").handler(this::handleGetData);
        vertx
                .createHttpServer()
                .requestHandler(router)
                .listen(port);

        log("Service ready.");
        
    }

    //il router chiama handleAddNewData passandogli la richiesta http ricevuta
    private void handleAddNewData(RoutingContext routingContext) {
        HttpServerResponse response = routingContext.response();
        // log("new msg "+routingContext.getBodyAsString());
        JsonObject res = routingContext.getBodyAsJson();
        if (res == null) {
            response.setStatusCode(200).end();
        } else { //qui ho il body del messaggio come json
            System.out.println("HTTP request: "+res);
            //uso il metodo interpretMessage per capire cosa fare e farlo
            this.interpretMessage(res, response);

        }
    }

    private void log(String msg) {
        System.out.println("[DATA SERVICE] "+msg);
    }
    
    
    private void interpretMessage(JsonObject msg, HttpServerResponse response) {
        this.commandsToActions.get(msg.getString("command")).startAction(msg, response);
    }
    
    //controlla la presenza del valore nel campo opzionale. se viene richiesto un dato che ha un optional vuoto manda una response con codice 400
    private boolean checkOptionalPresence(HttpServerResponse response, Optional<?> opt) {
        if(opt.isEmpty()) {
            response.setStatusCode(400).end();
            return false;
        } 
        return true;
    }
    
    //return a string in json format
    private String getAllDetectionsAsJsonString(LinkedList<DataPoint> detections){

        String json = "{";
        int i=0;
        
        for(DataPoint dp : detections) {
            //singleDetection è un singolo rilevamento in json
            json = json + "\""+i+"\":" + dp.getDetectionAsJson()+",";
            i++;
        }
        //rimuovo l'ultima virgola e ci metto la graffa chiusa
        if(json.endsWith(","))
        {
            json = json.substring(0,json.length() - 1) + "}";
        }
        
        return json;
    }
}