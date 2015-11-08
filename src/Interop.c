#include <DroidSharp/Interop.h>

const char* getString(JNIEnv *env, jstring javaString)
{
    return (*env)->GetStringUTFChars(env, javaString, 0);
}

void freeString(JNIEnv *env, jstring javaString, const char* nativeString)
{
    (*env)->ReleaseStringUTFChars(env, javaString, nativeString);
}

void internalCall_LogI(const char* Message)
{
    LOGI_TAG("managed-interop", Message);
}

void internalCall_LogE(const char* Message)
{
    LOGE_TAG("managed-interop", Message);
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JVM = vm;
    return JNI_VERSION_1_4;
}

void Java_droidsharp_interop_DSActivity_SetPaths(JNIEnv *env, jobject thisObj, jstring AssemblyPath, jstring ConfigPath)
{
    const char* assembly = getString(env, AssemblyPath);
    const char* config = getString(env, ConfigPath);

    mono_set_dirs(assembly, config);
    LOGI("Paths set successfully");

    freeString(env, AssemblyPath, assembly);
    freeString(env, ConfigPath, config);
}

void Java_droidsharp_interop_DSActivity_LoadRuntime(JNIEnv *env, jobject thisObj, jstring RuntimePath)
{
    const char* file = getString(env, RuntimePath);

    LOGI("Initializing domain...");
    Domain = mono_jit_init(file);

    LOGI("Opening bridge assembly...");
    RuntimeAssembly = mono_domain_assembly_open(Domain, file);
    if (!RuntimeAssembly)
    {
        LOGE("Failed to load runtime assembly '%s'", file);
        return;
    }

    freeString(env, RuntimePath, file);

    LOGI("Registering internal calls...");
    mono_add_internal_call("DroidSharp.Interop.Log::LogI(intptr)", internalCall_LogI);
    mono_add_internal_call("DroidSharp.Interop.Log::LogE(intptr)", internalCall_LogE);

    LOGI("Getting assemly image...");
    MonoImage* image = mono_assembly_get_image(RuntimeAssembly);

    LOGI("Creating init method description...");
    MonoMethodDesc* desc = mono_method_desc_new("DroidSharp.Interop.Bridge:Initialize(intptr)", 1);

    LOGI("Searching for init method...");
    MonoMethod* initFunction = mono_method_desc_search_in_image(desc, image);
    mono_method_desc_free(desc);

    if (initFunction)
    {
        LOGI("Invoking init method...");
        void* args[1];
        args[0] = &JVM;
        mono_runtime_invoke(initFunction, NULL, args, NULL);
    }
    else
    {
        LOGE("Failed to locate init method");
        return;
    }
}

void Java_droidsharp_interop_DSActivity_Shutdown(JNIEnv *env, jobject thisObj)
{
    mono_jit_cleanup(Domain);
}
