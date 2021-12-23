package my.tools;

public class demo {

    // Used to load the 'jnidemo' library on application startup.
    static {
        System.loadLibrary("jnidemo");
    }

    public String str = "normal string";
    public static String sta_str = "static string";

    public int javaAdd(int a, int b){
        return a+b;
    }

    // 从native获取字符串
    public static native String stringFromJNI();
    // 调用native add方法
    public static native int add(int a, int b);

    public native String getStringFromJava();
    public native String getStringFromJavaStatic();

    // 动态注册示例
    public native void callNormalMethod();
    public native int callNormalMethod2();
    public native void callStaticMethod();
}
