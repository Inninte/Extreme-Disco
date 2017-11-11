int sensorPin = A3; // select the input pin for the potentiometer
int sensorValue = 0; // variable to store the value coming from the sensor
int ledGreen = 5;
int ledBlue= 3;
int ledRed = 6;

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin (9600);               
  // initialize the digital pin as an output.
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledRed, OUTPUT); 
}

// the loop routine runs over and over again forever:
void loop() {
  {
  sensorValue = analogRead (sensorPin);
  Serial.println (sensorValue, DEC);
  }

  if (sensorValue > 100){
    setColor(255, 170, 0); 
  }
  else if (sensorValue >75){
    setColor(0, 255, 170); 
  }
  else{
    setColor(170, 0, 255); 
  }
  delay(100);
}

void setColor(int r, int g, int b){
  analogWrite(ledRed, r);
  analogWrite(ledGreen, g);
  analogWrite(ledBlue, b);
}


