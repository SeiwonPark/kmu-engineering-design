#define PIN_LED 13
unsigned int count, toggle;

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
    toggle = toggle_state(toggle);
    digitalWrite(PIN_LED, toggle);
    delay(1000);
}

int toggle_state(int toggle) {
    if (toggle == LOW) {
        return HIGH;
    } else {
        return LOW;
    }
}