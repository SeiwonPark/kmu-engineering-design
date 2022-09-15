#define PIN_LED 7

int count = 0;
bool toggle = LOW;

void setup() {
    pinMode(PIN_LED, OUTPUT);
}

void loop() {
    digitalWrite(PIN_LED, toggle);
    delay(1000);

    while(count < 10) {
      toggle = set_toggle(toggle);
      digitalWrite(PIN_LED, toggle);
      delay(100);
      count++;
    }
    
    while (1) {
      digitalWrite(PIN_LED, HIGH);
      // done
    }
}

bool set_toggle(bool toggle) {
  return !toggle;
}
