/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package simpleread;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.io.*;
import java.util.*;
import javax.comm.*;
import javax.swing.JEditorPane;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.comm.CommPort;
import javax.swing.text.DefaultCaret;
import org.jfree.ui.RefineryUtilities;
/**
 *
 * @author mediamarkt
 */

public class SimpleRead_parametr_response implements Runnable, SerialPortEventListener  {

    Grafics demo;

    static CommPortIdentifier portId;
    static Enumeration portList;
    static String t;
    String FILENAME = "binary.dat";
    InputStream source;
    InputStream inputStream;
    SerialPort serialPort;
    Thread readThread;
    ByteArrayInputStream bais;
    
    JEditorPane text1= new JEditorPane();
    JEditorPane text2= new JEditorPane();
    static char v[]=new char [17];
    JTextField kpR=new JTextField();
    JTextField kiR=new JTextField();
    JTextField kdR=new JTextField();
    JTextField  kpP=new JTextField();
    
    JTextField kiP=new JTextField();
    JTextField kdP=new JTextField();
    JTextField kpY=new JTextField();

    JTextField kiY=new JTextField();

    JTextField kdY=new JTextField();

    JTextField lpR=new JTextField();
    JTextField hpR=new JTextField();
    JTextField lpP=new JTextField();
    JTextField hpP=new JTextField();
    JTextField inertiaX=new JTextField();
    JTextField inertiaY=new JTextField();
    JTextField inertiaZ=new JTextField();
    JTextField lenBoom=new JTextField();
     


  public static void Start(){
    

    portList = CommPortIdentifier.getPortIdentifiers();

        while (portList.hasMoreElements()) {
            portId = (CommPortIdentifier) portList.nextElement();
            if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
                // // Ja pomenjala zdes'!!
                 if (portId.getName().equals( PortSettings.FindPortIdentification())) {
			//                if (portId.getName().equals("/dev/term/a")) {
                    SimpleRead_parametr_response reader = new SimpleRead_parametr_response();
                }
            }
        }
    }
    public SimpleRead_parametr_response() {
        try {
            serialPort = (SerialPort) portId.open("SimpleReadApp", 2000);
        } catch (PortInUseException e) {System.out.println(e);}
        try {
            inputStream = serialPort.getInputStream();

           // String t = inputStream.toString();


        } catch (IOException e) {System.out.println(e);}

	try {
            serialPort.addEventListener(this);
	} catch (TooManyListenersException e) {System.out.println(e);}
        serialPort.notifyOnDataAvailable(true);
        try {
            serialPort.setSerialPortParams(9600,
                SerialPort.DATABITS_8,
                SerialPort.STOPBITS_1,
                SerialPort.PARITY_NONE);
        } catch (UnsupportedCommOperationException e) {System.out.println(e);}
       // finally {
         //   return inputStream.read() ;
            readThread = new Thread(this);
            readThread.start();

       JFrame f = new JFrame("Helicoper parametrs");
       JPanel center=new JPanel();
       
       
       f.getContentPane().add(center,BorderLayout.CENTER);
       center.setPreferredSize(new Dimension(300, 550));
       center.setLayout(new GridLayout(0,2,10,10));
       center.add(new JLabel("kpR",JLabel.RIGHT));
       center.add(kpR);
       
       center.add(new JLabel("kiR",JLabel.RIGHT));
       center.add(kiR);
       
       center.add(new JLabel("kdR",JLabel.RIGHT));
       center.add(kdR);

       center.add(new JLabel(" kpP",JLabel.RIGHT));
       center.add( kpP);
       center.add(new JLabel("kiP",JLabel.RIGHT));
       center.add(kiP);
       center.add(new JLabel("kdP",JLabel.RIGHT));
       center.add(kdP);
       
       center.add(new JLabel("kpY",JLabel.RIGHT));
       center.add(kpY);
       center.add(new JLabel("kiY",JLabel.RIGHT));
       center.add(kiY);
       center.add(new JLabel("kdY",JLabel.RIGHT));
       center.add(kdY);
       
       center.add(new JLabel("lpR",JLabel.RIGHT));
       center.add(lpR);
       center.add(new JLabel("hpR",JLabel.RIGHT));
       center.add(hpR);
       center.add(new JLabel("lpP",JLabel.RIGHT));
       center.add(lpP);
       
       center.add(new JLabel("hpP",JLabel.RIGHT));
       center.add(hpP);
       center.add(new JLabel("inertiaX",JLabel.RIGHT));
       center.add(inertiaX);
       center.add(new JLabel("inertiaY",JLabel.RIGHT));
       center.add(inertiaY);
       
       center.add(new JLabel("inertiaZ",JLabel.RIGHT));
       center.add(inertiaZ);
       center.add(new JLabel("lenBoom",JLabel.RIGHT));
       center.add(lenBoom);
        f.pack();
        f.setLocation(100,00);
        f.setVisible(true);







    }

    public void run() {
        try {
            Thread.sleep(20000);
        } catch (InterruptedException e) {System.out.println(e);}
    //original
    }


    public void serialEvent(SerialPortEvent event) {

        switch(event.getEventType()) {
        case SerialPortEvent.BI:
        case SerialPortEvent.OE:
        case SerialPortEvent.FE:
        case SerialPortEvent.PE:
        case SerialPortEvent.CD:
        case SerialPortEvent.CTS:
        case SerialPortEvent.DSR:
        case SerialPortEvent.RI:
        case SerialPortEvent.OUTPUT_BUFFER_EMPTY:
            break;
        case SerialPortEvent.DATA_AVAILABLE:
            byte[] readBuffer = new byte[5];
            long schet=0;
            int schet2=0;
            

          
         //  ByteArrayInputStream bais1=new ByteArrayInputStream(readBuffer);
            try {
            DataInputStream dis=new DataInputStream(inputStream);
          
                     byte ID=Objects.id(dis.readByte());
                     byte DLC=Objects.dlc(dis.readByte());

                     char  x_axis_p=Objects.x_axis_p(dis.readChar());
                     char  x_axis_i=Objects.x_axis_i(dis.readChar());
                     char  x_axis_d=Objects.x_axis_d(dis.readChar());
                     char pitch_p=Objects.pitch_p(dis.readChar());
                     char  pitch_i=Objects.pitch_i(dis.readChar());
                     char  pitch_d=Objects.pitch_d(dis.readChar());

                     char yaw_p=Objects.yaw_p(dis.readChar());
                     char yaw_i=Objects.yaw_i(dis.readChar());
                     char  yaw_d=Objects.yaw_d(dis.readChar());

                     char lpRc=Objects.lpR(dis.readChar());
                     char hpRc=Objects.hpR(dis.readChar());
                     char lpPc=Objects.lpP(dis.readChar());
                     char hpPc=Objects.hpP(dis.readChar());


                     char inertiaXc=Objects. inertiaX(dis.readChar());
                     char inertiaYc=Objects. inertiaY(dis.readChar());
                     char inertiaZc=Objects. inertiaZ(dis.readChar());
                     char lenBoomc=Objects.lenBoom(dis.readChar());

                     char crc=Objects.CRC(dis.readChar());

                     
                     kpR.setText(Character.toString(x_axis_p));
                     System.out.print("kpR"+x_axis_p);
                     kiR.setText(Character.toString(x_axis_i));
                     System.out.print("kiR"+x_axis_i);
                     kdR.setText(Character.toString(x_axis_d));
                     System.out.print("kdR"+x_axis_d);

                     kpP.setText(Character.toString(pitch_p));
                     System.out.print("kpP"+pitch_p);
                     kiP.setText(Character.toString(pitch_i));
                     System.out.print("kiP"+pitch_i);
                     kdP.setText(Character.toString(pitch_d));
                     System.out.print("kdP"+pitch_d);

                     kpY.setText(Character.toString(yaw_p));
                     System.out.print("kpY"+yaw_p);
                     kiY.setText(Character.toString(yaw_i));
                     System.out.print("kiY"+yaw_i);
                     kdY.setText(Character.toString( yaw_d));
                     System.out.print("kdY"+yaw_d);

                     lpR.setText(Character.toString(lpRc));
                     System.out.print("lpR"+lpRc);
                     hpR.setText(Character.toString(hpRc));
                     System.out.print("hpR"+hpRc);
                     lpP.setText(Character.toString( lpPc));
                     System.out.print("LpR"+lpPc);

                     hpP.setText(Character.toString(hpPc));
                     System.out.print("hpP"+hpPc);
                     hpR.setText(Character.toString(hpRc));
                     System.out.print("hpR"+hpRc);
                     inertiaX.setText(Character.toString( inertiaXc));
                     System.out.print("inertiaX"+inertiaXc);


                     inertiaY.setText(Character.toString(inertiaYc));
                     System.out.print("inertiaY"+inertiaYc);
                     inertiaZ.setText(Character.toString(inertiaZc));
                     System.out.print("inertiaZ"+inertiaZc);
                     lenBoom.setText(Character.toString( lenBoomc));
                     System.out.print("lenBoom"+lenBoomc);

                dis.close();
                
                //inputStream.reset();
            } catch (IOException e) {System.out.println(e);}
          break;
          
        }
    }






 public static char value_massiv (int index){

                            return v[index];

                        }
}