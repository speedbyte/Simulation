/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package simpleread;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.io.FileOutputStream;

import javax.swing.*;

/**
 *
 * @author mediamarkt
 */
public  class readfromfile_mod {
public static DataInputStream  inDataStream;
public static int [] v= new int[30];
long de;
static int i=0;
    
                   

    public  int[] readfromfile_mod() throws IOException, UnsupportedOperationException {


        String mas;
        
        i=0;

       
try{
        File inFile= new File("peredacha1.data");
        FileInputStream inFileStream = new FileInputStream(inFile);
        inDataStream = new DataInputStream(inFileStream);
         de=inFile.length()/4;
         System.out.print(Long.toString(de)+" ");

         

                while (i<de){

                   v[i]= inDataStream.readInt();
                   System.out.print(Integer.toString(v[i])+" ");
                   i++;
                  //Start_delay();
                }
       return v;

       /*int i1=inDataStream.readInt();
        int i2=inDataStream.readInt();
        System.out.print(i1);
        System.out.print(i2);*/
    //     System.out.print(new String(readBuffer));
    //    inDataStream.close();

}
   catch (IOException e) {System.out.println(e);}
   finally {
         return v;
    }
    }

 public static int value_massiv (int index){

        return v[index];

     }
     }

