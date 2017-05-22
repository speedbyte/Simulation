                                                                                                                                                                                                    /*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package simpleread;

/**
 *
 * @author mediamarkt
 */
public class BytesTransformation {

    public static int UnsignedbyteToInt (byte first){
        short anUnsignedByte = 0;
	int firstByte = 0;
     
        return firstByte = (0x000000FF & ((int)first));
	
     }

    static byte [] charToByteArray( char c )
   {
      byte [] twoBytes = { (byte)(c & 0xff), (byte)(c >> 8 & 0xff) };
      return twoBytes;
   }


    public static byte[] toBytes(char s)
    {
        return new byte[]{
            (byte)(s & 0x00FF),(byte)((s & 0xFF00)>>8)};
    }

    /*  public static byte[] ToByta (short data) {
	return new byte[]{
		(byte)(data & 0xff),
		(byte)((data >>> 8) & 0xff)
	};
}
*/
public static char CRC(byte []bytes) {
        char myChar;
        int crc = 0xFFFF;          // initial value
        int polynomial =0xA001;

        // byte[] testBytes = "123456789".getBytes("ASCII");

            for (byte b : bytes) {
            for (int i = 0; i < 8; i++) {
                boolean bit = ((b   >> (7-i) & 1) == 1);
                boolean c15 = ((crc >> 15    & 1) == 1);
                crc <<= 1;
                if (c15 ^ bit) crc ^= polynomial;
             }
        }

        crc &= 0xffff;
   System.out.println("CRC16-CCITT = " + Integer.toHexString(crc));

    return  myChar = (char)crc;

      //  System.out.println("CRC16-CCITT = " + myChar);
    }

    public static int BytesTransformation(byte first, byte second ) {
        short anUnsignedByte = 0;
	char anUnsignedShort = 0;
//	long anUnsignedInt = 0;

        int firstByte = 0;
        int secondByte = 0;
       	int index = 0;
        int vtoroj=0;
        firstByte = (0x000000FF & ((int)first));
	index++;
//	System.out.print("firstByte"+first+" ");
        secondByte = (0x000000FF & ((int)second));

   //     System.out.print("secondByteb"+secondByte+" ");

	index = index+2;
	anUnsignedShort  = (char) (firstByte << 8 | secondByte);
  //      System.out.print("anUnsignedShort" +anUnsignedShort+" ");

        vtoroj =(int)(anUnsignedShort);
     //   System.out.print("vtoroj" +vtoroj+" ");
        return vtoroj;
    }


 
}










