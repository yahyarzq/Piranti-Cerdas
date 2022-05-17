#include "DHT.h"
#define DHTPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);

}
float readPressure(int pin){
  float val = analogRead(pin);
  if (isnan(val)){
    Serial.println(F("Failed to read from MPX sensor!"));
    return;
    }
  float pressure = ((val/1023)+0.095)/0.009;
  // float pressure = ((float)val/(float)1023+0.095)/0.009;
  return pressure;
  }

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  
  float pressure = readPressure(A0);
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(temperature, humidity, false);

  // condition 1
  if (hic < 45.0 && pressure < 80.0){
    digitalWrite(2,HIGH);
    noTone(5);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
  }
  // condition 2
  else if (( hic >= 45.0 && hic < 55.0 ) && (pressure >= 80.0 && pressure <= 100.0 )){
    digitalWrite(3,HIGH);
    noTone(5);
    digitalWrite(2,LOW);
    digitalWrite(4,LOW);
  }
  // condition 3
  else if (hic >= 55.0 && pressure > 100.0 ){
    digitalWrite(4,HIGH);
    tone(5,5000);
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


    Serial.println();
    Serial.print("------");
    Serial.println();
    Serial.print(F("Humidity: "));Serial.print(humidity);Serial.print(F("% "));
    Serial.println();
    Serial.print(F("Temperature: "));Serial.print(temperature);Serial.print(F("°C "));
    Serial.println();
    Serial.print(F("Heat index: "));Serial.print(hic);Serial.print(F("°C "));
    Serial.println();
    Serial.print("Pressure: ");Serial.print(pressure);Serial.print("kPa");
    Serial.println();
}
