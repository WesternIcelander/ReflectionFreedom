package io.siggi.reflectionfreedom;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.AccessibleObject;
import java.util.logging.Level;
import java.util.logging.Logger;

public class ReflectionFreedom {
    private ReflectionFreedom() {
    }

    private static final boolean isMac;
    private static final boolean isWindows;
    private static final boolean isArm;
    private static final int bits;
    private static final boolean supported;

    public static boolean isSupported() {
        return supported;
    }

    public static native void setAccessible(AccessibleObject accessibleObject, boolean accessible);

    public static native void setModifiers(AccessibleObject accessibleObject, int modifiers);

    public static native <T> T allocateObject(Class<T> clazz);

    static {
        boolean isMac_ = false;
        boolean isWindows_ = false;
        boolean isArm_ = false;
        int bits_ = 64;
        boolean supported_ = false;
        if (System.getProperty("os.name").toLowerCase().contains("mac")) {
            isMac_ = true;
        }
        if (System.getProperty("os.name").toLowerCase().contains("windows")) {
            isWindows_ = true;
        }
        String arch = System.getProperty("os.arch").toLowerCase();
        if (arch.contains("arm") || arch.contains("aarch64")) {
            isArm_ = true;
        }
        try {
            bits_ = Integer.parseInt(System.getProperty("sun.arch.data.model"));
        } catch (NullPointerException | NumberFormatException ignored) {
        }
        isMac = isMac_;
        isWindows = isWindows_;
        isArm = isArm_;
        bits = bits_;
        File file = null;
        setup:
        try {
            String suffix;
            if (isMac) {
                suffix = isArm ? "_arm64.dylib" : "_x64.dylib";
            } else if (isWindows) {
                suffix = isArm ? "_aarch64.dll" : (bits == 64 ? "_x64.dll" : "_x86.dll");
            } else {
                suffix = isArm ? (bits == 64 ? "_aarch64.so" : "_arm.so") : "_x64.so";
            }
            InputStream in = ReflectionFreedom.class.getResourceAsStream("/reflectionfreedom" + suffix);
            if (in == null) {
                Logger.getLogger(ReflectionFreedom.class.getName()).log(Level.SEVERE, "ReflectionFreedom is not supported on this system!");
                break setup;
            }
            file = File.createTempFile("reflectionfreedom_", suffix);
            FileOutputStream out = new FileOutputStream(file);
            byte[] b = new byte[4096];
            int c;
            while ((c = in.read(b, 0, b.length)) != -1) {
                out.write(b, 0, c);
            }
            out.close();
            file.setExecutable(true);
            System.load(file.getAbsolutePath());
            if (isWindows) {
                file.deleteOnExit();
            } else {
                file.delete();
            }
            supported_ = true;
        } catch (IOException e) {
            if (file != null) {
                file.delete();
            }
            Logger.getLogger(ReflectionFreedom.class.getName()).log(Level.SEVERE, "ReflectionFreedom is not supported on this system!", e);
        }
        supported = supported_;
    }
}
