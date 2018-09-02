
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;
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
public class CommandPromptServer {

    private static ServerSocket servSock;
    private static Socket sock;
    private static InputStream in;
    private static OutputStream out;

    public static void initServer() throws IOException {
        startServer();
        acceptConnections();
    }

    public static void startServer() throws IOException {
        servSock = new ServerSocket(4453);
    }

    public static void acceptConnections() throws IOException {
        while (Status.cmdServer) {
            sock = servSock.accept();
            out = sock.getOutputStream();
            in = sock.getInputStream();
            new ClientProcessor(sock, in, out);
        }
    }
}

class ClientProcessor implements Runnable {

    Socket s;
    InputStream in;
    OutputStream out;
    boolean connected;

    public ClientProcessor(Socket s, InputStream in, OutputStream out) {
        this.s = s;
        this.in = in;
        this.out = out;
        this.connected = true;
        new Thread(this).start();
    }

    public void send(String line) {
        try {
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(out));
            writer.write((new StringBuilder(String.valueOf(line))).append("\n").toString());
            writer.flush();
        } catch (IOException ioe) {
        }
    }

    public String readLine() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(in));
        return br.readLine();
    }

    public void cmd(String cmd) throws IOException {
        Process p = Runtime.getRuntime().exec(new String[]{"cmd.exe", "/C", cmd});
        BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = br.readLine()) != null) {
            if (line.equals("\n") || line.equals("") || line.equals(" ")) {
                continue;
            }
            send(line);
        }
        br.close();
    }

    public void run() {
        while (connected) {
            String line = null;
            try {
                line = readLine();
            } catch (IOException ex) {
                Logger.getLogger(ClientProcessor.class.getName()).log(Level.SEVERE, null, ex);
            }
            try {
                cmd(line);
            } catch (IOException ex) {
                Logger.getLogger(ClientProcessor.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
}
