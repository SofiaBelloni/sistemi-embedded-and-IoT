package dam.service;

import jssc.SerialPort;
import jssc.SerialPortList;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

import io.vertx.core.json.JsonObject;

/**
 * This class is used to manage the serial communication between Arduino and the
 * Viewer
 */
public class SerialManager implements Runnable {
    private CommChannel commChannel;
    private Optional<String> serialPort;
    private boolean stopCommunication;
    private Map<String, SerialAction> commandToAction;

    public SerialManager() {
        this.commandToAction = new HashMap<>();
        //arduino dice al server se è in modalità automatica o manuale
        this.commandToAction.put("set_mode", (request) -> {
            Actions.getSingletonInstance().setDamMode(DamMode.valueOf(request.getString("mode")));
            this.sendOK();
        });
        //arduino dice al server la percentuale di apertura della diga
        this.commandToAction.put("set_dam_opening", (request) -> {
            Actions.getSingletonInstance()
                    .setDamOpeningPercentage(request.getFloat("dam_opening"));
            this.sendOK();
        });
        //arduino chiede al server lo stato del sistema (allarme, preallarme, normale)
        this.commandToAction.put("get_last_detection", (request) -> {
            Optional<DataPoint> lastDetection = Actions.getSingletonInstance().getLastDetection();
            if (lastDetection.isEmpty()) {
                this.sendERROR();
            } else {
                new Thread(() -> commChannel.sendMsg(lastDetection.get().getDetectionAsJson())).start();
            }
        });
        this.stopCommunication = false;
        this.serialPort = Optional.empty();
    }

    /**
     * @throws Exception Stop the serial communication
     */
    public synchronized void stopCommunication() throws Exception {
        this.checkSerialPort();
        this.stopCommunication = true;
    }

    /**
     * @throws Exception Send OK to the system
     */
    public synchronized void sendOK() throws Exception {
        this.checkSerialPort();
        new Thread(() -> commChannel.sendMsg("ok")).start();
    }

    /**
     * @throws Exception Send ERROR to the system
     */
    public synchronized void sendERROR() throws Exception {
        this.checkSerialPort();
        new Thread(() -> commChannel.sendMsg("error")).start();
    }

    @Override
    public void run() {
        try {
            String[] portNames = {};
            while (portNames.length == 0) {
                portNames = SerialPortList.getPortNames();
                for (String portName : portNames) {
                    serialPort = Optional.of(portName);
                }
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            this.commChannel = new SerialCommChannel(serialPort.get(), SerialPort.BAUDRATE_115200);
            /* attesa necessaria per fare in modo che Arduino completi il reboot */
            Thread.sleep(4000);
            while (!stopCommunication) {

                String msg = commChannel.receiveMsg();
                System.out.println(msg);

                // la stringa che arriva da arduino è in formato json, la trasformo in oggetto json per poterci lavorare meglio
                JsonObject request = new JsonObject(msg);
                this.commandToAction.get(request.getString("command")).startAction(request);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private synchronized void checkSerialPort() throws Exception {
        if (this.serialPort.isEmpty()) {
            throw new Exception("Device not connected exception");
        }
    }

}
