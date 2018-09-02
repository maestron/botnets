
import java.io.IOException;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.text.SimpleDateFormat;
import java.util.Date;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Nathan
 */
public class RsVersionChecker implements Handler {

    public boolean processCommand(String[] args, String nick) {
        if(args[0].equals(";rsversion")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Getting current RS revision!");
            try {
                getRevision();
                return true;
            } catch(IOException e) {
                return false;
            }
        }
        return true;
    }

    private int findRS2Revision() throws IOException {
        int clientNo = 539;
        boolean success = false;
        ByteBuffer out = ByteBuffer.allocate(5);
        while (!success) {
            Socket socket = new Socket("world119.runescape.com", 43594);
            out.put((byte) 15);
            out.putInt(clientNo);
            socket.getOutputStream().write(out.array(), 0, 5);
            int rsp = socket.getInputStream().read();
            if (rsp == 0) {
                success = true;
            } else {
                socket.close();
                clientNo++;
            }
            out.clear();
        }
        return clientNo;
    }

    public void getRevision() throws IOException {
        SimpleDateFormat date = new SimpleDateFormat("hh:mm:ss");
        String output = date.format(new Date());
        IRC.sendMessage(Config.channel, "Version: " + findRS2Revision() + " Time checked: " + output);
    }
}
