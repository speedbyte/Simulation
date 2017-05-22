/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package simpleread;

import java.io.*;
import java.io.FileOutputStream;

/**
 *
 * @author mediamarkt
 */
public class writetofile {

    public writetofile() throws IOException, UnsupportedOperationException {
int i;

        try{
        File outFile= new File("peredacha1.data");
        FileOutputStream outFileStream = new FileOutputStream(outFile);

        DataOutputStream outDataStream = new DataOutputStream(outFileStream);
            int k=0;
          //  long ch= outFile.length()/4;

       for (i=0; i<30; i++){
            k=i*2;
         outDataStream.writeInt(k);
         //outDataStream.writeInt(56);
         
      //   String k = Integer.toString(i);
        System.out.print(new String(" "+k));
     //   }
         }
      outDataStream.close();   }
catch (IOException e) {System.out.println(e);}



    }


     }

