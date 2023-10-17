package com.company;

/**
 * This class is used as interface between the logic (SerialManager) and the view of the application
 */
public class Controller {
    private final ConnectionManager connectionManager;
    private final Viewer viewer;

    public Controller(final ConnectionManager connectionManager, final Viewer viewer){
        this.connectionManager = connectionManager;
        this.viewer = viewer;
        viewer.setController(this);
        connectionManager.setController(this);
        this.connectionManager.start();
    }

    public synchronized void setSystemMode(String systemMode) {
        this.viewer.setSystemMode(systemMode);
    }

    public synchronized void setSystemState(String systemState) {
        this.viewer.setSystemState(systemState);
    }

    public synchronized void setDamOpening(int damOpening) {
        this.viewer.setDamOpening(String.valueOf(damOpening));
    }

    public synchronized void addDetection(long time, float water_level) {
        this.viewer.addDetection(time, water_level);
    }

    public synchronized void resetDetections() {
        this.viewer.resetDetections();
    }
    public synchronized void resetDamOpening(){
        this.viewer.resetDamOpening();
    }
}
