/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package simpleread;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.io.*;
import java.util.*;
import javax.comm.*;
import javax.swing.JFrame;
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

public class SimpleRead_response implements Runnable, SerialPortEventListener  {

    Grafics graf;

    static CommPortIdentifier portId;
    static Enumeration portList;
    static String t;
//    String FILENAME = "binary.dat";
    InputStream source;
    InputStream inputStream;
    SerialPort serialPort;
    Thread readThread;
    ByteArrayInputStream bais;
  //  static int v[]=new int [40];
    JTextArea text= new JTextArea(10,10);
    
//    text.setColumns();

  //  public static void main(String[] args) {




  public static void Start(){
    

    portList = CommPortIdentifier.getPortIdentifiers();

        while (portList.hasMoreElements()) {
            portId = (CommPortIdentifier) portList.nextElement();
            if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
                // // Ja pomenjala zdes'!!
                 if (portId.getName().equals( PortSettings.FindPortIdentification())) {
			//                if (portId.getName().equals("/dev/term/a")) {
                    SimpleRead_response reader = new SimpleRead_response();
                }
            }
        }
    }
    public SimpleRead_response() {
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
   //     finally {return t;}
        
        graf = new Grafics("Helicopters dynamic parameters");
        
        graf.pack();
        RefineryUtilities.centerFrameOnScreen(graf);
        graf.setVisible(true);

        JFrame f = new JFrame("Helicopter dynamic parametres");
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       
    //    JTable table = new JTable(data1, columnNames);
        f.getContentPane().setPreferredSize(new Dimension(1200, 100));
        
          JScrollPane scrollingArea = new JScrollPane(text);
      //    table.setFillsViewportHeight(true);

        //... Get the content pane, set layout, add to center
        JPanel content = new JPanel();
        content.setLayout(new BorderLayout());
        content.add(scrollingArea, BorderLayout.CENTER);

     
        f.getContentPane().add(content,BorderLayout.CENTER);
   


        text.setPreferredSize(new Dimension(1000,100));
        text.append("ID"+"*"+"  DLC"+"*"+"accX"+"*"+"accY"+"*"+"accZ" +"*"+"velZ"+"*"+"posZ"+"*"+"angVelR"
                              +"*"+"angR"+"*"+"angVelP"+"*"+"angP"+"*"
                              +"*"+"angVelY"+"*"+"angY"+"*"+ "temp" +"*"+
                              "airPressure"+"*"+"battery"+"*"+
                              "rpmFront"+"*"+ "rpmLeft"+"*"+"rpmRear"+"*"+"rpmRight"+"*"
                              + "forceTotal"+"*"+"remoteForce"+"*"+"remoteYaw"+"*"+"remotePitch"+"*"
                              +"remoteRoll"+"*"+ "error"+"*"+"crc" +  "\n");
       
        
        
        f.pack();
        f.setLocation(0,00);
        graf.setLocationRelativeTo(f);
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
            int v[]=new int [40];

          
         //  ByteArrayInputStream bais1=new ByteArrayInputStream(readBuffer);
            try {
            DataInputStream dis=new DataInputStream(inputStream);
          
                     byte ID=Objects.id(dis.readByte());
                     byte DLC=Objects.dlc(dis.readByte());

                     char  accXRaw=Objects.accXRaw(dis.readChar());
                     short accX=Objects.accX(dis.readShort());
                     char  accYRaw=Objects.accYRaw(dis.readChar());
                     short accY   = Objects.angY(dis.readShort());
                     char accZRaw=Objects.accZRaw(dis.readChar());
                     short accZ=Objects.accZ(dis.readShort());
                     short velZ=Objects.velZ(dis.readShort());
                     short posZ=Objects.posZ(dis.readShort());
                     char angVelRRaw=Objects.angVelPRaw(dis.readChar());
                     short angVelR=Objects.angVelR(dis.readShort());
                     short angR=Objects.angR(dis.readShort());
                     char  angVelPRaw=Objects.angVelPRaw(dis.readChar());
                     short angVelP=Objects.angVelP(dis.readShort());
                     short angP=Objects.angP(dis.readShort());
                     char  angVelYRaw=Objects.angVelYRaw(dis.readChar());
                     short angVelY=Objects.angVelY(dis.readShort());
                     short angY=Objects.angY(dis.readShort());
                     char  tempRaw=Objects.tempRaw(dis.readChar());
                     int  temp=Objects.temp(dis.readByte());
                     char airPressureRaw=Objects.airPressureRaw(dis.readChar());
                     int   airPressure=Objects.airPressure(dis.readByte());
                     char  batteryRaw=Objects.batteryRaw(dis.readChar());
                     int   battery=Objects.battery(dis.readByte());
                     char  rpmFront=Objects.rpmFront(dis.readChar());
                     char  rpmLeft=Objects.rpmLeft(dis.readChar());
                     char rpmRear=Objects.rpmRear(dis.readChar());
                     char rpmRight=Objects.rpmRight(dis.readChar());
                     char forceTotal=Objects.forceTotal(dis.readChar());
                     int remoteForceRaw=Objects.remoteForceRaw(dis.readByte());
                     char remoteForce=Objects.remoteForce(dis.readChar());
                     int remoteYawRaw=Objects.remoteYawRaw(dis.readByte());
                     char remoteYaw=Objects.remoteYaw(dis.readChar());
                     int   remotePitchRaw=Objects.remotePitchRaw(dis.readByte());
                     char  remotePitch=Objects.remotePitch(dis.readChar());
                     int   remoteRollRaw=Objects.remoteRollRaw(dis.readByte());
                     char remoteRoll=Objects.remoteRoll(dis.readChar());
                     int error=Objects.error(dis.readByte());
                     
                     char crc=Objects.CRC(dis.readChar());
                   


                      graf.setNewData((int)rpmFront,(int)rpmLeft,(int)rpmRear,(int)rpmRight);
                     text.append(ID+"     *"+DLC+"     *"+accX+"     *"+accY+"     *"+accZ + "     *"+velZ+"     *"+posZ
                              +"     *"+angVelR
                              +"       *"+angR+"       *"+angVelP+"       *"+angP+"      *"
                              +angVelY+"     *"+angY+"    *"+temp+"     *"+
                              +airPressure+"     *"+battery+ "     *"
                              + rpmFront+"       *"+ rpmLeft+"      *"+rpmRear+"       *"+rpmRight+"       *"
                              + forceTotal+"       *"+remoteForce+"       *"+remoteYaw+"       *"
                              +remotePitch+"       *"+remoteRoll+"       *"+ error+"       *"+crc +   "\n");
                       

          //  i++;
          //         }

                //value_massiv(v);

               

                dis.close();
                
                //inputStream.reset();
            } catch (IOException e) {System.out.println(e);}
          break;
          
        }
    }






 public static int[] value_massiv (int[] v){

                            return v;

                        }
}