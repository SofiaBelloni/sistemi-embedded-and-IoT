package dam.service;

import java.util.LinkedList;
import java.util.Optional;
/*
* This class has all available actions that can be executed in base of received command
* */
public class Actions {

    private static Optional<Actions> instance = Optional.empty();
    
    private static final int MAX_SIZE = 20;
    private final LinkedList<DataPoint> detections;
    private Optional<DamMode> mode;
    private Optional<Float> damOpeningPercentage;
    
    private Actions() {
        this.detections = new LinkedList<>();
        this.mode = Optional.of(DamMode.AUTO);
        this.damOpeningPercentage = Optional.of((float)0);
    }
    
    public static synchronized Actions getSingletonInstance() {
        if(instance.isEmpty()) {
            instance = Optional.of(new Actions());
        }
        return instance.get(); 
    }
    
    
    //set the dam mode (AUTO or MANUAL)
    public synchronized void setDamMode(final DamMode mode) {
        this.mode = Optional.of(mode);
        
    }

    //set the dam mode to AUTO
    public synchronized void setDamAuto() {
        this.mode = Optional.of(DamMode.AUTO);
        
    }

    //set the dam mode to MANUAL
    public synchronized void setDamManual() {
        this.mode = Optional.of(DamMode.MANUAL);
        
    }

    //set the dam opening percentage
    public synchronized void setDamOpeningPercentage(final float percentage) {
        this.damOpeningPercentage = Optional.of(percentage);
        
    }

    //return normal, prealarm, alarm
    public synchronized Optional<DamState> getDamState(){
        return Optional.of(this.getLastDetection().get().getState());
    }

    //add a detection
    public synchronized void addDetection(final float waterLevel, final DamState state, final long time) {
        this.detections.addFirst(new DataPoint(waterLevel, time, state));
        if (this.detections.size() > MAX_SIZE) {
            this.detections.removeLast();
        }
    }

    //add a detection
    public synchronized void addDetection(final DataPoint detection) {
        this.detections.addFirst(detection);
        if (this.detections.size() > MAX_SIZE) {
            this.detections.removeLast();
        }
    }

    //return the last detection
    public synchronized Optional<DataPoint> getLastDetection(){
        return Optional.of(this.detections.getFirst());
    }

    //return all detections
    public synchronized LinkedList<DataPoint> getAllDetections() {
        return this.detections;
    }

    //return the opening percentage of the dam 
    public synchronized Optional<Float> getDamOpeningPercentage(){
        return this.damOpeningPercentage;
    }

    //return the current control mode (auto or manual) 
    public synchronized Optional<DamMode> getMode(){
        return this.mode;
    }

}
