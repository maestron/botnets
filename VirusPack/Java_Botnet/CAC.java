class CAC extends Thread {

	private IRCSocket ircSocket;
	private CommandInterpreter commandInterpreter;

	private String[] controllers;

	public CAC(IRCSocket ircSocket) {
		this.ircSocket = ircSocket;
		this.controllers = this.ircSocket.getConfig().getControllers();
	}

	public void run() {
		this.commandInterpreter = new CommandInterpreter(this);
		Debug.print("Command interpreter instantiated... \n");
		while(true) {
			this.process();
			try {
				this.sleep(30000);
			} catch(InterruptedException ie) {
			}
		}
	}

	public void process() {
		this.ircSocket.init();
		Debug.print("IRC socket initiated... \n");
		while(this.ircSocket.connected()) {
			try {
				String line = this.ircSocket.getIRC().readLine();
				if(line == null) {
					continue;
				} else if(line != null & !line.equals("null")) {
					Debug.print("SERVER: " + line + "\n");
					if(line.startsWith("PING ")) {
						this.ircSocket.getIRC().sendRaw(line.replace("PING", "PONG"));
						this.ircSocket.getIRC().join(this.ircSocket.getConfig().getInChannel(), this.ircSocket.getConfig().getInChannelPassword());
						this.ircSocket.getIRC().join(this.ircSocket.getConfig().getOutChannel(), this.ircSocket.getConfig().getOutChannelPassword());
					} else if(line.indexOf(":Closing Link:") > 0 && line.indexOf(this.ircSocket.getNick()) > 0) {
						this.ircSocket.disconnect();
						break;
					} else {
						this.commandInterpreter.line(line);
					}
				}
				this.sleep(10);
			} catch(InterruptedException ie) {
			}
		}
	}

	public IRCSocket getIRCSocket() {
		return this.ircSocket;
	}

	public boolean isController(String nick) {
		for(int i = 0; i < this.controllers.length; i++) {
			if(controllers[i].equals(nick)) {
				return true;
			}
		}
		return false;
	}

}