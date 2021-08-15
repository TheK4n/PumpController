#define pressure_port 0
#define relay_port 5

#define CLK 2
#define DT 3
#define SW 4

#define const_pressure_min 0
#define const_pressure_max 100

#include <GyverEncoder.h>



int pressure, pressure_min, pressure_max;
bool flag;

Encoder enc(CLK, DT, SW);


void setup() {
  Serial.begin(9600);
  enc.setType(TYPE2);

}

void loop() {

  // encoder_val = constrain(map(analogRead(encoder_port), 0, 1023, const_pressure_min, const_pressure_max), const_pressure_max);

  enc.tick();
  if (enc.isTurn()) {
    if (enc.isRight()) {
      pressure_min = constrain(pressure_min++, pressure_min, const_pressure_max);
    }
    if (enc.isLeft()) {
      pressure_min = constrain(pressure_min--, pressure_min, const_pressure_max);
    }
    if (enc.isRightH()) {
      pressure_min = constrain(pressure_max++, pressure_min, const_pressure_max);
    }
    if (enc.isLeftH()) {
      pressure_min = constrain(pressure_max--, pressure_min, const_pressure_max);
    }
  }
  
  pressure = analogRead(pressure_port);

  if (pressure < pressure_min) {
    if (!flag) {
      digitalWrite(relay_port, HIGH);
      flag = true;
    }
    
    
  } else {
      if (pressure > pressure_max) {
        if (flag) {
          digitalWrite(relay_port, LOW);
          flag = false;
        }
        
      }
      
    
  }
  
  
  
  
}
