package it.unibo.dammobileapp.utils;

public class Config {
    public static final String APP_LOG_TAG = "BT CLN";
    public static final String URL = "https://a0f92722a02a.ngrok.io/api/data";

    public class bluetooth {
        public static final int ENABLE_BT_REQUEST = 1;
        public static final String BT_DEVICE_ACTING_AS_SERVER_NAME = "DSD TECH HC-05"; //MODIFICARE QUESTA COSTANTE CON IL NOME DEL DEVICE CHE FUNGE DA SERVER
        public static final String BT_SERVER_UUID = "7ba55836-01eb-11e9-8eb2-f2801f1b9fd1";
    }
}
