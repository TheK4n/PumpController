#define pressure_port A0
#define relay_port 5

#define DEBUG 0

int pressure;
int pressure_min = 180;
int pressure_max = 350;
bool flag;

unsigned long last_time_pressure;


void setup() {

  if (DEBUG) Serial.begin(9600);
  pinMode(relay_port, OUTPUT);

}

void loop() {

  pressure = analogRead(pressure_port);
  if (DEBUG) Serial.println(pressure);


  if (millis() - last_time_pressure > 700) { 
    last_time_pressure = millis();
    
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
}
