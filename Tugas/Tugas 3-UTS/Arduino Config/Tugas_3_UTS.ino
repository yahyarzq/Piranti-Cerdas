
#define BLYNK_PRINT SwSerial
#include <SoftwareSerial.h>
SoftwareSerial SwSerial(10, 11); // RX, TX
#include <BlynkSimpleStream.h>
#include <DHT.h>
#define BLYNK_TEMPLATE_ID "TMPLig32Q184"
#define BLYNK_DEVICE_NAME "SensorHujanForUTS"
#define BLYNK_AUTH_TOKEN "vNF8eiV5CRmdauWisjOB8JuxBV6i85ZZ"
char auth[] = BLYNK_AUTH_TOKEN;
#define DHTPIN 2          // What digital pin we're connected to
#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

float readPressure(int pin){
  float pressVal = analogRead(pin);
  if (isnan(pressVal)){
    Serial.println(F("Failed to read from MPX sensor!"));
    return;
    }
  //float pressure = ((pressVal/1023)+0.095)/0.009;
  float pressure = ((pressVal/1023)+0.095)/0.009;
  //float pressure = ((float)pressVal/(float)1023+0.095)/0.009;
  //float pressure = pressVal;
  return pressure;
  }

void sendSensor()
{
  float pressure = readPressure(A0);

  //float pressVal = analogRead(A0);
  //float pressure = ((pressVal/1023)+0.095)/0.009;
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  String rain = "";
  if(( temperature >= 26.0 && temperature <= 27.0 ) && (humidity >= 76.0 && humidity <= 81.0 ) && (pressure <= 101.02 )){
    rain = "Hujan Ringan";
    }
  else if (( temperature >= 27.0 && temperature <= 28.0 ) && (humidity >= 81.0 && humidity <= 82.0 ) && (pressure > 101.02 )&& (pressure < 101.05 )){
    rain = "Hujan Sedang";
    }
  else if(( temperature >= 28.0 && temperature <= 30.0 ) && (humidity >= 82.0 && humidity <= 85.0 ) && (pressure >= 101.05 )){
    rain = "Hujan Deras";
    }
  else{
    rain = "Unknown";
    }
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, pressure);
  Blynk.virtualWrite(V3, rain);
}

void setup()
{
  Serial.begin(9600);
  SwSerial.begin(9600);
  Blynk.begin(Serial, auth);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
