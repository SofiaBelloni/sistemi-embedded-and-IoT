package dam.service;

import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonObject;
/*
* This interface represents a generic action that can be executed from DataService http commands
* */
public interface HttpAction {
    void startAction(JsonObject msg, HttpServerResponse response);
}
