#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL Java_my_tools_demo_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jint JNICALL Java_my_tools_demo_add(
        JNIEnv* env,
        jclass, int a, int b) {
    return (a+b);
}

extern "C" JNIEXPORT jstring JNICALL Java_my_tools_demo_getStringFromJava
        (JNIEnv *env, jobject obj) {
    jclass clazz = env->FindClass("my/tools/demo");
    jfieldID fieldID = env->GetFieldID(clazz, "str", "Ljava/lang/String;");
    auto str = (jstring) env->GetObjectField(obj, fieldID);
    return str;
}

extern "C" JNIEXPORT jstring JNICALL Java_my_tools_demo_getStringFromJavaStatic
        (JNIEnv *env, jobject obj) {
    jclass clazz = env->FindClass("my/tools/demo");
    jfieldID fieldID = env->GetStaticFieldID(clazz, "sta_str", "Ljava/lang/String;");
    auto str = (jstring) env->GetStaticObjectField(clazz, fieldID);
    return str;
}

//extern "C" JNIEXPORT void JNICALL Java_my_tools_demo_callNormalMethodc
extern "C" JNIEXPORT void JNICALL callJavaNormalMethod
        (JNIEnv *env, jobject obj) {

    jclass clazz = env->FindClass("com/example/jnidemo/MainActivity");
    jmethodID methodID = env->GetMethodID(clazz, "logstr", "(Ljava/lang/String;)V");
    jmethodID methodID1 = env->GetMethodID(clazz, "<init>", "()V");
    jobject jobject1 = env->NewObject(clazz,methodID1);
    jstring str = env->NewStringUTF("Surprise！！");
    env->CallVoidMethod(jobject1, methodID, str);
}

//extern "C" JNIEXPORT void JNICALL Java_main_Tools_callStaticMethod
extern "C" JNIEXPORT void JNICALL callJavaStaticMethod
        (JNIEnv *env, jobject obj){
    jclass clazz = env->FindClass("com/example/jnidemo/MainActivity");
    jmethodID methodID = env->GetStaticMethodID(clazz, "staticLogStr", "(Ljava/lang/String;)V");
    jstring str = env->NewStringUTF("Super Surprise！！");
    env->CallStaticVoidMethod(clazz, methodID, str);
}

//extern "C" JNIEXPORT jint JNICALL Java_main_Tools_callNormalMethod2
extern "C" JNIEXPORT jint JNICALL callJavaNormalMethod2
        (JNIEnv *env, jobject obj){
    jclass clazz = env->FindClass("my/tools/demo");
    jmethodID methodID = env->GetMethodID(clazz, "javaAdd", "(II)I");
    jint a = env->CallIntMethod(obj, methodID, 100 , 2);
    return a;
}

// 动态注册
JNINativeMethod methods[]{
    {"callNormalMethod","()V", (void**) &callJavaNormalMethod},
    {"callStaticMethod", "()V", (void**) &callJavaStaticMethod},
    {"callNormalMethod2", "()I" , (void**) &callJavaNormalMethod2}
};

jint registerNative(JNIEnv* env){
    jclass clazz = env->FindClass("my/tools/demo");
    if(env->RegisterNatives(clazz, methods,sizeof methods / sizeof methods[0]) != JNI_OK){
        return JNI_ERR;
    }
    return JNI_OK;
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved){
    JNIEnv* env;
    vm->GetEnv((void**)&env, JNI_VERSION_1_4);
    if(registerNative(env)!=JNI_OK){
        return JNI_ERR;
    }
    return JNI_VERSION_1_4;
}