#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>      // MPU6050 Slave Device Address


const uint8_t MPU6050SlaveAddress = 0x68; // Select SDA and SCL pins for I2C communication 
const uint8_t scl = D1;
const uint8_t sda = D2;     // sensitivity scale factor respective to full scale setting provided  in datasheet 
const uint16_t AccelScaleFactor = 16384;
const uint16_t GyroScaleFactor = 131; // MPU6050 few configuration register addresses
const uint8_t MPU6050_REGISTER_SMPLRT_DIV   =  0x19;
const uint8_t MPU6050_REGISTER_USER_CTRL    =  0x6A;
const uint8_t MPU6050_REGISTER_PWR_MGMT_1   =  0x6B;
const uint8_t MPU6050_REGISTER_PWR_MGMT_2   =  0x6C;
const uint8_t MPU6050_REGISTER_CONFIG       =  0x1A;
const uint8_t MPU6050_REGISTER_GYRO_CONFIG  =  0x1B;
const uint8_t MPU6050_REGISTER_ACCEL_CONFIG =  0x1C;
const uint8_t MPU6050_REGISTER_FIFO_EN      =  0x23;
const uint8_t MPU6050_REGISTER_INT_ENABLE   =  0x38;
const uint8_t MPU6050_REGISTER_ACCEL_XOUT_H =  0x3B;
const uint8_t MPU6050_REGISTER_SIGNAL_PATH_RESET  = 0x68;
int16_t GyroX, GyroY, GyroZ;

const char* ssid = "wifimu";
const char* password = "wifipassmu";

// Domain Name with full URL Path for HTTP POST Request
const char* server = "http://192.168.10.1:80/insert";

WiFiClient wifiClient;

void setup() {
  Serial.begin(115200);
  Wire.begin(sda, scl);  
  MPU6050_Init();
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WIFI…");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("After 10 seconds the first reading will be displayed");
}

void loop() {
  delay(100);
  double Gx, Gy, Gz;     
  Read_RawValue(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_XOUT_H);    
  Gx = (double)GyroX/GyroScaleFactor;  
  Gy = (double)GyroY/GyroScaleFactor;  
  Gz = (double)GyroZ/GyroScaleFactor;  
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    http.begin(wifiClient,server);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    // Data to send with HTTP POST
    String httpRequestData = "gx=" + String(Gx) + "&gy=" + String(Gy) + "&gz=" + String(Gz);           
    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
    Serial.print(Gx);  
    Serial.print(";"); 
    Serial.print(Gy);  
    Serial.print(";"); 
    Serial.println(Gz);
//    Serial.println(httpRequestData);
//    Serial.print("HTTP Response code is: ");
//    Serial.println(httpResponseCode);
    http.end();
  }
  else {
    Serial.println("WiFi is Disconnected!");
  }
}


void I2C_Write(uint8_t deviceAddress, uint8_t regAddress, uint8_t data)
{  
  Wire.beginTransmission(deviceAddress);  
  Wire.write(regAddress);  Wire.write(data);  
  Wire.endTransmission();   // read all 14 register
}

void Read_RawValue(uint8_t deviceAddress, uint8_t regAddress)
{  
  Wire.beginTransmission(deviceAddress);  
  Wire.write(regAddress);  
  Wire.endTransmission();  
  Wire.requestFrom(deviceAddress, (uint8_t)14);  
  GyroX = (((int16_t)Wire.read()<<8) | Wire.read());  
  GyroY = (((int16_t)Wire.read()<<8) | Wire.read());  
  GyroZ = (((int16_t)Wire.read()<<8) | Wire.read());
}

//configure MPU6050

void MPU6050_Init()
{   
  delay(150);  
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SMPLRT_DIV, 0x07);    I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_1, 0x01);    I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_2, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_CONFIG, 0x00);    I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_GYRO_CONFIG, 0x00);    
  //set +/-250 degree/second full scale  
  
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_CONFIG, 0x00);   // set +/- 2g full scale   I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_FIFO_EN, 0x00);  
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_INT_ENABLE, 0x01);    I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SIGNAL_PATH_RESET,   0x00);   I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_USER_CTRL, 0x00);
}
