#include "Sensor_MPU6050.h"
//#include <SimpleTimer.h>

#define PIN_SCL D1
#define PIN_SDA D2

Sensor_MPU6050 mpu(PIN_SCL, PIN_SDA);
//Wifi_Client wifi(ssid, password);
//Simpletimer timer;

void sendSensor() {
  mpu.print();
  double* data = mpu.getData();
  Serial.print(" Ax: ");
  Serial.print(data[0]);
  Serial.print(" Ay: ");
  Serial.print(data[1]);
  Serial.print(" Az: ");
  Serial.print(data[2]);
  Serial.print(" T: ");
  Serial.print(data[3]);
  Serial.print(" Gx: ");
  Serial.print(data[4]);
  Serial.print(" Gy: ");
  Serial.print(data[5]);
  Serial.print(" Gz: ");
  Serial.println(data[6]);
  delay(1000);

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mpu.begin();

  // Setup a function to be called every second
  //timer.setInterval(2000L, sendSensor);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //timer.run(); // Initiates BlynkTimer
  //wifi.connect();
  sendSensor();
  delay(100);
}
