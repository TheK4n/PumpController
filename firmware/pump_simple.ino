#define pressure_Aport 0
#define relay_Dport 5



int pressure;
int pressure_min = 180;
int pressure_max = 350;
bool flag;



void setup() {
  Serial.begin(9600);
  pinMode(relay_Dport, OUTPUT);

}

void loop() {

  pressure = analogRead(pressure_Aport);
  Serial.println(pressure);

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
