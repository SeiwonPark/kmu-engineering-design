#include <Servo.h>

// Arduino pin assignment

#define PIN_POTENTIOMETER 3 // Potentiometer at Pin A3
// Add IR Sensor Definition Here !!!
#define PIN_IR 0 // Potentiometer at Pin A3
#define PIN_SERVO 10
#define PIN_LED 9

#define _DUTY_MIN 553  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1476 // servo neutral position (90 degree)
#define _DUTY_MAX 2399 // servo full counter-clockwise position (180 degree)
#define _DIST_MIN 100.0   // minimum distance to be measured (unit: mm)
#define _DIST_MAX 250.0   // maximum distance to be measured (unit: mm)

#define LOOP_INTERVAL 20   // Loop Interval (unit: msec)
#define _EMA_ALPHA 0.5

Servo myservo;
unsigned long last_loop_time;   // unit: msec
float dist_ema, dist_prev = _DIST_MAX;

void setup()
{
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  pinMode(PIN_LED, OUTPUT);
  dist_prev = _DIST_MIN; // raw distance output from USS (unit: mm)
  Serial.begin(1000000);
}

void loop()
{
  unsigned long time_curr = millis();
  int a_value, duty;
  float  dist;
  digitalWrite(PIN_LED, LOW);

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;

  // Remove Next line !!!
  a_value = analogRead(PIN_IR);
  // Read IR Sensor value !!!
  // Convert IR sensor value into distance !!!
  // we need distance range filter here !!!
  // we need EMA filter here !!!
  dist = (6762.0/(a_value-9)-4.0)*10.0 - 60.0;

  if (dist <= _DIST_MIN) {
    dist= dist_prev;           // cut lower than minimum
    digitalWrite(PIN_LED, LOW);       // LED OFF
  } else if (dist >= _DIST_MAX) {
    dist= dist_prev;           // Cut higher than maximum
    digitalWrite(PIN_LED, LOW);       // LED OFF
  } else {    // In desired Range
    digitalWrite(PIN_LED, HIGH);       // LED ON      
    dist_prev = dist;
  }

  // Apply ema filter here  
  dist_ema = dist;
  

  // map distance into duty
//  duty = (a_value / 1024) * _DUTY_MAX;
  duty = map(a_value, 0, 1023, _DUTY_MIN, _DUTY_MAX);
//  duty = (a_value - 0) * (_DUTY_MAX- _DUTY_MIN) / (1024- 0) + _DUTY_MIN;
  myservo.writeMicroseconds(duty);

  Serial.print("MIN:"); Serial.print(_DIST_MIN);
  Serial.print(",IR:"); Serial.print(a_value);
  Serial.print(",dist:"); Serial.print(dist);
  Serial.print(",ema:"); Serial.print(dist_ema);
  Serial.print(",servo:"); Serial.print(duty);
  Serial.print(",MAX:"); Serial.print(_DIST_MAX);
  Serial.println("");
  
}