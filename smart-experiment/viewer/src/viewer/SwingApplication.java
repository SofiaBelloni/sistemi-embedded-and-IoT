package viewer;

public class SwingApplication {
    public static void main (String[] args) {
        Viewer viewer = new Viewer();
        SerialManager serialManager = new SerialManager();
        Controller controller = new Controller(serialManager, viewer);
        viewer.setController(controller);
        serialManager.setController(controller);
    }
}
