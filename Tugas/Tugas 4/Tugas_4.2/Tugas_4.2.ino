#include "Sensor_MPU6050.h"
//#include "Wifi_Client.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLfTb0SWGv"
#define BLYNK_DEVICE_NAME "TUGAS 4 PIRANTI CERDAS 20222"
#define BLYNK_AUTH_TOKEN "nBL4q050cEXaoVVV3tL8d_RkyvDODa7T"
#define BLYNK_PRINT Serial
#define PIN_SCL D1
#define PIN_SDA D2

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "kos bct bawah";
char password[] = "Matikanlampu083";

Sensor_MPU6050 mpu(PIN_SCL, PIN_SDA);
//Wifi_Client wifi(ssid, password);
BlynkTimer timer;

void sendSensor() {
  mpu.print();
  double* data = mpu.getData();
  Blynk.virtualWrite(V0, data[0]);
  Blynk.virtualWrite(V1, data[1]);
  Blynk.virtualWrite(V2, data[2]);
  Blynk.virtualWrite(V3, data[3]);
  Blynk.virtualWrite(V4, data[4]);
  Blynk.virtualWrite(V5, data[5]);
  Blynk.virtualWrite(V6, data[6]);
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
  //wifi.begin();
  //Blynk.begin(auth, ssid, password);
  // You can also specify server:
  Blynk.begin(auth, ssid, password, "blynk.cloud", 8080);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(2000L, sendSensor);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run(); // Initiates BlynkTimer

  //wifi.connect();
}
