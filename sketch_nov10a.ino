#include "pitches.h"
const int sensorPin = A3;
int sensorValue = 0;

int mx = 0;
int mn = 1023;
short maxC = 0;
short minC = 0;
float range = 1;
int prev = 50;
int studyPeriod = 10000;
const int buzzerPin = 8;

const int p1 = 2;
const int p2 =3;
const int p3 =4;
const int p4 = 5;
const int p5 = 6;
const int p6 = 7;

void Glis(int pin, int note1, int note2, int rate) { // from someone else's github
  // Glissando = Slide
  // Slides up or down from note1 to note2
  // rate = 0 is fast and can be increased to slow the effect down
  if (note1 < note2)
  {
    //Slide up
    int i = note1;
    while (i < note2)
    {
      tone(pin, i);
      delay(rate);
      i++;
    }
  }
  else
  {
    //Slide down
    int i = note1;
    while (i > note2)
    {
      tone(pin,i);
      delay(rate);
      i--;
    }
  }
  noTone(pin);
}

void Trem(int pin, int note, int length, int rate) { // from someone else's github
   // Tremolo = Fast repetition of a note
  // note = the note (from pitches.h)
  // length = duration of the effect in msec
  // rate = number of repetitions

  int note_duration = length/rate;
  int pauseBetweenNotes = rate * (1 + rate/length);

  for (int i = 0; i <= rate; i++)
  {
    tone(pin, note, note_duration);
    delay(pauseBetweenNotes);
    noTone(pin);
  } 
}

void BeepBoop() {
  Glis(buzzerPin, NOTE_C3, NOTE_C4, 5);
  digitalWrite(p1,HIGH);
  delay(1000);
  digitalWrite(p1,LOW);
  Trem(buzzerPin, NOTE_C3, 1000, 30);
}

void setup() {
  Serial.begin (9600);
  // Start off with the LED off.
  setColourRgb(0,0,0);
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(p4, OUTPUT);
  pinMode(p5, OUTPUT);
  pinMode(p6, OUTPUT);
  digitalWrite(p6, LOW);
  digitalWrite(p1, LOW);
  digitalWrite(p2, LOW);
  digitalWrite(p3, LOW);
  digitalWrite(p4, LOW);
  digitalWrite(p5, LOW);
  BeepBoop();
}

void loop() {

      sensorValue = 10*analogRead(sensorPin);
      Serial.println(sensorValue, DEC); 

      if(sensorValue > mx + 5*range){
        digitalWrite(p1,HIGH);
        digitalWrite(p2,HIGH);
        digitalWrite(p3,HIGH);
        digitalWrite(p4,HIGH);
        digitalWrite(p5,HIGH);
        digitalWrite(p6,HIGH);
      }
      else if(sensorValue > mx + range){
        digitalWrite(p1,HIGH);
      }
      else if(sensorValue > mx){
        digitalWrite(p2,HIGH);
      }
      else if(sensorValue > mn + 2.75*range) {
        digitalWrite(p3,HIGH);
      }
      else if(sensorValue > mn + 2*range) {
        digitalWrite(p4,HIGH);
      }
      else if(sensorValue > mn + range) {
        digitalWrite(p5,HIGH);
      }
      else if(sensorValue > mn) {
        digitalWrite(p6,HIGH);
      }
      
      if(sensorValue > mx){
        mx = sensorValue;
        maxC = 0;
      } else {
        maxC += 1;
        if (maxC > 20){
          mx = sensorValue;
          maxC = 0;
        }
      }
      
      if(sensorValue < mn){
        mn = sensorValue;
      } else {
        minC += 1;
        if (minC > 20){
          mn = sensorValue;
          minC = 0;
        }
      }
      
      range = (mx-mn)/4;
    delay(25);
   digitalWrite(p1,LOW);
   digitalWrite(p2,LOW);
   digitalWrite(p3,LOW);
   digitalWrite(p4,LOW);
   digitalWrite(p5,LOW);
   digitalWrite(p6,LOW);

   studyPeriod -= 25;
   if(studyPeriod <= 0){
    BeepBoop();
    studyPeriod = 10000;
   }
}

