/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package simpleread;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import java.awt.event.*;

public class Main {

    public Main() {
  Display display= new Display();
  display.setVisible(true);
        /*   JFrame mainframe = new JFrame("Helicopter");
        CommPortOpen cp = null;
        mainframe.getContentPane().add(new Startpage());
        mainframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        mainframe.pack();
        mainframe.setVisible(true);
       // PropMgr.writeProps();
*/
    }


    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {

            public void run() {
                new Main();
            }
        });
    }


}
