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
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.comm.CommPort;
import javax.swing.text.DefaultCaret;
import org.jfree.ui.RefineryUtilities;
/**
 *
 * @author mediamarkt
 */

public class SimpleRead implements Runnable, SerialPortEventListener  {

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
    static int v[]=new int [40];
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
                    SimpleRead reader = new SimpleRead();
                }
            }
        }
    }
    public SimpleRead() {
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

        demo = new Grafics("Dynamic Data Demo");
        demo.pack();
        RefineryUtilities.centerFrameOnScreen(demo);
        demo.setVisible(true);

        JFrame f = new JFrame("Speedoment");
        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        f.getContentPane().setPreferredSize(new Dimension(100, 100));
        
          JScrollPane scrollingArea = new JScrollPane(text);

        //... Get the content pane, set layout, add to center
        JPanel content = new JPanel();
        content.setLayout(new BorderLayout());
        content.add(scrollingArea, BorderLayout.CENTER);

     
        f.getContentPane().add(content,BorderLayout.CENTER);
   


        text.setPreferredSize(new Dimension(100,100));
       
        
        
        f.pack();
        f.setLocation(200,200);
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
          
                     int i=0;
                     byte a=0;
        while (i<5){


                     a=Objects.id(dis.readByte());
                     System.out.print("first"+ a);
                     byte b=Objects.dlc(dis.readByte());
                     System.out.print("second "+ b);
                     byte c=Objects.request(dis.readByte());
                     System.out.print("third"+c);
                     char ch1=Objects.CRC(dis.readChar());


                     int ch=(int)ch1;
                     System.out.print("crc"+ch);
                     

                 //    System.out.print(Integer.toString(v[i])+" ");
                  //   demo.setNewData(v[i]);
                      demo.setNewData(a,b,c,ch);
                      text.append(a+" ");
                       text.append(ch+"\n");


                   /*  if (i==1)
                     {
                         demo.setNewData(v[i]);
                     }
                     */
            i++;
                   }

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