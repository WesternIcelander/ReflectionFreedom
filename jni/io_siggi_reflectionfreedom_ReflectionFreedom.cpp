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

