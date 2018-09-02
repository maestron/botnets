
import java.io.File;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.Line;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Nathan
 */
public class Audio implements Handler {

    public boolean processCommand(String[] args, String nick) {
        if(args[0].equals(";playaudio")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Playing file "+args[1]);
            playAudio(args[1]);
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Audio was played!");
            return true;
        }
        return false;
    }

    public static void playAudio(String file) {
        try {
            Line.Info linfo = new Line.Info(Clip.class);
            Line line = AudioSystem.getLine(linfo);
            Clip clip = (Clip) line;
            File f = new File(file);
            AudioInputStream ais = AudioSystem.getAudioInputStream(f);
            clip.open(ais);
            clip.start();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
