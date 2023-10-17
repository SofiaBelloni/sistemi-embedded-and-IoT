package it.unibo.dammobileapp;

public enum EnumDamState {

    NORMAL("NORMAL"), 
    PREALARM("PREALARM"), 
    ALARM("ALARM");

    private String state;

    EnumDamState(String state) {
        this.state = state;
    }

    public String toString() {
        return state;
    }
}
