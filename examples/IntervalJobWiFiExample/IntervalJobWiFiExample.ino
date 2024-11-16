#include "IntervalJob.h"

// Define the LED pin for indicating WiFi status
#define LED_PIN 2

// Global variable to track WiFi connection status
bool wifiConnected = false;

/**
 * Function to simulate WiFi connection.
 * This will set the `wifiConnected` flag to true and print a message.
 */
void wifiConnect() {
  Serial.println("Connecting to WiFi...");
  wifiConnected = true; // Simulate successful WiFi connection
}

/**
 * Function to send data if WiFi is connected.
 * Creates a new `IntervalJob` to simulate a delayed disconnection after sending data.
 *
 * @return true if data was sent, false if WiFi is not connected.
 */
bool sendData() {
  if (wifiConnected) {
    Serial.println("Sending data...");

    // Create a temporary IntervalJob to simulate WiFi disconnection after 3 seconds
    new IntervalJob(3000, []() {
      wifiConnected = false; // Simulate disconnection
      Serial.println("Disconnected from WiFi!");
    }, 0, true);

    return true; // Data sent successfully
  }
  Serial.println("No WiFi connection!");
  return false; // Data not sent due to no WiFi
}

/**
 * Function to update the LED status based on WiFi connection.
 * LED will turn ON if WiFi is connected and OFF otherwise.
 */
void showWiFiStatus() {
  digitalWrite(LED_PIN, wifiConnected ? HIGH : LOW);
}

// Create an IntervalJob to attempt WiFi connection every 10 seconds
IntervalJob wifiConnectJob(10000, wifiConnect);

// Create an IntervalJob to send data every 5 seconds with 1 second delay in case of failure
IntervalJob sendDataJob(5000, sendData, 1000);

// Create an IntervalJob to update LED status every 200 milliseconds
IntervalJob showWiFiStatusJob(200, showWiFiStatus);

/**
 * Arduino setup function. Runs once at startup.
 */
void setup() {
  Serial.begin(9600);    // Initialize Serial communication for debugging
  pinMode(LED_PIN, OUTPUT); // Set the LED pin as an output
  Serial.println("IntervalJob example started!");
}

/**
 * Arduino loop function. Runs continuously.
 * Calls `IntervalJob::runAll` to execute all registered IntervalJobs.
 */
void loop() {
  IntervalJob::runAll();
}
