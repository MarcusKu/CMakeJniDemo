#include <jni.h>
#include<malloc.h>
#include <android/log.h>
#include <string>
#include <string.h>

#define TAG "JniNative"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL, TAG, __VA_ARGS__)

extern "C" {

    JNIEXPORT jstring JNICALL Java_com_marcus_cmakedemo_JniNative_getStringFromJni(JNIEnv *env, jobject obj) {
        std::string hello = "return text from C++/C";
        return env->NewStringUTF(hello.c_str());
    };

    JNIEXPORT jboolean JNICALL Java_com_marcus_cmakedemo_JniNative_jniArrayAdd
            (JNIEnv *env, jobject obj, jintArray array, jint num) {
        jsize size = env->GetArrayLength(array);
        jboolean isCopy;
        jint *primitiveArray = (jint *) env->GetPrimitiveArrayCritical(array, &isCopy);
        for (int i = 0; i < size; i++) {
            primitiveArray[i] += num;
        }
        env->ReleasePrimitiveArrayCritical(array, primitiveArray, JNI_COMMIT);
        return isCopy;
    };
    JNIEXPORT void JNICALL Java_com_marcus_cmakedemo_JniNative_dataTypeMapping
            (JNIEnv *env, jobject obj, jbyte by, jshort sh, jchar ch, jint in, jfloat fl, jdouble dou, jlong lo, jboolean boo, jintArray array, jstring str,
            jobject jclass) {
        LOGI("byteType = %d, shortType = %hd, charType = %c, intType = %d, floatType = %f, doubleType = %lf, longType = %ld, booleanType = %c", by, sh, ch, in, fl, dou, lo, boo);
        const char *c_str = NULL;
        jboolean  isCopy = false;
        c_str = (env)->GetStringUTFChars(str, &isCopy);
        if (c_str == NULL)
        {
            return;
        }
        (env)->ReleaseStringUTFChars(str, c_str);
        LOGI("c_str: %s\n", (char*)c_str);
    };

    JNIEXPORT jstring JNICALL Java_com_marcus_cmakedemo_JniNative_getStringCritical
            (JNIEnv *env, jclass obj, jstring text){
        const jchar* cha = NULL;
        char buff[128] = "7890";
        char* pBuff = buff + 6;
        jboolean  isCopy;
        cha = env -> GetStringCritical(text, &isCopy);
        if(cha == NULL){
            return NULL;
        }
        while (*cha){
            *pBuff++ = *cha++;
        }
        env->ReleaseStringCritical(text, cha);
        return env->NewStringUTF(buff);
    };


    JNIEXPORT jstring JNICALL Java_com_marcus_cmakedemo_JniNative_getStringUTFRegion
            (JNIEnv *env, jclass obj, jstring text){
        jsize len  = env -> GetStringLength(text);
        LOGI("Text Length = %d", len);
        const jchar* cha = NULL;
        char buff[128] = "7890";
        char* pBuff = buff + 6;
        env -> GetStringUTFRegion(text, 0, len, pBuff);
        return env -> NewStringUTF(buff);
    };

    JNIEXPORT jint JNICALL Java_com_marcus_cmakedemo_JniNative_sumIntArray
            (JNIEnv *env, jclass obj, jintArray array){
        jint i, sum = 0;
        jint *c_array;
        jint len;
        len = env -> GetArrayLength(array);
        c_array = (jint *) malloc(sizeof(jint) * len);
        memset(c_array, 0, sizeof(jint) * len);
        LOGI("JintArray Length = %d", len);
        env->GetIntArrayRegion(array,0, len, c_array);
        for(int i=0; i<len; i++){
            sum += c_array[i];
        }
        free(c_array);
        return sum;
    };

    JNIEXPORT jobjectArray JNICALL Java_com_marcus_cmakedemo_JniNative_intToInt2DArray
            (JNIEnv *env, jclass obj){
        jclass floatArrayClass = env -> FindClass("[[F");
        jobjectArray float3DArray = env -> NewObjectArray(2, floatArrayClass, NULL);
        for(int i = 0; i < 2; i++){
            jclass intArray = env -> FindClass("[F");
            jobjectArray objArray = env -> NewObjectArray(10, intArray, NULL);
            for (int j = 0; j < 10; ++j) {
                jfloat temp[256];
                jfloatArray  array = env -> NewFloatArray(3);
                temp[0] = 10.0;
                temp[1] = 20.0;
                temp[2] = 30.0;
                env -> SetFloatArrayRegion(array, 0, 3, temp);
                env -> SetObjectArrayElement(objArray, j, array);
                env -> DeleteLocalRef(array);
            }
            env -> SetObjectArrayElement(float3DArray, i, objArray);
            env -> DeleteLocalRef(objArray);
        }
        return float3DArray;
    };

}