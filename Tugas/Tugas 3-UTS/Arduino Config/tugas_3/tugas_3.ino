#define BLYNK_TEMPLATE_ID "TMPLig32Q184"
#define BLYNK_DEVICE_NAME "SensorHujanForUTS"
#define BLYNK_AUTH_TOKEN "vNF8eiV5CRmdauWisjOB8JuxBV6i85ZZ"

#include <DHT.h>
#define DHTPIN 2 // Digital pin connected to the DHT sensor 
#define DHTTYPE DHT11 //type of sensor in use
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  delay(2000);
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
  //
  float minTemperature = 5.0; float maxTemperature = 50.0;
  float minHumidity = 10; float maxHumidity = 90;
  float minPressure = 50.0; float maxPressure = 105.0;

  String rain = "";
  if(( temperature >= 26.0 && temperature <= 27.0 ) && (humidity >= 76.0 && humidity <= 81.0 ) && (pressure >= 101.01 && pressure <= 101.02 )){
    rain = "Hujan Ringan";
    }
  else if (( temperature >= 27.0 && temperature <= 28.0 ) && (humidity >= 81.0 && humidity <= 82.0 ) && (pressure >= 101.02 && pressure <= 101.03 )){
    rain = "Hujan Sedang";
    }
  else if(( temperature >= 28.0 && temperature <= 30.0 ) && (humidity >= 82.0 && humidity <= 85.0 ) && (pressure >= 101.03 && pressure <= 101.05 )){
    rain = "Hujan Deras";
    }
  else{
    rain = "Unknown";
    }
    Serial.print(temperature);Serial.print(F(";"));
    Serial.print(humidity);Serial.print(F(";"));
    Serial.print(pressure);Serial.print(F(";"));
    Serial.println(rain);
  
}
