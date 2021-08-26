#define pressure_Aport 0
#define relay_Dport 5

#define S1 2
#define S2 3
#define KEY 4

#define CLK 6
#define DIO 7

#define const_pressure_min 0
#define const_pressure_max 1000

#include <EncButton.h>
#include <EEPROM.h>
#include <GyverTM1637.h>


int pressure, pressure_min, pressure_max;
bool flag;
unsigned long last_time1, last_time2;


EncButton<EB_TICK, S1, S2, KEY> enc;
GyverTM1637 disp(CLK, DIO);



int constraint_pressure(int pressure_) {
  return constrain(pressure_, 0, 1000);
}

void setup() {
  Serial.begin(9600);
  
  pinMode(relay_Dport, OUTPUT);
  
  EEPROM.get(0, pressure_min);
  EEPROM.get(2, pressure_max);

  disp.clear();
  disp.brightness(7);
  disp.clear();
}

void loop() {


  enc.tick();
  if (enc.isTurn()) {
    if (enc.isRight()) {
      pressure_min = constraint_pressure(pressure_min+10);
      disp.displayInt(pressure_min);
    }
    if (enc.isLeft()) {
      pressure_min = constraint_pressure(pressure_min-10);
      disp.displayInt(pressure_min);
    }
    if (enc.isRightH()) {
      pressure_max = constraint_pressure(pressure_max+10);
      disp.displayInt(pressure_max);
    }
    if (enc.isLeftH()) {
      pressure_max = constraint_pressure(pressure_max-10);
      disp.displayInt(pressure_max);
    }
  }

  if (enc.isHolded()) {
    EEPROM.put(0, pressure_min);
    EEPROM.put(2, pressure_max);
  }


  pressure = analogRead(pressure_Aport);

  if (millis() - last_time1 > 850) { 
        last_time1 = millis();
        disp.displayInt(pressure);
    }
  

  if (pressure < pressure_min) {
    if (!flag) {
      digitalWrite(relay_Dport, HIGH);
      flag = true;
    }
    
    
  } else {
      if (pressure > pressure_max) {
        if (flag) {
          digitalWrite(relay_Dport, LOW);
          flag = false;
        }
        
      }
      
    
  }
  
  
  
  
}
