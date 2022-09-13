void setup() {
    Serial.begin(115200);
    while (!Serial) {
        // wait
    }
}

void loop() {
    Serial.println("Hello World!");
    delay(1000);
}
