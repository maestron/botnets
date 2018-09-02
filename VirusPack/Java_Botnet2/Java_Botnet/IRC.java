import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.BufferedWriter;
import java.io.OutputStreamWriter;
import java.io.IOException;

class IRC {

	private IRCSocket ircSocket;

	public IRC(IRCSocket ircSocket) {
		this.ircSocket = ircSocket;
	}

	public void pass(String pass) {
		this.sendRaw("PASS " + pass);
	}

	public void nick(String nick) {
		this.sendRaw("NICK " + nick);
	}

	public void user(String nick, String hostname, String servername, String realname) {
		this.sendRaw("USER " + nick + " " + hostname + " " + servername + " " + realname);
	}

	public void quit(String message) {
		this.sendRaw("QUIT :" + message);
	}

	public void join(String channel) {
		this.sendRaw("JOIN " + channel);
	}

	public void join(String channel, String password) {
		this.sendRaw("JOIN " + channel + " " + password);
	}

	public void part(String channel) {
		this.sendRaw("PART " + channel);
	}

	public void sendMessage(String channel, String message) {
		this.sendRaw("PRIVMSG " + channel + " :" + message);
	}

	public void sendRaw(String line) {
		try {
			BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(this.ircSocket.getSocket().getOutputStream()));
			writer.write(line + "\n");
			writer.flush();
		} catch(IOException ioe) {
		}
	}

	public String readLine() {
		try {
			BufferedReader reader = new BufferedReader(new InputStreamReader(this.ircSocket.getSocket().getInputStream()));
			return reader.readLine();
		} catch(IOException ioe) {
			return "null";
		}
	}

	public String getNick(String line) {
		return line.substring(1, line.indexOf("!"));
	}

	public String getChannel(String line) {
		if(line.indexOf("#") != -1 && line.lastIndexOf(":") != -1 && line.indexOf("PRIVMSG") != -1 && line.indexOf("#") < line.lastIndexOf(" :")) {
			return line.substring(line.indexOf("#"), line.lastIndexOf(" :")).replaceAll(" ", "");
		} else if(line.indexOf("PRIVMSG") != -1) {
			return line.substring(1, line.indexOf("!"));
		} else {
			return "null";
		}
	}

	public String getMessage(String line) {
		if(line.lastIndexOf(":") != -1) {
			return line.substring(line.lastIndexOf(" :") + 2);
		} else {
			return null;
		}
	}

}