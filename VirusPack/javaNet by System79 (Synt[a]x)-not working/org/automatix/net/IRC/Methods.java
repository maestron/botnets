package org.automatix.net.IRC;

import java.util.ArrayList;

/**
 * Created by IntelliJ IDEA.
 * User: Administrator
 * Date: Oct 27, 2008
 * Time: 5:47:55 PM
 * To change this template use File | Settings | File Templates.
 */
public class Methods {
    	public static String[] splitArgs(String command) {
		command = command.trim();
		ArrayList<String> argsList = new ArrayList(15);
		int quotes = 0;
		int lastIndex = 0;
		for(int i = 0; i < command.length(); i++) {
			if(command.substring(i, i + 1).equals("\"")) {
				quotes++;
				if(i + 1 == command.length()) {
					argsList.add(command.substring(lastIndex + 1, i + 1));
				}
			} else if(command.substring(i, i + 1).equals(" ")) {
				if(quotes == 0) {
					int offset = (lastIndex != 0) ? 1 : 0;
					argsList.add(command.substring(lastIndex + offset, i));
					lastIndex = i;
				} else if(quotes % 2 == 0) {
					argsList.add(command.substring(lastIndex + 1, i));
					lastIndex = i;
				}
			} else if(i + 1 == command.length()) {
				int offset = (lastIndex != 0) ? 1 : 0;
				argsList.add(command.substring(lastIndex + offset, i + 1));
			}
		}
		argsList.trimToSize();
		Object[] objs = argsList.toArray();
		String[] args = new String[objs.length];
		for(int j = 0; j < objs.length; j++) {
			args[j] = (String)objs[j];
			args[j] = args[j].replaceAll("\"", "");
		}
		return args;
	}
}
