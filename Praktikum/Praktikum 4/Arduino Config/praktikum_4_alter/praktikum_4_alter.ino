
#define BLYNK_PRINT SwSerial
#include <SoftwareSerial.h>
SoftwareSerial SwSerial(11, 12); // RX, TX
#define BLYNK_MSG_LIMIT 20
#include <BlynkSimpleStream.h>
#include <DHT.h>
#define BLYNK_TEMPLATE_ID "TMPL4szN4kvU"
#define BLYNK_DEVICE_NAME "PRAKTIKUM 4 PIRANTI CERDAS 2022"
#define BLYNK_AUTH_TOKEN "RY_D1oT8tsxfuUSJVWL4UGqDZBB7eavn"
char auth[] = BLYNK_AUTH_TOKEN;
#define DHTPIN 10          // What digital pin we're connected to
#define DHTTYPE DHT11     // DHT 11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
BlynkTimer timer2;
WidgetLED ledblue(V6);
WidgetLED ledgreen(V7);
WidgetLED ledred(V8);



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

float kPatoAtm(float pressure){
  float kpa2atm = 0.00986923267;
  float value = kpa2atm*pressure;
  return value;
  }
void sendSensor()
{
  float pressure = readPressure(A0);
  float kpa2atm = 0.00986923267;
  float pressureAtm = kpa2atm*pressure;
  //float pressureAtm = kPatoAtm(pressure);
  
  //float pressVal = analogRead(A0);
  //float pressure = ((pressVal/1023)+0.095)/0.009;
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  // Compute heat index in Celsius (isFahreheit = false)
  float heatindex = dht.computeHeatIndex(temperature, humidity, false);

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
    // condition 1
  if (heatindex >= 0 && heatindex < 41.0){
    digitalWrite(2,HIGH);
    noTone(5);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
  }
  // condition 2
  else if ( heatindex >= 41.0 && heatindex < 54.0 ){
    digitalWrite(3,HIGH);
    noTone(5);
    digitalWrite(2,LOW);
    digitalWrite(4,LOW);
  }
  // condition 3
  else if (heatindex >= 54.0 ){
    digitalWrite(4,HIGH);
    tone(5,1000);
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
  }
  else {
    Serial.println();
    Serial.print("Error");
    
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    noTone(5);

    }

}

void getSensor()
{
  float pressure = readPressure(A0);
  float kpa2atm = 0.00986923267;
  float pressureAtm = kpa2atm*pressure;
  //float pressureAtm = kPatoAtm(pressure);
  
  //float pressVal = analogRead(A0);
  //float pressure = ((pressVal/1023)+0.095)/0.009;
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  // Compute heat index in Celsius (isFahreheit = false)
  float heatindex = dht.computeHeatIndex(temperature, humidity, false);

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  delay(1000);
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  //Blynk.virtualWrite(V2, pressure);
  Blynk.virtualWrite(V3, heatindex);
  Blynk.virtualWrite(V4, pressure);// in kPa
  Blynk.virtualWrite(V5, pressureAtm);

    // condition 1
  if (heatindex >= 0 && heatindex < 41.0){
    if (ledgreen.getValue() || ledred.getValue()) {
      ledgreen.off();
      delay(1000);
      ledred.off();
      }
    delay(1000);
    ledblue.on();
    //Blynk.virtualWrite(V6, 1);
    //Blynk.virtualWrite(V7, 0);
    //Blynk.virtualWrite(V8, 0);
  }
  // condition 2
  else if ( heatindex >= 41.0 && heatindex < 54.0 ){
    if (ledblue.getValue() || ledred.getValue()) {
      ledblue.off();
      delay(1000);
      ledred.off();
      }
    delay(1000);
    ledgreen.on();
    //Blynk.virtualWrite(V7, 1);
    //Blynk.virtualWrite(V6, 0);
    //Blynk.virtualWrite(V8, 0);
  }
  // condition 3
  else if (heatindex >= 54.0 ){
    if (ledblue.getValue() || ledgreen.getValue()) {
      ledblue.off();
      delay(1000);
      ledgreen.off();
      }
    delay(1000);
    ledred.on();
    delay(1000);
    //Blynk.virtualWrite(V8, 1);
    //Blynk.virtualWrite(V6, 0);
    //Blynk.virtualWrite(V7, 0);
  }
  else {
    //ledblue.off();
    //ledgreen.off();
    //ledred.off();
    //Blynk.virtualWrite(V6, 0);
    //Blynk.virtualWrite(V7, 0);
    //Blynk.virtualWrite(V8, 0);
    }

}
void setup()
{
  Serial.begin(9600);
  SwSerial.begin(9600);
  Blynk.begin(Serial, auth);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
  timer2.setInterval(1000L, getSensor);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
}

void loop()
{
  Blynk.run();
  timer.run();
  timer2.run();
}
