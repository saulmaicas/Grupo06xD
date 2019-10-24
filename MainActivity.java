package com.example.led_rgb;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.util.Log;

import com.google.android.things.pio.Gpio;
import com.google.android.things.pio.GpioCallback;
import com.google.android.things.pio.PeripheralManager;


import java.io.IOException;

/**
 * Skeleton of an Android Things activity.
 * <p>
 * Android Things peripheral APIs are accessible through the class
 * PeripheralManagerService. For example, the snippet below will open a GPIO pin and
 * set it to HIGH:
 *
 * <pre>{@code
 * PeripheralManagerService service = new PeripheralManagerService();
 * mLedGpio = service.openGpio("BCM6");
 * mLedGpio.setDirection(Gpio.DIRECTION_OUT_INITIALLY_LOW);
 * mLedGpio.setValue(true);
 * }</pre>
 * <p>
 * For more complex peripherals, look for an existing user-space driver, or implement one if none
 * is available.
 *
 * @see <a href="https://github.com/androidthings/contrib-drivers#readme">https://github.com/androidthings/contrib-drivers#readme</a>
 */


public class MainActivity extends AppCompatActivity {
    private static final int INTERVALO_LED = 1000; // Intervalo parpadeo (ms)
    private static final String LED_PIN = "BCM13"; // Puerto GPIO del LED
    private static final String LED_PIN_2 = "BCM19"; // Puerto GPIO del LED
    private static final String LED_PIN_3 = "BCM26"; // Puerto GPIO del LED
    private static final String TAG ="gsghdj" ;


    private Gpio ledGpio;
    private Gpio ledGpio2;
    private Gpio ledGpio3;
    @Override
    protected void onCreate(Bundle savedInstanceState) {


        super.onCreate(savedInstanceState); PeripheralManager manager = PeripheralManager.getInstance();
        try {
            ledGpio = manager.openGpio(LED_PIN); // 1. Crea conexión GPIO
            ledGpio2 = manager.openGpio(LED_PIN_2);
            ledGpio3 = manager.openGpio(LED_PIN_3);
            ledGpio.setDirection(Gpio.DIRECTION_OUT_INITIALLY_LOW); // 2. Se indica que es de salida
            ledGpio2.setDirection(Gpio.DIRECTION_OUT_INITIALLY_LOW);
            ledGpio3.setDirection(Gpio.DIRECTION_OUT_INITIALLY_LOW);
            cambiarLuz();

        } catch (IOException e) {
            Log.e(TAG, "Error en PeripheralIO API", e);
        }
        setContentView(R.layout.activity_main);
    }




    private  void cambiarLuz() {
        boolean a=true;
        boolean b =false;

        int i=0;
        while(true){
            try {

                i++;
                if(i>8)i=0;
                switch (i) {
                    case 1:ledGpio.setValue(a);
                        ledGpio2.setValue(a);
                        ledGpio3.setValue(a);
                        break;
                    case 2:ledGpio.setValue(a);// 4. Cambiamos valor LED
                        ledGpio2.setValue(b);
                        ledGpio3.setValue(b);
                        break;
                    case 3: ledGpio.setValue(b);
                        ledGpio2.setValue(a);
                        ledGpio3.setValue(b);
                        break;
                    case 4: ledGpio.setValue(b);
                        ledGpio2.setValue(b);
                        ledGpio3.setValue(a);
                        break;
                    case 5: ledGpio.setValue(a);
                        ledGpio2.setValue(a);
                        ledGpio3.setValue(b);
                        break;
                    case 6: ledGpio.setValue(b);
                        ledGpio2.setValue(a);
                        ledGpio3.setValue(a);
                        break;
                    case 7: ledGpio.setValue(a);
                        ledGpio2.setValue(b);
                        ledGpio3.setValue(a);
                        break;
                    case 8: ledGpio.setValue(b);
                        ledGpio2.setValue(b);
                        ledGpio3.setValue(b);
                        break;
                }
                if(i==7){
                    i=0;
                }
                try {
                    Thread.sleep(5000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            } catch (IOException e) {
                Log.e(TAG, "Error en PeripheralIO API", e);
            }

        }


    };
}
