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



/**
 * Static utility methods used by the command-line parsers
 *
 * @version $Revision: 1.1.1.1 $ ; $Date: 2004/02/16 01:17:52 $
 * @author Alexander V. Konstantinou (akonstan@cs.columbia.edu)   
 */
public class CommandLine {

  /**
   * Returns the int value of the command line argument at the specified
   * index, or exits with an error message if the value is missing or is
   * not an integer.
   * 
   * @param pname - the program's name (used for error reporting before exit)
   * @param description - description of value used for error reporting
   * @param args - the arguments array
   * @param index - index into the args array where the value is stored
   *                (if out of bounds then an error is issued and 
   *                 System.exit(1);
   *
   * @return the integer value, or exit process with System.exit(1)
   */
  public static int getIntArg(String pname, String description,
			      String[] args, int index) {
    if (index >= args.length) {
      System.err.println(pname + ": expected " + description + 
			 " integer argument following ");
      System.exit(1);
    }
    
    try {
      return(Integer.parseInt(args[index]));
    } catch (NumberFormatException e) {
      System.err.println(pname + ": Invalid " + description + " value " +
			 args[index] + ": " + e.getMessage());
      System.exit(1);
      return(0); // keep compiler happy
    }
  }
				
  /**
   * Returns the String value of the command line argument at the specified
   * index, or exits with an error message if the index is out of bounds.
   *
   * @param pname - the program's name (used for error reporting before exit)
   * @param description - description of value used for error reporting
   * @param args - the arguments array
   * @param index - index into the args array where the value is stored
   *                (if out of bounds then an error is issued and 
   *                 System.exit(1);
   */
  public static String getStringArg(String pname, String description,
				    String[] args, int index) {

    if (index >= args.length) {
      System.err.println(pname + ": empty " + description + " argument");
      System.exit(1);
    }

    return(args[index]);
  }
}
