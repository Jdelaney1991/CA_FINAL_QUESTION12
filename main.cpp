#include "mbed.h"
#include "LSM6DSLSensor.h"

// Define an instance of the accelerometer
DevI2C i2c(I2C_SDA, I2C_SCL);
LSM6DSLSensor acc(&i2c, LSM6DSL_ACC_GYRO_I2C_ADDRESS_LOW);

// Define pins for the RGB LED
PwmOut red_led(LED1);
PwmOut green_led(LED2);
PwmOut blue_led(LED3);

int main() {
    // Initialize the accelerometer
    acc.init(nullptr);

    // Set the LED pins to have a period of 0.001 seconds (1 kHz frequency)
    red_led.period(0.001);
    green_led.period(0.001);
    blue_led.period(0.001);

    while (1) {
        // Read accelerometer data
        int32_t accel_data[3];
        acc.get_x_axes(accel_data);

        // Map accelerometer values to LED brightness range (0 to 1)
        float red_value = static_cast<float>(accel_data[0]) / 32768.0;
        float green_value = static_cast<float>(accel_data[1]) / 32768.0;
        float blue_value = static_cast<float>(accel_data[2]) / 32768.0;

        // Ensure values are within the valid range (0 to 1)
        red_value = fmaxf(0.0, fminf(1.0, red_value));
        green_value = fmaxf(0.0, fminf(1.0, green_value));
        blue_value = fmaxf(0.0, fminf(1.0, blue_value));

        // Update LED brightness
        red_led.write(red_value);
        green_led.write(green_value);
        blue_led.write(blue_value);
    }
}

