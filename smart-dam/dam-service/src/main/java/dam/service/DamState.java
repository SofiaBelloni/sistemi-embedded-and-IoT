package dam.service;

public enum DamState {

    NORMAL("NORMAL"), 
    PREALARM("PREALARM"), 
    ALARM("ALARM");

    private String state;

    DamState(String state) {
        this.state = state;
    }

    public String toString() {
        return state;
    }
}
