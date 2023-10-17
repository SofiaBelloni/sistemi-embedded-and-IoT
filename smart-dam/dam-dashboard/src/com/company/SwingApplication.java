package com.company;

public class SwingApplication {
    public static void main (String[] args) {
        Viewer viewer = new Viewer();
        ConnectionManager connectionManager = new ConnectionManager();
        new Controller(connectionManager, viewer);
    }
}
