# IntervalJob Library

The IntervalJob library allows you to manage periodic tasks in Arduino projects efficiently. 
You can define jobs with fixed intervals, and run multiple jobs 
concurrently using static instance management.

## Features

- Execute jobs at fixed intervals.
- Retry jobs until they complete.
- Manage up to 20 instances (customizable).

## Installation

1. Download the library as a ZIP file.
2. In the Arduino IDE, go to **Sketch** > **Include Library** > **Add .ZIP Library**.
3. Select the downloaded ZIP file.

## Usage

### Example: Toggle LED

```cpp
#include "IntervalJob.h"

// Example job function
bool toggleLED() {
    static bool state = false;
    digitalWrite(LED_BUILTIN, state);
    state = !state;
    return true;
}

// Create an IntervalJob instance
IntervalJob ledJob(1000, toggleLED);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    IntervalJob::runAll();
}
