#include "io_siggi_reflectionfreedom_ReflectionFreedom.h"

JNIEXPORT void JNICALL Java_io_siggi_reflectionfreedom_ReflectionFreedom_setAccessible
  (JNIEnv *env, jclass clazz, jobject accessibleObject, jboolean accessible) {
	jclass aoClass = env->GetObjectClass(accessibleObject);
	jfieldID overrideField = env->GetFieldID(aoClass, "override", "Z");
	env->SetBooleanField(accessibleObject, overrideField, accessible);
}

JNIEXPORT void JNICALL Java_io_siggi_reflectionfreedom_ReflectionFreedom_setModifiers
  (JNIEnv *env, jclass clazz, jobject accessibleObject, jint modifiers) {
	jclass aoClass = env->GetObjectClass(accessibleObject);
	jfieldID modifierField = env->GetFieldID(aoClass, "modifiers", "I");
	env->SetIntField(accessibleObject, modifierField, modifiers);
}

JNIEXPORT jobject JNICALL Java_io_siggi_reflectionfreedom_ReflectionFreedom_allocateObject
  (JNIEnv *env, jclass clazz, jclass classToAllocate) {
	return env->AllocObject(classToAllocate);
}

#define getField(FieldType, JNIMethod, ClassMethod) \
JNIEXPORT FieldType JNICALL ClassMethod \
  (JNIEnv* env, jclass clazz, jobject field, jobject object) { \
	jfieldID fieldID = env->FromReflectedField(field); \
	return env->JNIMethod(object, fieldID); \
}

getField(jobject, GetObjectField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getObjectField);
getField(jboolean, GetBooleanField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getBooleanField);
getField(jbyte, GetByteField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getByteField);
getField(jchar, GetCharField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getCharField);
getField(jshort, GetShortField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getShortField);
getField(jint, GetIntField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getIntField);
getField(jlong, GetLongField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getLongField);
getField(jfloat, GetFloatField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getFloatField);
getField(jdouble, GetDoubleField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getDoubleField);

#define setField(FieldType, JNIMethod, ClassMethod) \
JNIEXPORT void JNICALL ClassMethod \
  (JNIEnv* env, jclass clazz, jobject field, jobject object, FieldType value) { \
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

#define getStaticField(FieldType, JNIMethod, ClassMethod) \
JNIEXPORT FieldType JNICALL ClassMethod \
  (JNIEnv* env, jclass clazz, jclass fieldClass, jobject field) { \
	jfieldID fieldID = env->FromReflectedField(field); \
	return env->JNIMethod(fieldClass, fieldID); \
}

getStaticField(jobject, GetStaticObjectField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticObjectField);
getStaticField(jboolean, GetStaticBooleanField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticBooleanField);
getStaticField(jbyte, GetStaticByteField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticByteField);
getStaticField(jchar, GetStaticCharField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticCharField);
getStaticField(jshort, GetStaticShortField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticShortField);
getStaticField(jint, GetStaticIntField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticIntField);
getStaticField(jlong, GetStaticLongField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticLongField);
getStaticField(jfloat, GetStaticFloatField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticFloatField);
getStaticField(jdouble, GetStaticDoubleField, Java_io_siggi_reflectionfreedom_ReflectionFreedom_getStaticDoubleField);

#define setStaticField(FieldType, JNIMethod, ClassMethod) \
JNIEXPORT void JNICALL ClassMethod \
  (JNIEnv* env, jclass clazz, jclass fieldClass, jobject field, FieldType value) { \
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

