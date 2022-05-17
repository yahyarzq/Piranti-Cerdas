void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(0,INPUT); //Button 1
  pinMode(1,INPUT); //Button 2
  pinMode(2,INPUT); //Button 3

  pinMode(8,OUTPUT); // 1ED 1
  pinMode(9,OUTPUT); // LED 2
  pinMode(10,OUTPUT);// LED 3

  pinMode(11,OUTPUT);// Buzzer 1
  pinMode(12,OUTPUT);// Buzzer 2
  pinMode(13,OUTPUT);// Buzzer 3
}

void loop() {
  //delay(1000);
  // put your main code here, to run repeatedly:
  int buttonRed = digitalRead(2);
  int buttonBlue = digitalRead(3);
  int buttonGreen = digitalRead(4);
  
  if (buttonRed == HIGH){
    Serial.println("Bel A menyala");
    digitalWrite(8,HIGH); // Turn On LED
    tone(11,500); // activate Buzzer
    }
  else if (buttonBlue == HIGH){
    Serial.println("Bel B menyala");
    digitalWrite(9,HIGH); // Turn On LED
    tone(12,500); // activate Buzzer
    }
  else if (buttonGreen == HIGH){
    Serial.println("Bel C menyala");
    digitalWrite(10,HIGH); // Turn On LED
    tone(13,500); // activate Buzzer
    }
  else {
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      noTone(11);
      noTone(12);
      noTone(13);
      }
}
