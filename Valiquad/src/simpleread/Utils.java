package simpleread;

import java.io.File;
import javax.swing.ImageIcon;

/* Utils.java is used by FileChooserDemo2.java. */
public class Utils {
    

    /*
     * Get the extension of a file.
     */
    public static String getExtension(File f) {
        String ext = null;
        String s = f.getName();
        int i = s.lastIndexOf('.');


        if (i > 0 &&  i < s.length() - 1) {

            ext = s.substring(i+1).toLowerCase();
        }
        return ext;
    }


    public static String getbody(File f) {
        String body = null;
        String s = f.getName();
        int i = s.lastIndexOf('.');
        if (i>0) { return body = s.substring(0,i).toLowerCase();}
        else {return body = s;}
    }
      
}
