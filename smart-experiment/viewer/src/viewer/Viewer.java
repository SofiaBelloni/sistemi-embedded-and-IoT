package viewer;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import javax.swing.*;
import java.awt.*;

/**
 * This class is used to manage the GUI of the program
 */
public class Viewer {
    private JFrame f;
    private JPanel mainPanel;
    private Dimension frameSize;
    private XYSeries positionSeries;
    private XYSeries speedSeries;
    private XYSeries accelerationSeries;
    private Controller controller;
    private JLabel lblCurrentSystemStatus;

    public Viewer(){
        this.setFrame();
        this.createTopPanel();
        this.createCenterPanel();
        f.setVisible(true);
    }

    /**
     * Notify to the user that the experiment is ended
     */
    public void endExperiment(){
        SwingUtilities.invokeLater(() -> {
            JOptionPane.showMessageDialog(f, "Experiment ended");
            lblCurrentSystemStatus.setText("WAITING");
            controller.endExperimentConfirm();
        });
    }

    /**
     * Notify to the user that the system is in error
     */
    public void error(){
        SwingUtilities.invokeLater(() -> lblCurrentSystemStatus.setText("ERROR"));
    }

    /**
     * @param position
     * @param time
     * Draw new value in the position chart
     */
    public void addPositionValue(double position, double time){
        SwingUtilities.invokeLater(() -> positionSeries.add(time, position));
    }

    /**
     * @param speed
     * @param time
     * Draw new value in the speed chart
     */
    public void addSpeedValue(double speed, double time){
        SwingUtilities.invokeLater(() -> speedSeries.add(time, speed));
    }

    /**
     * @param acceleration
     * @param time
     * Draw new value in the acceleration chart
     */
    public void addAccelerationValue(double acceleration, double time){
        SwingUtilities.invokeLater(() -> accelerationSeries.add(time, acceleration));
    }

    /**
     * Notify to the user that the Viewer has received a bad command
     */
    public void commandNotRecognized(String command){
        SwingUtilities.invokeLater(() -> JOptionPane.showMessageDialog(f, "ERROR. Command not recognized: " + command));
    }

    /**
     * Notify to the user that the experiment is started
     */
    public void startExperiment(){
        SwingUtilities.invokeLater(() -> {
            this.positionSeries.clear();
            this.speedSeries.clear();
            this.accelerationSeries.clear();
            lblCurrentSystemStatus.setText("EXPERIMENT STARTED");
        });
    }

    /**
     * Notify to the user that the Viewer is waiting for the experiment
     */
    public void waitForExperiment(){
        SwingUtilities.invokeLater(() -> this.lblCurrentSystemStatus.setText("WAITING"));
    }

    /**
     * Notify to the user that the system is calibrating the pir sensor
     */
    public void pirCalibration(){
        SwingUtilities.invokeLater(() -> this.lblCurrentSystemStatus.setText("PIR CALIBRATION"));

    }

    /**
     * Notify to the user that the Viewer is trying to connect with the system
     */
    public void waitForConnection(){
        SwingUtilities.invokeLater(() -> this.lblCurrentSystemStatus.setText("WAITING FOR CONNECTION"));
    }

    /**
     * Notify to the user that the system is in sleeping
     */
    public void sleep(){
        SwingUtilities.invokeLater(() -> this.lblCurrentSystemStatus.setText("SLEEP"));
    }

    /**
     * @param controller
     * Set the controller of this view
     */
    public void setController(final Controller controller){
        this.controller = controller;
    }

    private void setFrame(){
        f = new JFrame("Experiment Viewer");
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.getContentPane().add(mainPanel);
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        f.setSize((int)(screenSize.width * 0.90), (int)(screenSize.height * 0.90));
        f.setResizable(false);
        this.frameSize = f.getSize();
        mainPanel.setLayout(new BorderLayout(6,6));
    }

    private void createTopPanel(){
        this.lblCurrentSystemStatus = this.buildLabel("");
        JLabel lblSystemStatus = this.buildLabel("System status:");
        JPanel topPanel = new JPanel();
        topPanel.setBackground(Color.DARK_GRAY);
        topPanel.setLayout(new FlowLayout(FlowLayout.LEADING));
        topPanel.add(lblSystemStatus);
        topPanel.add(lblCurrentSystemStatus);
        mainPanel.add(topPanel, BorderLayout.NORTH);
    }

    private void createCenterPanel(){
        XYSeriesCollection positionData = new XYSeriesCollection();
        XYSeriesCollection speedData = new XYSeriesCollection();
        XYSeriesCollection accelerationData = new XYSeriesCollection();
        this.positionSeries = new XYSeries("(Time, Position)");
        this.speedSeries = new XYSeries("(Time, Speed)");
        this.accelerationSeries = new XYSeries("(Time, Acceleration)");
        positionData.addSeries(positionSeries);
        speedData.addSeries(speedSeries);
        accelerationData.addSeries(accelerationSeries);
        JFreeChart positionChart = this.buildChart("Position", positionData);
        JFreeChart speedChart = this.buildChart("Speed", speedData);
        JFreeChart accelerationChart = this.buildChart("Acceleration", accelerationData);

        JPanel centerPanel = new JPanel();
        centerPanel.setBackground(Color.WHITE);
        centerPanel.setLayout(new BoxLayout(centerPanel, BoxLayout.X_AXIS));
        this.addChartPanel(positionChart, centerPanel);
        this.addChartPanel(speedChart, centerPanel);
        this.addChartPanel(accelerationChart, centerPanel);
        mainPanel.add(centerPanel, BorderLayout.CENTER);
    }

    private JLabel buildLabel(final String text){
        JLabel label = new JLabel(text);
        label.setForeground(Color.WHITE);
        label.setFont(new Font(label.getFont().getName(), Font.BOLD, 20));
        return label;
    }

    private JFreeChart buildChart(String title, XYDataset data){
        return ChartFactory.createXYLineChart(
                title,
                "Time",
                title,
                data,
                PlotOrientation.VERTICAL,
                true, true, false);
    }

    private void addChartPanel(JFreeChart chart, JPanel parent){
        Dimension chartDimension = new Dimension((int)this.frameSize.getWidth(), (int)this.frameSize.getHeight()/2);
        ChartPanel chartPanel = new ChartPanel(chart);
        chartPanel.setMaximumSize(chartDimension);
        parent.add(chartPanel);
    }

    {
// GUI initializer generated by IntelliJ IDEA GUI Designer
// >>> IMPORTANT!! <<<
// DO NOT EDIT OR ADD ANY CODE HERE!
        $$$setupUI$$$();
    }

    /**
     * Method generated by IntelliJ IDEA GUI Designer
     * >>> IMPORTANT!! <<<
     * DO NOT edit this method OR call it in your code!
     *
     * @noinspection ALL
     */
    private void $$$setupUI$$$() {
        mainPanel = new JPanel();
        mainPanel.setLayout(new BorderLayout(0, 0));
    }

    /**
     * @noinspection ALL
     */
    public JComponent $$$getRootComponent$$$() {
        return mainPanel;
    }
}
