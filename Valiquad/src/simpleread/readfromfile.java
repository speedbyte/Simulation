/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package simpleread;

import java.io.*;
import java.io.FileOutputStream;
import java.util.Vector;



/**
 *
 * @author mediamarkt
 */
public  class readfromfile {
public static DataInputStream  inDataStream;
public static int [] v= new int[30];
public static int [] v1= new int[30];
 static  Vector V1=new Vector();
  static Vector V2= new Vector();
 /*   public static long Dline(File inFile){
    long dlina=0;
    return { dlina=inFile.length();}

}*/
     
    public  int[] readfromfile() throws IOException, UnsupportedOperationException {
        long de=10;
        int i;
        String mas;
      int index=1;
        i=0;
       
try{
        File inFile= new File("peredacha1.data");
        FileInputStream inFileStream = new FileInputStream(inFile);
        inDataStream = new DataInputStream(inFileStream);
         de=inFile.length()/4;
         System.out.print(Long.toString(de)+" ");

         //while (i<de){
         for (i=(index-1)*10;i<(index*10)-1;i++){
         
       //    V1.addElement(inDataStream.readInt());
         v[i]= inDataStream.readInt();
     
     //   System.out.print(Integer.toString(v[i])+" ");
      //    System.out.print(V1.elementAt(i));
     //    System.out.print(Integer.toString(inDataStream.readInt())+"r");
         i++;

      }
    //   return v;
return v;
       /*int i1=inDataStream.readInt();
        int i2=inDataStream.readInt();
        System.out.print(i1);
        System.out.print(i2);*/
    //     System.out.print(new String(readBuffer));
    //    inDataStream.close();

}
   catch (IOException e) {System.out.println(e);}
 /*   finally {
             while (i<10){
         v[i]= inDataStream.readInt();
  //     for (i=1 (i<inFile.length()-15); i++){
         System.out.print(Integer.toString(inDataStream.readInt())+"r");
         System.out.print(Integer.toString(inDataStream.readInt())+"r");
         i++;
      }
         }
*/
finally {
   // System.out.print(new String(" " +v));
    return v;
  // return v;
    
}
    }
    public static Object read_vector(int index)
    {
    return V1.elementAt(index);
    }

 public static int value_massiv (int index){

        return v[index];

     }
     }

