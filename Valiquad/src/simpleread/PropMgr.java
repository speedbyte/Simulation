/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package simpleread;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Properties;

/**
 *
 * @author adr
 */
public class PropMgr {

public static Properties defaultProps = new Properties();
//public static Properties applicationProps = new Properties(defaultProps);

    //  create and load default properties
    public static void defaultPropswrite() {
    
   	try {
            FileOutputStream out = new FileOutputStream("defaultProps2");
            
            defaultProps.setProperty("x_axis_p", "15");
            defaultProps.setProperty("x_axis_i", "15");
            defaultProps.setProperty("x_axis_d", "15");
            defaultProps.setProperty("pitch_p", "15");
            defaultProps.setProperty("pitch_i", "15");
            defaultProps.setProperty("pitch_d", "15");
            defaultProps.setProperty("yaw_p", "15");
            defaultProps.setProperty("yaw_i", "15");
            defaultProps.setProperty("yaw_d", "15");
            defaultProps.setProperty("lpR", "15");
            defaultProps.setProperty("lpP", "15");
            defaultProps.setProperty("hpP", "15");
            defaultProps.setProperty("inertiaX", "15");
            defaultProps.setProperty("inertiaY", "15");
            defaultProps.setProperty("inertiaZ", "15");
            defaultProps.setProperty("lenBoom", "15");

            defaultProps.store(out, "Default Properties have been stored");
            out.close();
          //  FileInputStream in = new FileInputStream("defaultProps");
           // defaultProps.load(in);
          //  in.close();
	} catch (Exception e) {
	  }
    }

    public static String  defaultPropsread(String t) {
	//Properties defaultProps = new Properties();
	try {
	    FileInputStream in = new FileInputStream("defaultProps2");
	    defaultProps.load(in);
	    in.close();
	/*    if (defaultProps.containsKey("height.d")) {
	   System.out.println("found height.d" + defaultProps.getProperty("height.d"));
	    }*/
	} catch (Exception e) {
	}
        finally {

         return defaultProps.getProperty(t);
         }


}
    /*public static String read(String k){
        String t;
    return t="bsdbsbs"+k;}
*/
public static String readProps(String otkuda,String t) {
	Properties applicationProps = new Properties(defaultProps);
	 String k;
        try {
	    FileInputStream in = new FileInputStream(otkuda);
	    applicationProps.load(in);
	    in.close();
	  //  if (applicationProps.containsKey(t)) {
	//	 System.out.println("found t" + applicationProps.getProperty(t));
              //  return k = applicationProps.getProperty("t");
	    //}
	} catch (Exception e) {
	}
         finally {
             
         return applicationProps.getProperty(t);
         }
         





}

public static void writeProps(String kuda,String xp,String xi,String
        xd, String pp,String pi,String pd,String yp, String yi,String yd,
        String lpR,String lpP,String hpP,String inertiaX,String inertiaY,String inertiaZ,String lenBoom)
                {
	Properties applicationProps = new Properties();
        int k=12;
        String p;
 //       String[] massive = new String []{"12","13","14","15","16"};
        try {
	    FileOutputStream out = new FileOutputStream(kuda);
	//    while (k>0) {
     
            applicationProps.setProperty("lpR", lpR);
//	    massive[1]= applicationProps.getProperty("height.p");
            applicationProps.setProperty("lpP", lpP);
      //      massive[2]= applicationProps.getProperty("height.i");
	    applicationProps.setProperty("hpP", hpP);
            
            applicationProps.setProperty("inertiaX", inertiaX);
            applicationProps.setProperty("inertiaY", inertiaY);
            applicationProps.setProperty("inertiaZ", inertiaZ);
            applicationProps.setProperty("lenBoom", lenBoom);



            applicationProps.setProperty("x_axis_p", xp);
            applicationProps.setProperty("x_axis_i", xi);
            applicationProps.setProperty("x_axis_d", xd);
            applicationProps.setProperty("pitch_p", pp);
            applicationProps.setProperty("pitch_i", pi);
            applicationProps.setProperty("pitch_d", pd);
            applicationProps.setProperty ("yaw_p", yp);
            applicationProps.setProperty("yaw_i", yi);
            applicationProps.setProperty("yaw_d", yd);
    //        k= k--;}
	    applicationProps.store(out, "Properties have been stored");
            System.out.println("Properties have been stored");
	//    System.exit();
            out.close();

        } catch (Exception e) {
	}
}


/* public static void writePropssingle(String kuda,String hp) {

  	Properties applicationProps = new Properties();
        String p;
 //       String[] massive = new String []{"12","13","14","15","16"};
        try {
	    FileOutputStream out = new FileOutputStream(kuda);
	//    while (k>0) {

            applicationProps.setProperty("height_p", hp);
//
    //        k= k--;}
	    applicationProps.store(out, "Properties have been stored");
            System.out.println("Properties have been stored");
	//    System.exit();
            out.close();

        } catch (Exception e) {
	}

  /*      finally {

            return t;*/



}
