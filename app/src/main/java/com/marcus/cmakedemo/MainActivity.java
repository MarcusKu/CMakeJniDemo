package com.marcus.cmakedemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.util.Arrays;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private JniNative jniNative = null;
    private Button btnA;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        jniNative = new JniNative();
        TextView textView = findViewById(R.id.tv_text);
        btnA = findViewById(R.id.btn_a);
        btnA.setOnClickListener(this);

        int[] array = new int[]{2, 3, 4};
        String text = "StringFromJni : " + jniNative.getStringFromJni() + "\n" +
                "原始数组：" + Arrays.toString(array) + "\n" +
                "修改是否成功 ： " + jniNative.jniArrayAdd(array, 4) + "\n" +
                "修改后的数组 ： " + Arrays.toString(array) + "\n" +
                "GetStringCritical ： " + jniNative.getStringCritical("12345") + "\n" +
                "GetStringUTFRegion ： " + jniNative.getStringUTFRegion("12345") + "\n" +
                "Array Sum = " + jniNative.sumIntArray(new int[]{1, 2, 3, 4, 5}) + "\n" +
                "float 3d array = " + Arrays.toString(jniNative.intToInt2DArray());
        textView.setText(text);
        float[][][] arrays = jniNative.intToInt2DArray();
        for (int i = 0; i < arrays.length; i++) {
            for (int i1 = 0; i1 < arrays[i].length; i1++) {
                for (int i2 = 0; i2 < arrays[i][i1].length; i2++) {
                    Log.d("MainActivity", "" + arrays[i][i1][i2]);
                }
            }
        }

    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_a:
                jniNative.dataTypeMapping(Byte.decode("21"), Short.decode("12"), 'c', 100, 999.9f, 88.8d, 132132, true, new int[]{1, 2, 3}, "哈哈", new ObjectClass());
                break;
        }

    }
}
