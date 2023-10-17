package dam.service;

import io.vertx.core.json.JsonObject;

public interface SerialAction {
    void startAction(JsonObject request) throws Exception;
}
