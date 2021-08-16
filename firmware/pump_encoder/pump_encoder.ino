#define pressure_Aport 0
#define relay_Dport 5

#define CLK 2
#define DT 3
#define SW 4

#define const_pressure_min 0
#define const_pressure_max 1000

#include <GyverEncoder.h>
#include <EEPROM.h>


int pressure, pressure_min, pressure_max;
bool flag;

Encoder enc(CLK, DT, SW);


void setup() {
  Serial.begin(9600);
  enc.setType(TYPE2);
  pinMode(relay_Dport, OUTPUT);
  EEPROM.get(0, pressure_min);
  EEPROM.get(2, pressure_max);
}

void loop() {


  enc.tick();
  if (enc.isTurn()) {
    if (enc.isRight()) {
      pressure_min = constrain(pressure_min+10, const_pressure_min, const_pressure_max);
    }
    if (enc.isLeft()) {
      pressure_min = constrain(pressure_min-10, const_pressure_min, const_pressure_max);
    }
    if (enc.isRightH()) {
      pressure_min = constrain(pressure_max+10, const_pressure_min, const_pressure_max);
    }
    if (enc.isLeftH()) {
      pressure_min = constrain(pressure_max-10, const_pressure_min, const_pressure_max);
    }
  }

  if (enc.isClick()) {
    EEPROM.put(0, pressure_min);
    EEPROM.put(2, pressure_max);
  }

  
  pressure = analogRead(pressure_Aport);

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
