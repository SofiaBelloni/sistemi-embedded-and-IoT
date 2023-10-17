package dam.service;

class DataPoint {
    private double water_level;
    private long time;
    private DamState state;

    public DataPoint(float water_level, long time, DamState state) {
        this.water_level = water_level;
        this.time = time;
        this.state = state;
    }

    public double getWaterLevel() {
        return water_level;
    }

    public long getTime() {
        return time;
    }

    public DamState getState() {
        return state;
    }
    
    public String getDetectionAsJson() {
        return "{\"water_level\":"+ water_level +",\"state\":\""+ state +"\",\"time\":"+ time +"}";
    }
    
}
