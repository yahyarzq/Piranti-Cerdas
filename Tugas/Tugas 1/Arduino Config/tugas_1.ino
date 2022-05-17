#include <DHT.h>
#define DHTPIN 2 // Digital pin connected to the DHT sensor 
#define DHTTYPE DHT11 //type of sensor in use
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  pinMode(3,OUTPUT); // Pin for LED
  pinMode(4,OUTPUT); // Pin for Buzzer
  }
// Read Pressure from sensor and return pressure value
float readPressure(int pin){
  float pressVal = analogRead(pin);
  if (isnan(pressVal)){
    Serial.println(F("Failed to read from MPX sensor!"));
    return;
    }
  float pressure = ((pressVal/1023)+0.095)/0.009;
  // float pressure = ((float)pressVal/(float)1023+0.095)/0.009;
  return pressure;
  }
void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float pressure = readPressure(A0);
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(temperature, humidity, false);
  
  float minTemperature = 5.0; float maxTemperature = 50.0;
  float minHumidity = 10; float maxHumidity = 90;
  float minPressure = 50.0; float maxPressure = 105.0;
  
  if ((temperature <= minTemperature || temperature >= maxTemperature )||( humidity <= minHumidity || humidity >= maxHumidity )|| (pressure <= minPressure || pressure >= maxPressure)){
    Serial.println("Warning Extreme Condition");
    digitalWrite(3,HIGH);
    tone(4,5000);
    }
  else{
    digitalWrite(3,LOW);
    noTone(4);
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
}
