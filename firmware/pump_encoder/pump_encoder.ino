
// ====Ports====
#define pressure_port A0
#define relay_port 5

// ====Encoder====
#define S1 2
#define S2 3
#define KEY 4

// ====Display====
#define CLK 6
#define DIO 7


// ====Consts====
#define DEBUG 0
#define MIN_PRESSURE 60
#define MAX_PRESSURE 800


// ====Libs====
#include <EncButton.h>
#include <EEPROM.h>
#include <GyverTM1637.h>


int pressure, pressure_low, pressure_high;
bool is_on_pump, is_on_display, display_cur_pressure;
unsigned long last_time1, last_time2, last_time3, last_time_pressure;
const int NUM_READ = 3;

EncButton<EB_TICK, S1, S2, KEY> enc;
GyverTM1637 disp(CLK, DIO);


// ограничивает нижний порог от 0 до верхнего порога
int get_constrained_pressure_low(int pressure_low_local) {
  return constrain(pressure_low_local, MIN_PRESSURE, pressure_high-10);
}

// ограничивает верхний порог от нижнего порога до 800(8 атмосфер)
int get_constrained_pressure_high(int pressure_high_local) {
  return constrain(pressure_high_local, pressure_low+10, MAX_PRESSURE);
}

// растянутое среднее арифметическое
int midArifm2(int newVal) {
  static byte counter = 0;     // счётчик
  static int prevResult = 0; // хранит предыдущее готовое значение
  static int sum = 0;  // сумма
  sum += newVal;   // суммируем новое значение
  counter++;       // счётчик++
  if (counter == NUM_READ) {      // достигли кол-ва измерений
    prevResult = sum / NUM_READ;  // считаем среднее
    sum = 0;                      // обнуляем сумму
    counter = 0;                  // сброс счётчика
  }
  return prevResult;
}

void setup() {
  if (DEBUG) {
      Serial.begin(9600);
      Serial.print("pressure");
      Serial.print(',');
      Serial.print("low");
      Serial.print(',');
      Serial.print("high");
      Serial.print(',');
      Serial.println("status");
  }
  

  pinMode(relay_port, OUTPUT);

  // загрузить пороги из памяти
  EEPROM.get(0, pressure_low);
  EEPROM.get(2, pressure_high);

  disp.clear();
  disp.brightness(5);  // яркость, 0 - 7 (минимум - максимум)
  disp.clear();
  
}

void loop() {



  enc.tick();
  if (enc.isTurn()) {
    disp.clear();
    if (enc.isRight()) {
      pressure_low = get_constrained_pressure_low(pressure_low+10);
      disp.displayInt(pressure_low);
      disp.displayByte(0, _L);
    }
    if (enc.isLeft()) {
      pressure_low = get_constrained_pressure_low(pressure_low-10);
      disp.displayInt(pressure_low);
      disp.displayByte(0, _L);
    }
    if (enc.isRightH()) {
      pressure_high = get_constrained_pressure_high(pressure_high+10);
      disp.displayInt(pressure_high);
      disp.displayByte(0, _H);
    }
    if (enc.isLeftH()) {
      pressure_high = get_constrained_pressure_high(pressure_high-10);
      disp.displayInt(pressure_high);
      disp.displayByte(0, _H);
    }
    is_on_display = true;
    display_cur_pressure = false;
    last_time2 = millis();
  }

  // нажать на энкодер - показать текущее давление
  if (enc.isClick()) {
    display_cur_pressure = true;
    is_on_display = true;
    last_time2 = millis();
  }


  // Если энкодер зажат то записать текущие пороги в энергонезависимую память
  if (enc.isHolded()) {
    EEPROM.put(0, pressure_low);
    EEPROM.put(2, pressure_high);
    disp.displayByte(_S, _A, _U, _E);
    display_cur_pressure = false;
    last_time2 = millis();
  }

  // Датчик давления 0 - 1000 0 - 10 атмосфер
  pressure = midArifm2(pressure);

  // Если прошло 7 сек с момента взаимодействия с энкодером, то отключить дисплей
  if (millis() - last_time2 > 7000) { 
        if (is_on_display) {
          last_time2 = millis();
          is_on_display = false;
          disp.clear();
        }
    }

  if (millis() - last_time1 > 350) { 
        last_time1 = millis();
        if (display_cur_pressure & is_on_display) {
          disp.displayInt(pressure);
        }
    }

  // измерение каждые 1500 мс
  if (millis() - last_time_pressure > 1500) {
        last_time_pressure = millis();

    // Если текущее давление ниже нижнего порога - включить насос
    if (pressure < pressure_low) {
      if (!is_on_pump) {
        digitalWrite(relay_port, HIGH);
        is_on_pump = true;
      }
  
    }
    // Иначе если давление выше верхнего порога - выключить насос
    else if (pressure > pressure_high) {
      if (is_on_pump) {
        digitalWrite(relay_port, LOW);
        is_on_pump = false;
      } 
    }
  }
    
    if (DEBUG) {
      Serial.print(pressure);
      Serial.print(',');
      Serial.print(pressure_low);
      Serial.print(',');
      Serial.print(pressure_high);
      Serial.print(',');
      Serial.println(is_on_pump*100);
    }
}
