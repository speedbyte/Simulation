/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package simpleread;
import java.io.*;
import java.util.*;
import javax.comm.*;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Enumeration;
import javax.comm.CommPort;
import javax.comm.CommPortIdentifier;
import javax.comm.PortInUseException;
import javax.comm.SerialPort;
import javax.comm.UnsupportedCommOperationException;
import javax.swing.JTextField;
//import simpleread.PortChooser;

/**
 *
 * @author mediamarkt
 */
public class PortSettings {

public static Enumeration portList;
public static DataInputStream dis;
public static CommPortIdentifier portId;
public static String messageString = "Vishal looblut Ninu!\n";
public static SerialPort serialPort;
public static OutputStream outputStream;
public static ByteArrayOutputStream bao;
public static InputStream inputStream;
public static Thread readThread;
/** The chosen Port itself */
 /** The chosen Port Identifier */
public static CommPortIdentifier thePortID;
public static  CommPort thePort;




public static void SimpleWrite () {


    portList = CommPortIdentifier.getPortIdentifiers();

        while (portList.hasMoreElements()) {
            portId = (CommPortIdentifier) portList.nextElement();
            if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
                // Ja pomenjala zdes'!!
                 if (portId.getName().equals(FindPortIdentification())) {
                //if (portId.getName().equals("/dev/term/a")) {
                       try {
                        serialPort = (SerialPort)
                        portId.open("SimpleWriteApp", 2000);
                    } catch (PortInUseException e) {}
                    try {
                        outputStream = serialPort.getOutputStream();
                    } catch (IOException e) {}
                    try {
                        serialPort.setSerialPortParams(9600,
                            SerialPort.DATABITS_8,
                            SerialPort.STOPBITS_1,
                            SerialPort.PARITY_NONE);
                    } catch (UnsupportedCommOperationException e) {}
                    try {
                     DataOutputStream dost=new DataOutputStream(outputStream);
                     File inFile= new File("peredacha.data");

                   
                        long l=inFile.length();
                        dost.writeLong(l);
                       
                        readfromfile_mod posilka = new readfromfile_mod();
                        // inizializazija massiva iz fijla dlja peredachi cherez com port
                        int v []=new int[30];
                        int i=0;
                        v=posilka.readfromfile_mod();
                        int massiv=v.length;

                        while (i<massiv){

                        dost.writeInt(posilka.value_massiv(i));
                       
                        try
                         {
                              Thread.sleep(1000);
                         }
                        catch (InterruptedException ie)
                        {
                              System.out.println(ie.getMessage());
                         }
                        i++;
                        }
                          
                      

                      System.out.print(l);
                   //   System.out.print(in1);
                   //   System.out.print(in2);
                      dost.close();
                    } catch (IOException e) {}
                }
            }        }
    }


public static void SimpleWrite_request (byte Request) {


        byte first_request=0x20;
        byte second_request=0x01;
        byte third_request=Request;
        byte[] message=new byte[3];
        byte[] message_end=new byte[1];
       

        // array formation
        message[0]=first_request;
        message[1]=second_request;
        message[2]=third_request;

        BytesTransformation crc=new BytesTransformation();
        char between;

        System.out.println(message[0]);
        System.out.println(message[1]);
        System.out.println(message[2]);

        between=BytesTransformation.CRC(message);
     //  System.out.println(between);
       //
        // Object message
        Objects.id(first_request);
        System.out.println("First" +Objects.id(first_request));
        Objects.dlc(second_request);
        System.out.println("Second" +Objects.id(second_request));
        Objects.request(Request);
        System.out.println("Third" +Objects.id(third_request));
        Objects.CRC(between);
        System.out.println("CRC" +Objects.CRC(between));

    portList = CommPortIdentifier.getPortIdentifiers();

        while (portList.hasMoreElements()) {
            portId = (CommPortIdentifier) portList.nextElement();
            if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
                // Ja pomenjala zdes'!!
                 if (portId.getName().equals(FindPortIdentification())) {
                //if (portId.getName().equals("/dev/term/a")) {
                       try {
                        serialPort = (SerialPort)
                        portId.open("SimpleWriteApp", 2000);
                    } catch (PortInUseException e) {}
                    try {
                        outputStream = serialPort.getOutputStream();
                    } catch (IOException e) {}
                    try {
                        serialPort.setSerialPortParams(9600,
                            SerialPort.DATABITS_8,
                            SerialPort.STOPBITS_1,
                            SerialPort.PARITY_NONE);
                    } catch (UnsupportedCommOperationException e) {}
                    try {
                     DataOutputStream dost=new DataOutputStream(outputStream);
                     // 5 Bites array

                     dost.writeByte(Objects.id(first_request));
                     System.out.println("First" +Objects.id(first_request));
                     dost.writeByte(Objects.dlc(second_request));
                     System.out.println("Second" +Objects.id(second_request));
                     dost.writeByte(Objects.request(Request));
                     System.out.println("Third" +Objects.id(third_request));
                     dost.writeChar(Objects.CRC(between));
                     System.out.println("CRC" +Objects.CRC(between));

                     dost.close();
                    } catch (IOException e) {}
                }
            }        }
    }

public static void SimpleWrite_update ( char kpR, char kiR, char kdR, char kpP,
        char kiP, char kdP, char kpY, char kiY, char kdY, char lpR, char hpR,
        char lpP, char hpP, char inertiaX, char inertiaY,char inertiaZ, char lenBoom
        ) {


        byte first_request=0x12;
        byte second_request=0x22;


        byte[] message=new byte[36];
        byte[] message_end=new byte[1];


        // array formation
        message[0]=first_request;
        message[1]=second_request;
        byte []kpR_array=BytesTransformation.charToByteArray(kpR);
        message[2]=kpR_array[1];
        message[3]=kpR_array[0];

        byte []kiR_array=BytesTransformation.charToByteArray(kiR);
        message[4]=kiR_array[1];
        message[5]=kiR_array[0];

        byte []kdR_array=BytesTransformation.charToByteArray(kdR);
        message[6]=kdR_array[1];
        message[7]=kdR_array[0];

        byte []kpP_array=BytesTransformation.charToByteArray(kpP);
        message[8]=kpP_array[1];
        message[9]=kpP_array[0];

        byte []kiP_array=BytesTransformation.charToByteArray(kiP);
        message[10]=kiP_array[1];
        message[11]=kiP_array[0];

        byte []kdP_array=BytesTransformation.charToByteArray(kdP);
        message[12]=kdP_array[1];
        message[13]=kdP_array[0];

        byte []kpY_array=BytesTransformation.charToByteArray(kpY);
        message[14]=kpY_array[1];
        message[15]=kpY_array[0];

        byte []kiY_array=BytesTransformation.charToByteArray(kiY);
        message[16]=kiY_array[1];
        message[17]=kiY_array[0];

        byte []kdY_array=BytesTransformation.charToByteArray(kdY);
        message[18]=kdY_array[1];
        message[19]=kdY_array[0];

        byte []lpR_array=BytesTransformation.charToByteArray(lpR);
        message[20]=lpR_array[1];
        message[21]=lpR_array[0];

        byte []hpR_array=BytesTransformation.charToByteArray(hpR);
        message[22]=hpR_array[1];
        message[23]=hpR_array[0];

        byte []lpP_array=BytesTransformation.charToByteArray(lpP);
        message[24]=lpP_array[1];
        message[25]=lpP_array[0];

        byte []hpP_array=BytesTransformation.charToByteArray(hpP);
        message[26]=hpP_array[1];
        message[27]=hpP_array[0];

        byte []inertiaX_array=BytesTransformation.charToByteArray(inertiaX);
        message[28]=inertiaX_array[1];
        message[29]=inertiaX_array[0];

         byte []inertiaY_array=BytesTransformation.charToByteArray(inertiaY);
        message[30]=inertiaY_array[1];
        message[31]=inertiaY_array[0];

        byte []inertiaZ_array=BytesTransformation.charToByteArray(inertiaZ);
        message[32]=inertiaZ_array[1];
        message[33]=inertiaZ_array[0];

        byte []lenBoom_array=BytesTransformation.charToByteArray(lenBoom);
        message[34]=lenBoom_array[1];
        message[35]=lenBoom_array[0];
        BytesTransformation crc=new BytesTransformation();
        char between;

       

        between=BytesTransformation.CRC(message);
     //  System.out.println(between);
       //
        // Object message
       

    portList = CommPortIdentifier.getPortIdentifiers();

        while (portList.hasMoreElements()) {
            portId = (CommPortIdentifier) portList.nextElement();
            if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
                // Ja pomenjala zdes'!!
                 if (portId.getName().equals(FindPortIdentification())) {
                //if (portId.getName().equals("/dev/term/a")) {
                       try {
                        serialPort = (SerialPort)
                        portId.open("SimpleWriteApp", 2000);
                    } catch (PortInUseException e) {}
                    try {
                        outputStream = serialPort.getOutputStream();
                    } catch (IOException e) {}
                    try {
                        serialPort.setSerialPortParams(9600,
                            SerialPort.DATABITS_8,
                            SerialPort.STOPBITS_1,
                            SerialPort.PARITY_NONE);
                    } catch (UnsupportedCommOperationException e) {}
                    try {
                     DataOutputStream dost=new DataOutputStream(outputStream);
                     // Message array

                     dost.writeByte(first_request);
                     System.out.println(first_request);
                     dost.writeByte(second_request);
                     System.out.println("Second" +second_request);
                     dost.writeChar(kpR);
                     dost.writeChar(kiR);
                     dost.writeChar(kdR);
                     dost.writeChar(kpP);
                     dost.writeChar(kiP);
                     dost.writeChar( kdP);
                     dost.writeChar(kpY);
                     dost.writeChar(kiY);
                     dost.writeChar(kdY);
                     dost.writeChar(lpR);
                     dost.writeChar(hpR);
                     dost.writeChar(lpP);
                     dost.writeChar(hpP);
                     dost.writeChar(inertiaX);
                     dost.writeChar(inertiaY);
                     dost.writeChar(inertiaZ);
                     dost.writeChar(lenBoom);

                     dost.writeChar(Objects.CRC(between));
                     System.out.println("CRC" +Objects.CRC(between));

                     dost.close();
                    } catch (IOException e) {}
                }
            }        }
    }


public static void SimpleWrite_Parametr_request () {


        byte first_request=0x10;
        byte second_request=0x00;
        byte[] message=new byte[2];
        byte[] message_end=new byte[1];


        // array formation
        message[0]=first_request;
        message[1]=second_request;


        BytesTransformation crc=new BytesTransformation();
        char between;

        System.out.println(message[0]);
        System.out.println(message[1]);


        between=BytesTransformation.CRC(message);
     //  System.out.println(between);
       //
        // Object message
        Objects.id(first_request);
        System.out.println("First" +Objects.id(first_request));
        Objects.dlc(second_request);
        System.out.println("Second" +Objects.id(second_request));
        Objects.CRC(between);
        System.out.println("CRC" +Objects.CRC(between));

    portList = CommPortIdentifier.getPortIdentifiers();

        while (portList.hasMoreElements()) {
            portId = (CommPortIdentifier) portList.nextElement();
            if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
                // Ja pomenjala zdes'!!
                 if (portId.getName().equals(FindPortIdentification())) {
                //if (portId.getName().equals("/dev/term/a")) {
                       try {
                        serialPort = (SerialPort)
                        portId.open("SimpleWriteApp", 2000);
                    } catch (PortInUseException e) {}
                    try {
                        outputStream = serialPort.getOutputStream();
                    } catch (IOException e) {}
                    try {
                        serialPort.setSerialPortParams(9600,
                            SerialPort.DATABITS_8,
                            SerialPort.STOPBITS_1,
                            SerialPort.PARITY_NONE);
                    } catch (UnsupportedCommOperationException e) {}
                    try {
                     DataOutputStream dost=new DataOutputStream(outputStream);
                     // 5 Bites array

                     dost.writeByte(Objects.id(first_request));
                     System.out.println("First" +Objects.id(first_request));
                     dost.writeByte(Objects.dlc(second_request));
                     System.out.println("Second" +Objects.id(second_request));
                     dost.writeChar(Objects.CRC(between));
                     System.out.println("CRC" +Objects.CRC(between));

                     dost.close();
                    } catch (IOException e) {}
                }
            }        }
    }


public static void SimpleWrite_response () {


        byte ID=0x21;
        byte DLC=0x42;
        char  accXRaw=1;
        short accX=2;
        char  accYRaw=3;
        short accY   = 4;
        char accZRaw=5;
        short accZ=6;
        short velZ=7;
        short posZ=8;
        char angVelRRaw=9;
        short angVelR=10;
        short angR=11;
        char  angVelPRaw=12;
        short angVelP=13;
        short angP=14;
        char  angVelYRaw=15;
        short angVelY=16;
        short angY=17;
        char  tempRaw=18;
        byte  temp=19;
        char airPressureRaw=20;
        byte   airPressure=21;
        char  batteryRaw=22;
        byte   battery=23;
        char  rpmFront=24;
        char  rpmLeft=25;
        char rpmRear=26;
        char rpmRight=27;
        char forceTotal=28;
        byte remoteForceRaw=29;
        char remoteForce=30;
        byte remoteYawRaw=31;
        char remoteYaw=32;
        byte   remotePitchRaw=33;
        char  remotePitch=34;
        byte   remoteRollRaw=35;
        char remoteRoll=36;
        byte error=37;
        char crc=38;





    portList = CommPortIdentifier.getPortIdentifiers();

        while (portList.hasMoreElements()) {
            portId = (CommPortIdentifier) portList.nextElement();
            if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
                // Ja pomenjala zdes'!!
                 if (portId.getName().equals(FindPortIdentification())) {
                //if (portId.getName().equals("/dev/term/a")) {
                       try {
                        serialPort = (SerialPort)
                        portId.open("SimpleWriteApp", 2000);
                    } catch (PortInUseException e) {}
                    try {
                        outputStream = serialPort.getOutputStream();
                    } catch (IOException e) {}
                    try {
                        serialPort.setSerialPortParams(9600,
                            SerialPort.DATABITS_8,
                            SerialPort.STOPBITS_1,
                            SerialPort.PARITY_NONE);
                    } catch (UnsupportedCommOperationException e) {}
                    try {
                     DataOutputStream dost=new DataOutputStream(outputStream);
                     // 5 Bites array
                     dost.writeByte(Objects.id(ID));
                     System.out.println("ID" +Objects.id(ID));
                     dost.writeByte(Objects.dlc(DLC));
                     System.out.println("DLC" +Objects.dlc(DLC));
                     dost.writeChar(Objects.accXRaw(accXRaw));
                     System.out.println("accXRaw" +Objects.accXRaw(accXRaw));
                     dost.writeShort(Objects.accX(accX));
                     System.out.println("accX" +(Objects.accX(accX)));
                     dost.writeChar(Objects.accYRaw(accYRaw));
                     System.out.println("accYRaw" +Objects.accYRaw(accYRaw));
                     dost.writeShort(Objects.accY(accY));
                     System.out.println("accY" +(Objects.accY(accY)));
                     dost.writeChar(Objects.accZRaw(accZRaw));
                     System.out.println("accZRaw" +Objects.accZRaw(accZRaw));
                     dost.writeShort(Objects.accZ(accZ));
                     System.out.println("accZ" +(Objects.accZ(accZ)));
                     dost.writeShort(Objects.velZ(velZ));
                     System.out.println("velZ" +(Objects.velZ(velZ)));
                     dost.writeShort(Objects.posZ(posZ));
                     System.out.println("posZ" +(Objects.posZ(posZ)));
                     dost.writeChar(Objects.angVelRRaw(angVelRRaw));
                     System.out.println("angVelRRaw" +Objects.angVelRRaw(angVelRRaw));
                     dost.writeShort(Objects.angVelR(angVelR));
                     System.out.println("angVelR" +(Objects.angVelR(angVelR)));
                     dost.writeShort(Objects.angR(angR));
                     System.out.println("angR" +(Objects.angR(angR)));

                     dost.writeChar(Objects.angVelPRaw(angVelPRaw));
                     System.out.println("angVelPRaw" +Objects.angVelPRaw(angVelPRaw));
                     dost.writeShort(Objects.angVelR(angVelR));
                     System.out.println("angVelP" +(Objects.angVelP(angVelP)));
                     dost.writeShort(Objects.angP(angP));
                     System.out.println("angP" +(Objects.angP(angP)));

                     dost.writeChar(Objects. angVelYRaw( angVelYRaw));
                     System.out.println(" angVelYRaw" +Objects. angVelYRaw( angVelYRaw));
                     dost.writeShort(Objects.angVelY(angVelY));
                     System.out.println("angVelY" +(Objects.angVelY(angVelY)));
                     dost.writeShort(Objects.angY(angY));
                     System.out.println("angY" +(Objects.angY(angY)));

                     dost.writeChar(Objects.tempRaw( tempRaw));
                     System.out.println(" tempRaw" +Objects. tempRaw(tempRaw));
                     dost.writeByte(Objects.temp(temp));
                     System.out.println(" temp" +Objects. temp(temp));

                     dost.writeChar(Objects.airPressureRaw( airPressureRaw));
                     System.out.println(" airPressureRaw" +Objects. airPressureRaw(airPressureRaw));
                     dost.writeByte(Objects.airPressure(airPressure));
                     System.out.println(" airPressure" +Objects. airPressure(airPressure));

                     dost.writeChar(Objects.batteryRaw( batteryRaw));
                     System.out.println(" batteryRaw" +Objects. batteryRaw(batteryRaw));
                     dost.writeByte(Objects. battery( battery));
                     System.out.println("  battery" +Objects.  battery( battery));

                     dost.writeChar(Objects.rpmFront( rpmFront));
                     System.out.println("rpmFront" +Objects.rpmFront(rpmFront));
                     dost.writeChar(Objects.rpmLeft( rpmLeft));
                     System.out.println(" rpmLeft" +Objects. rpmLeft(rpmLeft));
                     dost.writeChar(Objects.rpmRear( rpmRear));
                     System.out.println("rpmRear" +Objects. rpmRear(rpmRear));
                     dost.writeChar(Objects.rpmRight( rpmRight));
                     System.out.println(" rpmRight" +Objects. rpmRight(rpmRight));

                      dost.writeChar(Objects.forceTotal( forceTotal));
                     System.out.println(" forceTotal" +Objects. forceTotal(forceTotal));
                     dost.writeByte(Objects. remoteForceRaw(remoteForceRaw));
                     System.out.println("  remoteForceRaw" +Objects. remoteForceRaw(remoteForceRaw));

                     dost.writeChar(Objects.remoteForce( remoteForce));
                     System.out.println(" remoteForce" +Objects. remoteForce(remoteForce));
                     dost.writeByte(Objects. remoteYawRaw(remoteYawRaw));
                     System.out.println("remoteYawRaw" +Objects.remoteYawRaw(remoteYawRaw));

                     dost.writeChar(Objects.remoteYaw(remoteYaw));
                     System.out.println("remoteYaw" +Objects.remoteYaw(remoteYaw));
                     dost.writeByte(Objects.  remotePitchRaw( remotePitchRaw));
                     System.out.println(" remotePitchRaw" +Objects. remotePitchRaw( remotePitchRaw));

                     dost.writeChar(Objects.remotePitch(remotePitch));
                     System.out.println("remotePitch" +Objects.remotePitch(remotePitch));
                     dost.writeByte(Objects.  remoteRollRaw( remoteRollRaw));
                     System.out.println(" remoteRollRaw" +Objects. remoteRollRaw(remoteRollRaw));
                     dost.writeChar(Objects.remoteRoll(remoteRoll));
                     System.out.println(" remoteRoll" +Objects. remoteRoll(remoteRoll));
                      dost.writeByte(Objects. error( error));
                     System.out.println(" error" +Objects.error(error));
                     dost.writeChar(Objects.CRC(crc));
                     System.out.println("CRC" +Objects.CRC(crc));
                    

                     dost.close();
                    } catch (IOException e) {}
                }
            }        }
    }



public static String FindPortIdentification(){
/** A mapping from names to CommPortIdentifiers. */
 String t=null;
 HashMap map = new HashMap();
 JTextField newText = new JTextField();
 Enumeration pList = CommPortIdentifier.getPortIdentifiers();
// Process the list, putting serial and parallel into ComboBoxes
       try {
      // while (pList.hasMoreElements()) {
            CommPortIdentifier cpi = (CommPortIdentifier) pList.nextElement();
             System.out.println("Port " + cpi.getName());
         //   map.put(cpi.getName(), cpi);
            if (cpi.getPortType() == CommPortIdentifier.PORT_SERIAL) {

          return t= cpi.getName();
   //   return t;
/*
                serialPortsChoice.setEnabled(true);
                serialPortsChoice.addItem(cpi.getName());*/

       //      System.out.println("Port dfbdfnbdnd:"+cpi.getName());
             //   printout(cpi.getName());
           }else System.out.println("There are no serial Ports on the compute");
       }
   finally {return t;}

}}
   



