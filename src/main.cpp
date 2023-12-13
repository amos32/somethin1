#include <Arduino.h>
#define throttle 3
#define br 4
#define tr 5
#define bl 6
#define tl 7  
#define center 532

bool states[4] = {LOW,LOW,LOW,LOW};

volatile bool fw = true;
volatile unsigned long last=0;
unsigned long lastM=0;



void update(){
  
for(int i=0; i<4; ++i)
  digitalWrite(4+i,states[i]);  
}


void forward(){

  states[0]=HIGH;
  states[1]=LOW;
  states[2]=LOW;
  states[3]=HIGH;
  update();
}

void reverse(){

  states[0]=LOW;
  states[1]=HIGH;
  states[2]=HIGH;
  states[3]=LOW;
  update();
}

void breaks(){
  
  states[0]=LOW;
  states[1]=LOW;
  states[2]=LOW;
  states[3]=LOW;
  update();
}

void swap(){

  if(millis()-last>20){
    fw = !fw;
    if(fw)
      forward();
    else
      reverse();

    last=millis();
    }
}


void setup() {
  // put your setup code here, to run once:
pinMode(A0,INPUT);
pinMode(throttle,OUTPUT);
for(int i=4; i<8; ++i)
  pinMode(i,OUTPUT);

forward();
pinMode(2,INPUT_PULLUP);
//attachInterrupt(digitalPinToInterrupt(2),swap,FALLING);
//Serial.begin(9600);
}

void motion(){

  int th = analogRead(A0);
  if (th>=center){
    forward();
    analogWrite(throttle, (th-center)/float(1023-center)*255);  
  }
  else{
    reverse();
    analogWrite(throttle, (center-th)/float(center)*255);  
  }
  
}
void loop() {
  // put your main code here, to run repeatedly:
  if (millis()-lastM > 10){
    motion();
    lastM=millis();
  }
}