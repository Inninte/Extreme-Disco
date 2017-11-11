int sensorPin = A3; // select the input pin for the potentiometer
int sensorValue = 0; // variable to store the value coming from the sensor
int ledGreen = 2;
int ledYellow= 3;
int ledRed = 4;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin (9600);               
  // initialize the digital pin as an output.
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT); 
}

// the loop routine runs over and over again forever:
void loop() {
  {
  sensorValue = analogRead (sensorPin);
  Serial.println (sensorValue, DEC);
  }

  if (sensorValue > 600){
    digitalWrite(ledGreen, HIGH);   // turn the ledGreen on (HIGH is the voltage level)
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, LOW);
  }
  else if (sensorValue >200){
    digitalWrite(ledGreen, LOW);   // turn the ledGreen on (HIGH is the voltage level)
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, HIGH);
  }
  else{
    digitalWrite(ledGreen, LOW);   // turn the ledGreen on (HIGH is the voltage level)
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledYellow, LOW);
  }
  delay(100);
}
