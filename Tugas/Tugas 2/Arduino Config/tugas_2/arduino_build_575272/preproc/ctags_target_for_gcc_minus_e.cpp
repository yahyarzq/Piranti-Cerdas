# 1 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino"
# 2 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino" 2


DHT dht(2 /* Digital pin connected to the DHT sensor */, DHT11 /*type of sensor in use*/);

void setup() {
  // put your setup code here, to run once:
  delay(2000);
  Serial.begin(9600);
  dht.begin();
  pinMode(3,0x1); // Pin for LED
  pinMode(4,0x1); // Pin for Buzzer
  }
// Read Pressure from sensor and return pressure value
float readPressure(int pin){
  float pressVal = analogRead(pin);
  if (isnan(pressVal)){
    Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 18 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino" 3
                  (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 18 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino"
                  "Failed to read from MPX sensor!"
# 18 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino" 3
                  ); &__c[0];}))
# 18 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino"
                  )));
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
    Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 32 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino" 3
                  (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 32 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino"
                  "Failed to read from DHT sensor!"
# 32 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino" 3
                  ); &__c[0];}))
# 32 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino"
                  )));
    return;
  }
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(temperature, humidity, false);

  float minTemperature = 5.0; float maxTemperature = 50.0;
  float minHumidity = 10; float maxHumidity = 90;
  float minPressure = 50.0; float maxPressure = 105.0;

  String rain = "";
  if(humidity > 60.0 && temperature < 20.0 && pressure > 80){
    rain = "Heavy Rain";
    }
  else if(humidity < 60.0 && temperature > 20.0 && pressure < 80){
    rain = "Dry";
    }
  else{
    rain = "Unknown";
    }
    Serial.print(temperature);Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 52 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino" 3
                                          (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 52 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino"
                                          ";"
# 52 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino" 3
                                          ); &__c[0];}))
# 52 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino"
                                          )));
    Serial.print(humidity);Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 53 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino" 3
                                       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 53 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino"
                                       ";"
# 53 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino" 3
                                       ); &__c[0];}))
# 53 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino"
                                       )));
    Serial.print(pressure);Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 54 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino" 3
                                       (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 54 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino"
                                       ";"
# 54 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino" 3
                                       ); &__c[0];}))
# 54 "C:\\Users\\PC\\Documents\\Piranti Cerdas\\Tugas 2\\Arduino Config\\tugas_2\\tugas_2.ino"
                                       )));
    Serial.println(rain);

}
