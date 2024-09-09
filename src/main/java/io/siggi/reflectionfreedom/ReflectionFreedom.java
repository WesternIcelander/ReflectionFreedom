package io.siggi.reflectionfreedom;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.AccessibleObject;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
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

    public static native Field getField(Class<?> clazz, String name, String signature, boolean isStatic) throws NoSuchFieldException;

    public static native Method getMethod(Class<?> clazz, String name, String signature, boolean isStatic) throws NoSuchMethodException;

    public static native <T> Constructor<T> getConstructor(Class<T> clazz, String signature) throws NoSuchMethodException;

    public static native Object getObjectField(Field field, Object object);

    public static native boolean getBooleanField(Field field, Object object);

    public static native byte getByteField(Field field, Object object);

    public static native char getCharField(Field field, Object object);

    public static native short getShortField(Field field, Object object);

    public static native int getIntField(Field field, Object object);

    public static native long getLongField(Field field, Object object);

    public static native float getFloatField(Field field, Object object);

    public static native double getDoubleField(Field field, Object object);

    public static native void setObjectField(Field field, Object object, Object value);

    public static native void setBooleanField(Field field, Object object, boolean value);

    public static native void setByteField(Field field, Object object, byte value);

    public static native void setCharField(Field field, Object object, char value);

    public static native void setShortField(Field field, Object object, short value);

    public static native void setIntField(Field field, Object object, int value);

    public static native void setLongField(Field field, Object object, long value);

    public static native void setFloatField(Field field, Object object, float value);

    public static native void setDoubleField(Field field, Object object, double value);

    public static Object getStaticObjectField(Field field) {
        return getStaticObjectField(field.getDeclaringClass(), field);
    }

    private static native Object getStaticObjectField(Class clazz, Field field);

    public static boolean getStaticBooleanField(Field field) {
        return getStaticBooleanField(field.getDeclaringClass(), field);
    }

    private static native boolean getStaticBooleanField(Class clazz, Field field);

    public static byte getStaticByteField(Field field) {
        return getStaticByteField(field.getDeclaringClass(), field);
    }

    private static native byte getStaticByteField(Class clazz, Field field);

    public static char getStaticCharField(Field field) {
        return getStaticCharField(field.getDeclaringClass(), field);
    }

    private static native char getStaticCharField(Class clazz, Field field);

    public static short getStaticShortField(Field field) {
        return getStaticShortField(field.getDeclaringClass(), field);
    }

    private static native short getStaticShortField(Class clazz, Field field);

    public static int getStaticIntField(Field field) {
        return getStaticIntField(field.getDeclaringClass(), field);
    }

    private static native int getStaticIntField(Class clazz, Field field);

    public static long getStaticLongField(Field field) {
        return getStaticLongField(field.getDeclaringClass(), field);
    }

    private static native long getStaticLongField(Class clazz, Field field);

    public static float getStaticFloatField(Field field) {
        return getStaticFloatField(field.getDeclaringClass(), field);
    }

    private static native float getStaticFloatField(Class clazz, Field field);

    public static double getStaticDoubleField(Field field) {
        return getStaticDoubleField(field.getDeclaringClass(), field);
    }

    private static native double getStaticDoubleField(Class clazz, Field field);

    public static void setStaticObjectField(Field field, Object value) {
        setStaticObjectField(field.getDeclaringClass(), field, value);
    }

    private static native void setStaticObjectField(Class clazz, Field field, Object value);

    public static void setStaticBooleanField(Field field, boolean value) {
        setStaticBooleanField(field.getDeclaringClass(), field, value);
    }

    private static native void setStaticBooleanField(Class clazz, Field field, boolean value);

    public static void setStaticByteField(Field field, byte value) {
        setStaticByteField(field.getDeclaringClass(), field, value);
    }

    private static native void setStaticByteField(Class clazz, Field field, byte value);

    public static void setStaticCharField(Field field, char value) {
        setStaticCharField(field.getDeclaringClass(), field, value);
    }

    private static native void setStaticCharField(Class clazz, Field field, char value);

    public static void setStaticShortField(Field field, short value) {
        setStaticShortField(field.getDeclaringClass(), field, value);
    }

    private static native void setStaticShortField(Class clazz, Field field, short value);

    public static void setStaticIntField(Field field, int value) {
        setStaticIntField(field.getDeclaringClass(), field, value);
    }

    private static native void setStaticIntField(Class clazz, Field field, int value);

    public static void setStaticLongField(Field field, long value) {
        setStaticLongField(field.getDeclaringClass(), field, value);
    }

    private static native void setStaticLongField(Class clazz, Field field, long value);

    public static void setStaticFloatField(Field field, float value) {
        setStaticFloatField(field.getDeclaringClass(), field, value);
    }

    private static native void setStaticFloatField(Class clazz, Field field, float value);

    public static void setStaticDoubleField(Field field, double value) {
        setStaticDoubleField(field.getDeclaringClass(), field, value);
    }

    private static native void setStaticDoubleField(Class clazz, Field field, double value);

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
