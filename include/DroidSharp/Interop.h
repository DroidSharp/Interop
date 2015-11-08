#ifndef DS_INTEROP_H
#define DS_INTEROP_H

#include <jni.h>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>

#include <DroidSharp/Logging.h>

JavaVM* JVM;
MonoDomain* Domain;
MonoAssembly* RuntimeAssembly;

JNIEXPORT void JNICALL Java_droidsharp_interop_DSActivity_SetPaths(JNIEnv *env, jobject thisObj, jstring AssemblyPath, jstring ConfigPath);

JNIEXPORT void JNICALL Java_droidsharp_interop_DSActivity_LoadRuntime(JNIEnv *env, jobject thisObj, jstring AssemlyFilename);

JNIEXPORT void JNICALL Java_droidsharp_interop_DSActivity_Shutdown(JNIEnv *env, jobject thisObj);

#endif
