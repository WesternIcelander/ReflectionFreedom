#include <string.h>
#include "io_siggi_reflectionfreedom_ReflectionFreedom.h"

void throwNPE(JNIEnv* env, const char* message) {
	env->ThrowNew(env->FindClass("java/lang/NullPointerException"), message);
}

jobject makeAccessible(JNIEnv* env, jobject accessibleObject) {
	jclass aoClass = env->GetObjectClass(accessibleObject);
	jfieldID overrideField = env->GetFieldID(aoClass, "override", "Z");
	env->SetBooleanField(accessibleObject, overrideField, JNI_TRUE);
	return accessibleObject;
}

void rethrow(JNIEnv* env, const char* originalType, const char* newType) {
	jthrowable thrown = env->ExceptionOccurred();
	if (thrown == NULL) return;

	jclass thrownClass = env->GetObjectClass(thrown);
	jclass expectedClass = env->FindClass(originalType);
	if (!env->IsAssignableFrom(thrownClass, expectedClass)) return;

	env->ExceptionClear();

	jmethodID getMessage = env->GetMethodID(expectedClass, "getMessage", "()Ljava/lang/String;");
	jobject throwableMessage = env->CallObjectMethod(thrown, getMessage);

	jclass newClass = env->FindClass(newType);
	jmethodID newThrowableConstructor = env->GetMethodID(newClass, "<init>", "(Ljava/lang/String;)V");

	jthrowable newThrowable = (jthrowable) env->NewObject(newClass, newThrowableConstructor, throwableMessage);

	env->Throw(newThrowable);
}

JNIEXPORT void JNICALL Java_io_siggi_reflectionfreedom_ReflectionFreedom_setAccessible
  (JNIEnv *env, jclass clazz, jobject accessibleObject, jboolean accessible) {
	if (accessibleObject == NULL) {
		throwNPE(env, "AccessibleObject must not be null");
		return;
	}
	jclass aoClass = env->GetObjectClass(accessibleObject);
	jfieldID overrideField = env->GetFieldID(aoClass, "override", "Z");
	env->SetBooleanField(accessibleObject, overrideField, accessible);
}

JNIEXPORT void JNICALL Java_io_siggi_reflectionfreedom_ReflectionFreedom_setModifiers
  (JNIEnv *env, jclass clazz, jobject accessibleObject, jint modifiers) {
	if (accessibleObject == NULL) {
		throwNPE(env, "AccessibleObject must not be null");
		return;
	}
	jclass aoClass = env->GetObjectClass(accessibleObject);
	jfieldID modifierField = env->GetFieldID(aoClass, "modifiers", "I");
	env->SetIntField(accessibleObject, modifierField, modifiers);
}

JNIEXPORT jobject JNICALL Java_io_siggi_reflectionfreedom_ReflectionFreedom_allocateObject
  (JNIEnv *env, jclass clazz, jclass classToAllocate) {
	if (classToAllocate == NULL) {
		throwNPE(env, "Class must not be null");
		return NULL;
	}
	return env->AllocObject(classToAllocate);
}

JNIEXPORT jobject JNICALL Java_io_siggi_reflectionfreedom_ReflectionFreedom_getField
  (JNIEnv* env, jclass clazz, jclass classToGetFieldFrom, jstring name, jstring signature, jboolean isStatic) {
	if (classToGetFieldFrom == NULL || name == NULL || signature == NULL) {
		throwNPE(env, "Class, field name, and field signature must not be null");
		return NULL;
	}
	const char* fieldName = env->GetStringUTFChars(name, 0);
	const char* fieldSignature = env->GetStringUTFChars(signature, 0);
	jfieldID fieldID;
	if (isStatic == JNI_TRUE) {
		fieldID = env->GetStaticFieldID(classToGetFieldFrom, fieldName, fieldSignature);
	} else {
		fieldID = env->GetFieldID(classToGetFieldFrom, fieldName, fieldSignature);
	}
	env->ReleaseStringUTFChars(name, fieldName);
	env->ReleaseStringUTFChars(signature, fieldSignature);
	if (fieldID == NULL) {
		rethrow(env, "java/lang/NoSuchFieldError", "java/lang/NoSuchFieldException");
		return NULL;
	}
	return makeAccessible(env, env->ToReflectedField(classToGetFieldFrom, fieldID, isStatic));
}

JNIEXPORT jobject JNICALL Java_io_siggi_reflectionfreedom_ReflectionFreedom_getMethod
  (JNIEnv* env, jclass clazz, jclass classToGetMethodFrom, jstring name, jstring signature, jboolean isStatic) {
	if (classToGetMethodFrom == NULL || name == NULL || signature == NULL) {
		throwNPE(env, "Class, method name, and method signature must not be null");
		return NULL;
	}
	const char* methodName = env->GetStringUTFChars(name, 0);
	const char* methodSignature = env->GetStringUTFChars(signature, 0);
	if (strcmp("<init>", methodName) == 0) {
		env->ReleaseStringUTFChars(name, methodName);
		env->ReleaseStringUTFChars(signature, methodSignature);
		env->ThrowNew(env->FindClass("java/lang/NoSuchMethodException"), "Cannot get method with name of <init> - try getConstructor() instead!");
		return NULL;
	}
	jmethodID methodID;
	if (isStatic == JNI_TRUE) {
		methodID = env->GetStaticMethodID(classToGetMethodFrom, methodName, methodSignature);
	} else {
		methodID = env->GetMethodID(classToGetMethodFrom, methodName, methodSignature);
	}
	env->ReleaseStringUTFChars(name, methodName);
	env->ReleaseStringUTFChars(signature, methodSignature);
	if (methodID == NULL) {
		rethrow(env, "java/lang/NoSuchMethodError", "java/lang/NoSuchMethodException");
		return NULL;
	}
	return makeAccessible(env, env->ToReflectedMethod(classToGetMethodFrom, methodID, isStatic));
}

JNIEXPORT jobject JNICALL Java_io_siggi_reflectionfreedom_ReflectionFreedom_getConstructor
  (JNIEnv* env, jclass clazz, jclass classToGetConstructorFrom, jstring signature) {
	if (classToGetConstructorFrom == NULL || signature == NULL) {
		throwNPE(env, "Class, and constructor signature must not be null");
		return NULL;
	}
	const char* constructorSignature = env->GetStringUTFChars(signature, 0);
	jmethodID constructorID = env->GetMethodID(classToGetConstructorFrom, "<init>", constructorSignature);
	env->ReleaseStringUTFChars(signature, constructorSignature);
	if (constructorID == NULL) {
		rethrow(env, "java/lang/NoSuchMethodError", "java/lang/NoSuchMethodException");
		return NULL;
	}
	return makeAccessible(env, env->ToReflectedMethod(classToGetConstructorFrom, constructorID, JNI_FALSE));
}

#define getField(FieldType, JNIMethod, ClassMethod, ReturnOnFail) \
JNIEXPORT FieldType JNICALL ClassMethod \
  (JNIEnv* env, jclass clazz, jobject field, jobject object) { \
	if (field == NULL || object == NULL) { \
        throwNPE(env, "Class and field must not be null. If this is a static field, use the static version of this method instead."); \
        return ReturnOnFail; \
	} \
	jfieldID fieldID = env->FromReflectedField(field); \
	return env->JNIMethod(object, fieldID); \
}

getField(jobject, GetObjectField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getObjectField, NULL);
getField(jboolean, GetBooleanField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getBooleanField, JNI_FALSE);
getField(jbyte, GetByteField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getByteField, 0);
getField(jchar, GetCharField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getCharField, 0);
getField(jshort, GetShortField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getShortField, 0);
getField(jint, GetIntField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getIntField, 0);
getField(jlong, GetLongField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getLongField, 0);
getField(jfloat, GetFloatField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getFloatField, 0.0f);
getField(jdouble, GetDoubleField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getDoubleField, 0.0);

#define setField(FieldType, JNIMethod, ClassMethod) \
JNIEXPORT void JNICALL ClassMethod \
  (JNIEnv* env, jclass clazz, jobject field, jobject object, FieldType value) { \
	if (field == NULL || object == NULL) { \
        throwNPE(env, "Class and field must not be null. If this is a static field, use the static version of this method instead."); \
        return; \
	} \
	jfieldID fieldID = env->FromReflectedField(field); \
	env->JNIMethod(object, fieldID, value); \
}

setField(jobject, SetObjectField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setObjectField);
setField(jboolean, SetBooleanField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setBooleanField);
setField(jbyte, SetByteField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setByteField);
setField(jchar, SetCharField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setCharField);
setField(jshort, SetShortField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setShortField);
setField(jint, SetIntField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setIntField);
setField(jlong, SetLongField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setLongField);
setField(jfloat, SetFloatField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setFloatField);
setField(jdouble, SetDoubleField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setDoubleField);

#define getStaticField(FieldType, JNIMethod, ClassMethod, ReturnOnFail) \
JNIEXPORT FieldType JNICALL ClassMethod \
  (JNIEnv* env, jclass clazz, jclass fieldClass, jobject field) { \
	if (field == NULL) { \
        /* class is never null as ReflectionFreedom on java-side never passes a null class */ \
        throwNPE(env, "Field must not be null."); \
        return ReturnOnFail; \
	} \
	jfieldID fieldID = env->FromReflectedField(field); \
	return env->JNIMethod(fieldClass, fieldID); \
}

getStaticField(jobject, GetStaticObjectField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticObjectField, NULL);
getStaticField(jboolean, GetStaticBooleanField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticBooleanField, JNI_FALSE);
getStaticField(jbyte, GetStaticByteField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticByteField, 0);
getStaticField(jchar, GetStaticCharField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticCharField, 0);
getStaticField(jshort, GetStaticShortField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticShortField, 0);
getStaticField(jint, GetStaticIntField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticIntField, 0);
getStaticField(jlong, GetStaticLongField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticLongField, 0);
getStaticField(jfloat, GetStaticFloatField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticFloatField, 0.0f);
getStaticField(jdouble, GetStaticDoubleField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticDoubleField, 0.0);

#define setStaticField(FieldType, JNIMethod, ClassMethod) \
JNIEXPORT void JNICALL ClassMethod \
  (JNIEnv* env, jclass clazz, jclass fieldClass, jobject field, FieldType value) { \
	if (field == NULL) { \
        /* class is never null as ReflectionFreedom on java-side never passes a null class */ \
        throwNPE(env, "Field must not be null."); \
        return; \
	} \
	jfieldID fieldID = env->FromReflectedField(field); \
	env->JNIMethod(fieldClass, fieldID, value); \
}

setStaticField(jobject, SetStaticObjectField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setStaticObjectField);
setStaticField(jboolean, SetStaticBooleanField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setStaticBooleanField);
setStaticField(jbyte, SetStaticByteField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setStaticByteField);
setStaticField(jchar, SetStaticCharField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setStaticCharField);
setStaticField(jshort, SetStaticShortField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setStaticShortField);
setStaticField(jint, SetStaticIntField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setStaticIntField);
setStaticField(jlong, SetStaticLongField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setStaticLongField);
setStaticField(jfloat, SetStaticFloatField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setStaticFloatField);
setStaticField(jdouble, SetStaticDoubleField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_setStaticDoubleField);

