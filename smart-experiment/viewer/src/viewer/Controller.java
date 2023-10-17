package viewer;

/**
 * This class is used as interface between the logic (SerialManager) and the view of the application
 */
public class Controller {
    private final SerialManager serialManager;
    private final Viewer viewer;

    public Controller(final SerialManager serialManager, final Viewer viewer){
        this.serialManager = serialManager;
        this.viewer = viewer;
        new Thread(serialManager).start();
    }

    /**
     * @param position
     * @param time
     * Draw new value in the position chart
     */
    public void addPositionValue(double position, double time){
        this.viewer.addPositionValue(position, time);
    }

    /**
     * @param speed
     * @param time
     * Draw new value in the speed chart
     */
    public void addSpeedValue(double speed, double time){
        this.viewer.addSpeedValue(speed, time);
    }

    /**
     * @param acceleration
     * @param time
     * Draw new value in the acceleration chart
     */
    public void addAccelerationValue(double acceleration, double time){
        this.viewer.addAccelerationValue(acceleration, time);
    }

    /**
     * Notify to the user that the experiment is started
     */
    public void startExperiment(){
        this.viewer.startExperiment();
    }

    /**
     * @throws Exception
     * Send OK to the system
     */
    public void endExperimentConfirm(){
        try {
            this.serialManager.sendOK();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Notify to the user that the experiment is ended
     */
    public void endExperiment(){
        this.viewer.endExperiment();
    }

    /**
     * Notify to the user that the system is in error
     */
    public void error(){
        this.viewer.error();
    }

    /**
     * Notify to the user that the Viewer is waiting for the experiment
     */
    public void waitForExperiment(){
        this.viewer.waitForExperiment();
    }

    /**
     * Notify to the user that the Viewer is trying to connect with the system
     */
    public void waitForConnection(){
        this.viewer.waitForConnection();
    }

    /**
     * Notify to the user that the system is in sleeping
     */
    public void sleep(){
        this.viewer.sleep();
    }

    /**
     * Notify to the user that the system is calibrating the pir sensor
     */
    public void pirCalibration(){
        this.viewer.pirCalibration();
    }

    /**
     * Notify to the user that the Viewer has received a bad command
     */
    public void commandNotRecognized(String command){
        this.viewer.commandNotRecognized(command);
    }
}
