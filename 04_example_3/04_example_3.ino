#define PIN_LED 13
unsigned int count;
bool toggle;

void setup() {
    pinMode(PIN_LED, OUTPUT);
    Serial.begin(115200);
    while (!Serial) {
        // wait
    }
    toggle = HIGH;
}

void loop() {
    Serial.println(++count);
    toggle = set_toggle(toggle);
    digitalWrite(PIN_LED, toggle);
    delay(1000);
}

bool set_toggle(bool toggle) {
    return !toggle;
}