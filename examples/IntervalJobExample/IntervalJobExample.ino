#include "IntervalJob.h"

// Example job that toggles the built-in LED
void toggleLED() {
    static bool state = false;
    digitalWrite(LED_BUILTIN, state);
    state = !state;
}

// Another example job
void printMessage() {
    Serial.println("Hello from IntervalJob!");
}

// Create instances of IntervalJob
IntervalJob ledJob(1000, toggleLED);   // Toggle LED every 1 second
IntervalJob messageJob(2000, printMessage); // Print a message every 2 seconds

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    // Run all registered IntervalJob instances
    IntervalJob::runAll();
}
