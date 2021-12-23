package com.example.jnidemo;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.example.jnidemo.databinding.ActivityMainBinding;

import my.tools.demo;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private static final String TAG = "Demo3";
    private static TextView tv;

    public demo demo;
    private int [] bts = {R.id.bt1, R.id.bt2, R.id.bt3, R.id.bt4,
            R.id.bt5, R.id.bt6};


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        demo = new demo();

        // Example of a call to a native method
        tv = findViewById(R.id.sample_text);
        for (int bt : bts) {
            findViewById(bt).setOnClickListener(this);
        }
        tv.setText(demo.stringFromJNI());
    }

    public void logstr(String str){
//        Toast.makeText(MainActivity.this, str, Toast.LENGTH_SHORT).show();
        Log.d(TAG, "toastStr: " + str);
        tv.setText(str);
    }

    public int add(int a, int b){
        return a+b;
    }

    public static void staticLogStr(String str){
        Log.d(TAG, "toastStr: " + str);
        tv.setText(str);
    }


    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.bt1:
                tv.setText("132 + 56 = " + demo.add(132,56));
                break;
            case R.id.bt2:
                tv.setText(demo.getStringFromJava());
                break;
            case R.id.bt3:
                tv.setText(demo.getStringFromJavaStatic());
                break;
            case R.id.bt4:
//                tv.setText(tools.getStringFromJavaStatic());
                demo.callNormalMethod();
                break;
            case R.id.bt5:
//                tv.setText(tools.getStringFromJavaStatic());
                demo.callStaticMethod();
                break;
            case R.id.bt6:
                tv.setText("" + demo.callNormalMethod2());
                Log.d(TAG, "onClick: " + demo.callNormalMethod2());
                break;
        }
    }
}