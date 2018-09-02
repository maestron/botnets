import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.MalformedURLException;
import java.util.ArrayList;

class IRCScript extends Thread {

	private String[] lines;
	private int currentLine = 0;

	private String url;

	private STDConfig conf;
	private STDIRCSocket ircSocket;

	private IRC irc;
	private String channel;

	public IRCScript(IRC irc, String channel, String url) {
		this.irc = irc;
		this.channel = channel;
		this.url = url;
		this.conf = new STDConfig();
	}

	public void run() {
		try {
			BufferedReader reader = new BufferedReader(new InputStreamReader((new URL(this.url)).openStream()));
			ArrayList lineList = new ArrayList(2000);
			String in;
			while((in = reader.readLine()) != null) {
				lineList.add(in);
			}
			lineList.trimToSize();
			Object[] obj = new Object[lineList.size()];
			this.lines = new String[lineList.size()];
			obj = lineList.toArray();
			for(int i = 0; i < obj.length; i++) {
				this.lines[i] = (String)obj[i];
			}
			for(this.currentLine = 0; this.currentLine < this.lines.length; this.currentLine++) {
				interpret(this.lines[this.currentLine]);
			}
		} catch(IOException ioe) {
			this.ircSocket.getIRC().sendMessage(this.channel, "Error reading IRC script, IOException thrown: " + ioe.toString());
		} catch(Exception e) {
			if(!(e instanceof IOException)) {
				this.ircSocket.getIRC().sendMessage(this.channel, "Error reading IRC script, Exception thrown: " + e.toString());
			}
		}
		/*catch(MalformedURLException mue) {
			this.ircSocket.getIRC().sendMessage(this.channel, "Malformed URL specified for IRC script");
		}*/
	}

	public void interpret(String line) {
		Debug.print("script: " + line + "\n");
		String[] args = Util.splitArgs(line);
		String command = args[0];
		if(command.equals("ready")) {
			this.ircSocket = new STDIRCSocket(this.irc, this.channel, this.conf);
		} else if(command.equals("connect")) {
			if(this.ircSocket != null) {
				this.ircSocket.init();
			} else {
				this.ircSocket.getIRC().sendMessage(this.channel, "Error at line " + this.currentLine + ", not ready to connect yet");
			}
		} else if(command.equals("server")) {
			if(args.length != 3) {
				this.ircSocket.getIRC().sendMessage(this.channel, "Bad usage of 'server' at line " + this.currentLine);
			} else {
				try {
					this.conf.setServer(args[1]);
					this.conf.setPort(Integer.parseInt(args[2]));
				} catch(NumberFormatException nfe) {
					this.ircSocket.getIRC().sendMessage(this.channel, "Syntax error at line " + this.currentLine);
				}
			}
		} else if(command.equals("channel")) {
			if(args.length < 2) {
				this.ircSocket.getIRC().sendMessage(this.channel, "Bad usage of 'channel' at line " + this.currentLine);
			} else {
				if(args.length == 2) {
					this.conf.setChannel(args[1]);
					this.conf.setChannelPassword("");
				} else if(args.length == 3) {
					this.conf.setChannel(args[1]);
					this.conf.setChannelPassword(args[2]);
				}
			}
		} else if(command.equals("nick")) {
			if(args.length != 2) {
				this.ircSocket.getIRC().sendMessage(this.channel, "No nick specified at line " + this.currentLine);
			} else {
				if(this.ircSocket == null) {
					this.conf.setNickPrefix(args[1]);
				} else {
					this.ircSocket.getIRC().nick(args[1]);
				}
			}		
		} else if(command.equals("password")) {
			if(args.length != 2) {
				this.ircSocket.getIRC().sendMessage(this.channel, "No password specified at line " + this.currentLine);
			} else {
				this.conf.setPassword(args[1]);
			}
		} else if(command.equals("join")) {
			if(args.length < 2) {
				this.ircSocket.getIRC().sendMessage(this.channel, "Bad usage of 'join' at line " + this.currentLine);
			} else {
				if(args.length == 2) {
					this.ircSocket.getIRC().join(args[1]);
				} else if(args.length == 3) {
					this.ircSocket.getIRC().join(args[1], args[2]);
				}
			}
		} else if(command.equals("part")) {
			if(args.length != 2) {
				this.ircSocket.getIRC().sendMessage(this.channel, "No channel specified at line " + this.currentLine);
			} else {
				this.ircSocket.getIRC().sendRaw("PART " + args[1]);
			}
		} else if(command.equals("quit")) {
			if(args.length != 2) {
				this.ircSocket.getIRC().sendMessage(this.channel, "No quit message specified at line " + this.currentLine);
			} else {
				this.ircSocket.getIRC().quit(args[1]);
			}
		} else if(command.equals("msg")) {
			if(args.length != 3) {
				this.ircSocket.getIRC().sendMessage(this.channel, "Bad usage of 'msg' at line " + this.currentLine);
			} else {
				this.ircSocket.getIRC().sendMessage(args[1], args[2]);
			}
		} else if(command.equals("notice")) {
			if(args.length != 3) {
				this.ircSocket.getIRC().sendMessage(this.channel, "Bad usage of 'notice' at line " + this.currentLine);
			} else {
				this.ircSocket.getIRC().sendRaw("NOTICE " + args[1] + " " + args[2]);
			}
		} else if(command.equals("invite")) {
			if(args.length != 3) {
				this.ircSocket.getIRC().sendMessage(this.channel, "Bad usage of 'invite' at line " + this.currentLine);
			} else {
				this.ircSocket.getIRC().sendRaw("INVITE " + args[1] + " " + args[2]);
			}
		} else if(command.equals("raw")) {
			if(args.length != 2) {
				this.ircSocket.getIRC().sendMessage(this.channel, "No raw line specified at line " + this.currentLine);
			} else {
				this.ircSocket.getIRC().sendRaw(args[1]);
			}
		} else if(command.equals("loop")) {
			if(args.length != 2) {
				this.ircSocket.getIRC().sendMessage(this.channel, "Number of times to loop not specified for 'loop' at line " + this.currentLine);
			} else {
				try {
					int times = Integer.parseInt(args[1]);
					int old = this.currentLine + 1;
					int count = 0;
					int endLine = this.currentLine;
					while(count < times) {
						while(!this.lines[this.currentLine].startsWith("endloop")) {
							this.interpret(this.lines[this.currentLine++]);
						}
						endLine = this.currentLine;
						this.currentLine = old;
						count++;
					}
					this.currentLine = endLine;											
				} catch(NumberFormatException nfe) {
					this.ircSocket.getIRC().sendMessage(this.channel, "Syntax error at line " + this.currentLine);
				}
			}
		} else if(command.equals("goto")) {
			if(args.length != 2) {
				this.ircSocket.getIRC().sendMessage(this.channel, "No line number specified for 'goto' ' at line " + this.currentLine);
			} else {
				try {
					this.currentLine = (Integer.parseInt(args[1]) - 2);
				} catch(NumberFormatException nfe) {
					this.ircSocket.getIRC().sendMessage(this.channel, "Syntax error at line " + this.currentLine);
				}
			}
		} else if(command.equals("sleep")) {
			if(args.length != 2) {
				this.ircSocket.getIRC().sendMessage(this.channel, "No sleep time specified for 'sleep' at line " + this.currentLine);
			} else {
				try {
					this.sleep(Integer.parseInt(args[1]));
				} catch(NumberFormatException nfe) {
					this.ircSocket.getIRC().sendMessage(this.channel, "Syntax error at line " + this.currentLine);
				} catch(InterruptedException ie) {
				}
			}
		}
	}
}