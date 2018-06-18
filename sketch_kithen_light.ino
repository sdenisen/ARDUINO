/*
Author: sdenisen@ymail.com 
Additional use:
	*) PIR Sensor;
	*) L298N Dual Bridge DC Stepper Motor Driver Controller module;
	*) LED line;
	*) DC adaper to 12V/1A.

Description: 
When PIR sensor raise event, after that micro. smoothly turn on the LEDs, 
and they are light 10 minutes in case of no any event appeared otherwise timeout will be reset to 0.  
*/
int PIR_SENSOR_EVENT = 2;
int LED_OUTPUT = 10; // PWM pin
bool is_led_light = false;
int set_start_timer = 0;
int IN_1 = 9;
int IN_2 = 8;
int LED_PIN = 13;



void setup() {
  // put your setup code here, to run once:
  pinMode(PIR_SENSOR_EVENT, INPUT);
  pinMode(LED_OUTPUT, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);  
  Serial.begin(9600);
  Serial.println("--- start ---");  
}


void turnOn(){
  Serial.println("---- turnOn ----");
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);    
  for (int i=0; i<255; i+=1){
    analogWrite(LED_OUTPUT, i);
    delay(100);  
  }    
}
void turnOff(){
  Serial.println("---- turnOff ----");
  for (int i=255; i>0; i-=5){
    analogWrite(LED_OUTPUT, i);
    delay(250);  
  }
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);    
}

void loop() {
  int getted_event = digitalRead(PIR_SENSOR_EVENT);  
  digitalWrite(LED_PIN, getted_event);
  
  if (getted_event == HIGH && is_led_light == false){
    turnOn();
    is_led_light = true;  
    set_start_timer = 0;
  }

  if (set_start_timer == 600){
    turnOff();
    is_led_light = false;  
  }

  if (getted_event == HIGH){
    set_start_timer = 0;
  }  
  
  delay(1000);
  set_start_timer += 1; 
}
