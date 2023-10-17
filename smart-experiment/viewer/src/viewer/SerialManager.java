package viewer;

import jssc.SerialPort;
import jssc.SerialPortList;

import java.util.Optional;

/**
 * This class is used to manage the serial communication between Arduino and the Viewer
 */
public class SerialManager implements Runnable{
    private CommChannel commChannel;
    private Optional<String> serialPort;
    private Controller controller;
    private boolean stopCommunication;

    public SerialManager() {
        stopCommunication = false;
        serialPort = Optional.empty();
    }

    /**
     * @param controller
     * Set the controller of the SerialManager
     */
    public void setController(final Controller controller){
        this.controller = controller;
        this.controller.waitForConnection();
    }

    /**
     * @throws Exception
     * Stop the serial communication
     */
    public synchronized void stopCommunication() throws Exception {
        this.checkSerialPort();
        this.stopCommunication = true;
    }

    /**
     * @throws Exception
     * Send OK to the system
     */
    public synchronized void sendOK() throws Exception {
        this.checkSerialPort();
        new Thread(() -> commChannel.sendMsg("ok")).start();
    }

    @Override
    public void run() {
        try {
            String[] portNames = {};
            while (portNames.length == 0){
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
            while (!stopCommunication){
                String msg = commChannel.receiveMsg();
                switch (msg){
                    case "start":
                        this.controller.startExperiment();
                        break;
                    case "end":
                        this.controller.endExperiment();
                        break;
                    case "error":
                        this.controller.error();
                        break;
                    case "wait":
                        this.controller.waitForExperiment();
                        break;
                    case "sleep":
                        this.controller.sleep();
                        break;
                    case "pir":
                        this.controller.pirCalibration();
                        break;
                    default:
                        addValue(msg);
                        break;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private synchronized void checkSerialPort() throws Exception{
        if (this.serialPort.isEmpty()){
            throw new Exception("Device not connected exception");
        }
    }

    private void addValue(String msg) {
        try {
            String[] split = msg.split(";");
            double value = Double.parseDouble(split[0].substring(2));
            double time = Double.parseDouble(split[1].substring(2));
            switch (split[0].substring(0, 2)){
                case "p_":
                    controller.addPositionValue(value, time);
                    break;

                case "s_":
                    controller.addSpeedValue(value, time);
                    break;

                case "a_":
                    controller.addAccelerationValue(value, time);
                    break;

                default:
                    controller.commandNotRecognized(msg);
            }
        }catch (Exception e){
            controller.commandNotRecognized(msg);
        }
    }
}
