
import java.awt.AWTException;
import java.awt.Robot;
import java.awt.event.KeyEvent;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Nathan
 */
public class Main {

    public static void main(String[] args) throws AWTException {
        Robot r = new Robot();
        while(true) {
            r.keyPress(KeyEvent.VK_A);
        }
    }
}
