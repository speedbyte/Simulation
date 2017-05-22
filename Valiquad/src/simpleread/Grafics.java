/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package simpleread;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JPanel;

import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.DateAxis;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.CombinedDomainXYPlot;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.StandardXYItemRenderer;
import org.jfree.data.general.Dataset;
import org.jfree.data.time.Millisecond;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;
import org.jfree.ui.ApplicationFrame;
import org.jfree.ui.RefineryUtilities;
//import org.jfree.ui.Spacer;

/**
 * A demonstration application showing a time series chart where you can dynamically add
 * (random) data by clicking on a button.
 *
 */
public class Grafics extends ApplicationFrame implements ActionListener {

    /** The number of subplots. */
    public static final int SUBPLOT_COUNT = 4;

    /** The datasets. */
    private TimeSeriesCollection[] datasets;

    /** The most recent value added to series 1. */
    private double[] lastValue = new double[SUBPLOT_COUNT];

    /**
     * Constructs a new demonstration application.
     *
     * @param title  the frame title.
     */
    public Grafics(final String title) {

        super(title);
        
        final CombinedDomainXYPlot plot = new CombinedDomainXYPlot(new DateAxis("Time"));
        this.datasets = new TimeSeriesCollection[SUBPLOT_COUNT];

    /*    for (int i = 0; i < SUBPLOT_COUNT; i++) {

            this.lastValue[i] = 100.0;
            final TimeSeries series = new TimeSeries("time " + i, Millisecond.class);
            this.datasets[i] = new TimeSeriesCollection(series);
            final NumberAxis rangeAxis = new NumberAxis("Values" + i);
            rangeAxis.setAutoRangeIncludesZero(false);
            final XYPlot subplot = new XYPlot(
                    this.datasets[i], null, rangeAxis, new StandardXYItemRenderer()
            );*/
            this.lastValue[0] = 100.0;
            final TimeSeries series0 = new TimeSeries("front rotor", Millisecond.class);
            this.datasets[0] = new TimeSeriesCollection(series0);
            final NumberAxis rangeAxis = new NumberAxis("front rotor ");
            rangeAxis.setAutoRangeIncludesZero(false);
            final XYPlot subplot = new XYPlot(
            this.datasets[0], null, rangeAxis, new StandardXYItemRenderer());

            subplot.setBackgroundPaint(Color.lightGray);
            subplot.setDomainGridlinePaint(Color.white);
            subplot.setRangeGridlinePaint(Color.white);
            plot.add(subplot);

            this.lastValue[1] = 100.0;
            final TimeSeries series1 = new TimeSeries("left rotor", Millisecond.class);
            this.datasets[1] = new TimeSeriesCollection(series1);
            final NumberAxis rangeAxis1 = new NumberAxis("left rotor ");
            rangeAxis1.setAutoRangeIncludesZero(false);
            final XYPlot subplot1 = new XYPlot(
            this.datasets[1], null, rangeAxis, new StandardXYItemRenderer());
            subplot1.setBackgroundPaint(Color.lightGray);
            subplot1.setDomainGridlinePaint(Color.white);
            subplot1.setRangeGridlinePaint(Color.white);
            plot.add(subplot1);

            this.lastValue[2] = 100.0;
            final TimeSeries series2 = new TimeSeries("rear rotor", Millisecond.class);
            this.datasets[2] = new TimeSeriesCollection(series2);
            final NumberAxis rangeAxis2 = new NumberAxis("rear rotor ");
            rangeAxis2.setAutoRangeIncludesZero(false);
            final XYPlot subplot2 = new XYPlot(
            this.datasets[2], null, rangeAxis, new StandardXYItemRenderer());
            subplot2.setBackgroundPaint(Color.lightGray);
            subplot2.setDomainGridlinePaint(Color.white);
            subplot2.setRangeGridlinePaint(Color.white);
            plot.add(subplot2);

             this.lastValue[3] = 100.0;
             final TimeSeries series3 = new TimeSeries("right rotor", Millisecond.class);
            this.datasets[3] = new TimeSeriesCollection(series3);
            final NumberAxis rangeAxis3 = new NumberAxis("right rotor ");
            rangeAxis3.setAutoRangeIncludesZero(false);
            final XYPlot subplot3 = new XYPlot(
            this.datasets[3], null, rangeAxis, new StandardXYItemRenderer());
            subplot3.setBackgroundPaint(Color.lightGray);
            subplot3.setDomainGridlinePaint(Color.white);
            subplot3.setRangeGridlinePaint(Color.white);
            plot.add(subplot3);

          


        final JFreeChart chart = new JFreeChart("Systems states", plot);
//        chart.getLegend().setAnchor(Legend.EAST);
        chart.setBorderPaint(Color.black);
        chart.setBorderVisible(true);
        chart.setBackgroundPaint(Color.white);

        plot.setBackgroundPaint(Color.lightGray);
        plot.setDomainGridlinePaint(Color.white);
        plot.setRangeGridlinePaint(Color.white);
  //      plot.setAxisOffset(new Spacer(Spacer.ABSOLUTE, 4, 4, 4, 4));
        final ValueAxis axis = plot.getDomainAxis();
        axis.setAutoRange(true);
        axis.setFixedAutoRange(60000.0);  // 60 seconds

        final JPanel content = new JPanel(new BorderLayout());

        final ChartPanel chartPanel = new ChartPanel(chart);
        content.add(chartPanel);

     final JPanel buttonPanel = new JPanel(new FlowLayout());

    /*    for (int i = 0; i < SUBPLOT_COUNT; i++) {
            final JButton button = new JButton("Series " + i);
            button.setActionCommand("ADD_DATA_" + i);
            button.addActionListener(this);
            buttonPanel.add(button);
        }
        final JButton buttonAll = new JButton("ALL");
        buttonAll.setActionCommand("ADD_ALL");
        buttonAll.addActionListener(this);
        buttonPanel.add(buttonAll);
*/
        content.add(buttonPanel, BorderLayout.SOUTH);
        chartPanel.setPreferredSize(new java.awt.Dimension(500, 470));
        chartPanel.setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5));
        setContentPane(content);

    
    }
    // ****************************************************************************
    // * JFREECHART DEVELOPER GUIDE                                               *
    // * The JFreeChart Developer Guide, written by David Gilbert, is available   *
    // * to purchase from Object Refinery Limited:                                *
    // *                                                                          *
    // * http://www.object-refinery.com/jfreechart/guide.html                     *
    // *                                                                          *
    // * Sales are used to provide funding for the JFreeChart project - please    *
    // * support us so that we can continue developing free software.             *
    // ****************************************************************************

    /**
     * Handles a click on the button by adding new (random) data.
     *
     * @param e  the action event.
     *    */
   public void actionPerformed(final ActionEvent e) {

        for (int i = 0; i < SUBPLOT_COUNT; i++) {
            if (e.getActionCommand().endsWith(String.valueOf(i))) {
                final Millisecond now = new Millisecond();
                System.out.println("Now = " + now.toString());
                this.lastValue[i] = this.lastValue[i] * (0.90 + 0.2 * Math.random());
                this.datasets[i].getSeries(0).add(new Millisecond(), this.lastValue[i]);
            }
        }

        if (e.getActionCommand().equals("ADD_ALL")) {
            final Millisecond now = new Millisecond();
            System.out.println("Now = " + now.toString());
            for (int i = 0; i < SUBPLOT_COUNT; i++) {
                this.lastValue[i] = this.lastValue[i] * (0.90 + 0.2 * Math.random());
                this.datasets[i].getSeries(0).add(new Millisecond(), this.lastValue[i]);
            }
        }
     }
    public void setNewData(int value1,int value2,int value3,int value4)// i-nomer shemi
    {
        this.lastValue[0] = value1;
        this.datasets[0].getSeries(0).add(new Millisecond(), this.lastValue[0]);
        this.lastValue[1] = value2;
        this.datasets[1].getSeries(0).add(new Millisecond(), this.lastValue[1]);
        this.lastValue[2] = value3;
        this.datasets[2].getSeries(0).add(new Millisecond(), this.lastValue[2]);
        this.lastValue[3] = value4;
        this.datasets[3].getSeries(0).add(new Millisecond(), this.lastValue[3]);

    }
}

/**
 *
 * @author mediamarkt
 */