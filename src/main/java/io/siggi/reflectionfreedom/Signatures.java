package io.siggi.reflectionfreedom;

import java.lang.reflect.Array;

public class Signatures {
    private Signatures() {
    }

    private static Class<?> arrayType(Class<?> clazz) {
        return Array.newInstance(clazz, 0).getClass();
    }

    public static String signature(Class<?> cls) {
        if (cls.isArray()) {
            return cls.getName().replace('.', '/');
        } else if (cls.isPrimitive()) {
            if (cls == void.class) return "V";
            if (cls == boolean.class) return "Z";
            if (cls == byte.class) return "B";
            if (cls == char.class) return "C";
            if (cls == short.class) return "S";
            if (cls == int.class) return "I";
            if (cls == long.class) return "J";
            if (cls == float.class) return "F";
            if (cls == double.class) return "D";
            return arrayType(cls).getName().substring(1);
        } else {
            return "L" + cls.getName().replace('.', '/') + ";";
        }
    }

    public static String methodSignature(Class<?> returnType, Class<?>... args) {
        StringBuilder builder = new StringBuilder("(");
        for (Class<?> arg : args) {
            builder.append(signature(arg));
        }
        builder.append(")");
        builder.append(signature(returnType));
        return builder.toString();
    }
}
