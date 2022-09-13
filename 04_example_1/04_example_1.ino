#define PIN_LED 13

void setup() {
    pinMode(PIN_LED, OUTPUT);
}

void loop() {
    digialWrite(PIN_LED, 0);
}
