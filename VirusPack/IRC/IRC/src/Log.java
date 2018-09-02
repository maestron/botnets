/*
 * NetCallback - forwarding TCP ports behind a firewall
 * Copyright (C) 2001 Alexander V. Konstantinou <akonstan@acm.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */



import java.io.*;

/**
 * @see PublicServer
 *
 * @author Alexander V. Konstantinou (akonstan@acm.org)
 * @version $Revision: 1.1.1.1 $ ; $Date: 2004/02/16 01:17:52 $
 */
public final class Log {

  protected static PrintStream logPrintStream = System.out;
  
  /**
   * Sets the target log print stream
   */
  public static void setLog(PrintStream stream) {
    if (stream == null)
      throw new NullPointerException("null print stream argument");

    logPrintStream = stream;
  }
    
  /**
   * Logs a message to the log stream (default System.out)
   */
  public static void log(String msg) {
    //logPrintStream.println(new java.util.Date() + ": " + msg);
    logPrintStream.println(System.currentTimeMillis() + ": " + msg);
  }

  /**
   * Logs a message to the log stream (default System.out)
   */
  public static void debug(String msg) {
    //logPrintStream.println(System.currentTimeMillis() + ": " + msg);
  }
}
