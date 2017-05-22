/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package simpleread;

/**
 *
 * @author mediamarkt
 */
public class RequestChooser {

    public static byte RequestChooser() {
    byte bytik;
        return bytik=-1;
    }
    public static byte RequestChooser_100() {
        byte bytik=0xA;
        System.out.println( " Request bite is"+bytik);
        return bytik=0xA;
    }
    public static byte RequestChooser_200() {
        byte bytik;
        return bytik=0x14;
    }
     public static byte RequestChooser_500() {
        byte bytik;
        return bytik=0x32;
    }
    public static byte RequestChooser_1000() {
        byte bytik;
        return bytik=0x64;
    }
     public static byte StopSending() {
        byte bytik;
        return bytik=0x00;
    }
    

    public static Objects messageCollector(byte Request) {
       // Identification
        
        byte first_request=0x20;
        byte second_request=0x01;
        byte third_request=Request;
        byte[] message=new byte[3];
        byte[] message_end=new byte[1];
        Objects mess= new Objects();

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
     

        return mess;
    }
}
