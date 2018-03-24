package com.marcus.cmakedemo;

/**
 * Created by Marcus on 2018/3/22.
 */

public class JniNative {

    static {
        System.loadLibrary("JniNative");
    }

    public native String getStringFromJni();

    public native boolean jniArrayAdd(int[] array, int num);

    public native void dataTypeMapping(byte by, short sh, char ch, int in, float fl, double dou, long lo, boolean boo, int[] intArray, String str, ObjectClass objectClass);

    public static native String getStringCritical(String text);

    public static native String getStringUTFRegion(String text);

    public static native int sumIntArray(int[] array);

    public static native float[][][] intToInt2DArray();

}

class ObjectClass {

}
