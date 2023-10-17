package com.company;

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
    private XYSeries waterLevelSeries;
    private Controller controller;
    private JLabel lblCurrentMode;
    private JLabel lblCurrentState;
    private JLabel lblDamOpening;
    
    

    public Viewer(){
        this.setFrame();
        this.createLeftPanel();
        this.createCenterPanel();
        f.setVisible(true);
    }

    /**
     * @param controller
     * Set the controller of this view
     */
    public void setController(final Controller controller){
        this.controller = controller;
    }

    /**
     * @param systemMode
     * Set the system mode
     */
    public void setSystemMode(String systemMode) {
        this.lblCurrentMode.setText(systemMode);
    }

    /**
     * @param damOpening
     * Set dam opening
     */
    public void setDamOpening(String damOpening) {
        this.lblDamOpening.setText(damOpening);
    }

    /**
     * @param systemState
     * Set system state
     */
    public void setSystemState(String systemState) {
        this.lblCurrentState.setText(systemState);
    }

    /**
     * @param time
     * @param water_level
     * Add new detection to the graph
     */
    public void addDetection(long time, float water_level) {
        this.waterLevelSeries.add(time, water_level);
    }

    /**
     * Clear the graph
     */
    public void resetDetections() {
        this.waterLevelSeries.clear();
    }

    /**
     * Reset dam opening value
     */
    public void resetDamOpening(){
        this.lblDamOpening.setText("NULL");
    }

    private void setFrame(){
        f = new JFrame("Dam Dashboard");
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.getContentPane().add(mainPanel);
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        f.setSize((int)(screenSize.width * 0.90), (int)(screenSize.height * 0.90));
        f.setResizable(false);
        this.frameSize = f.getSize();
        mainPanel.setLayout(new BorderLayout(6,6));
    }

    private void createLeftPanel(){
        JPanel leftPanel = new JPanel();
        leftPanel.setBackground(Color.DARK_GRAY);
        leftPanel.setLayout(new BoxLayout (leftPanel, BoxLayout.Y_AXIS));
        this.lblCurrentMode = this.buildLabel("NULL");
        this.lblCurrentState = this.buildLabel("NULL");
        this.lblDamOpening = this.buildLabel("NULL");
        leftPanel.add(this.createHBox(this.buildLabel("System mode:"), lblCurrentMode));
        leftPanel.add(this.createHBox(this.buildLabel("System state:"), lblCurrentState));
        leftPanel.add(this.createHBox(this.buildLabel("Dam opening:"), lblDamOpening));
        mainPanel.add(leftPanel, BorderLayout.WEST);
    }
    
    private JPanel createHBox(JLabel label1, JLabel label2){
        JPanel panel = new JPanel();
        panel.setAlignmentX(0);
        panel.setBackground(Color.DARK_GRAY);
        panel.setBorder(BorderFactory.createEmptyBorder(10,10,10,10));
        panel.setLayout(new BoxLayout (panel, BoxLayout.X_AXIS));
        panel.add(label1);
        panel.add(label2);
        return panel;
    }

    private void createCenterPanel(){
        XYSeriesCollection waterLevelData = new XYSeriesCollection();
        this.waterLevelSeries = new XYSeries("(Time, Water Level)");
        waterLevelData.addSeries(waterLevelSeries);
        JFreeChart waterLevelChart = this.buildChart("Water Level", waterLevelData);

        JPanel centerPanel = new JPanel();
        centerPanel.setBorder(BorderFactory.createEmptyBorder(10,10,10,10));
        centerPanel.setBackground(Color.WHITE);
        centerPanel.setLayout(new BoxLayout(centerPanel, BoxLayout.X_AXIS));
        this.addChartPanel(waterLevelChart, centerPanel);
        mainPanel.add(centerPanel, BorderLayout.CENTER);
    }

    private JLabel buildLabel(final String text){
        JLabel label = new JLabel(text);
        label.setForeground(Color.WHITE);
        label.setFont(new Font(label.getFont().getName(), Font.BOLD, 18));
        return label;
    }

    private JFreeChart buildChart(String title, XYDataset data){
        return ChartFactory.createXYLineChart(
                title,
                "Time (timestamp)",
                "Water Level (cm)",
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
