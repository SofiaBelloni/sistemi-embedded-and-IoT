package dam.service;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;

public class Main extends AbstractVerticle {

    public static void main(String[] args) {
        Vertx vertx = Vertx.vertx();
        DataService service = new DataService(8080);
        vertx.deployVerticle(service);
        
        //connessione alla seriale di arduino
        new Thread(new SerialManager()).start();

    }

}
