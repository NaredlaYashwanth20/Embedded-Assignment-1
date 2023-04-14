// Define ARDUINO_RUNNING_CORE based on CONFIG_FREERTOS_UNICORE
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

// Include necessary libraries
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>

// Declare a semaphore
SemaphoreHandle_t sem;

// Declare variables for pin numbers
int t1_out = 1; // LED for Task 1, connected to pin 1
int f1_in = 19; // Input pin for Task 2 to read frequency, connected to pin 19
int f2_in = 10; // Input pin for Task 3 to read frequency, connected to pin 10
int potPin = 8; // Potentiometer input pin, connected to pin 8
int ERROR_LED = 2; // LED for Task 4 to indicate error, connected to pin 2
int BUTTON_PIN = 18; // Push Button used in Debouncing task connected to pin 18
int LED_PIN = 3; // LED used in Debouncing LED task connected to pin 3

// Declare variables for frequency and time measurements
float f1; // Frequency of Task 2
int f1_1; // Used in Task 5 to scale the frequency read in Task 2
float f1_read; // Frequency time difference of Task 2
unsigned long t1; // Timestamp used to measure time in Task 2
unsigned long t2;
float f2; // Frequency of Task 3
int f2_1; // Used in Task 5 to scale the frequency read in Task 3
float f2_read; // Frequency time difference of Task 3
unsigned long t3; // Timestamp used to measure time in Task 3
unsigned long t4;

// Declare variables for potentiometer measurements
float potval; // The analog data read from the potentiometer
float cal_val = 0; // Used to scale the voltage from 0V to 3.3V
typedef struct { // A struct to hold recent potentiometer values
float a1; // 4th recent value read from potentiometer
float a2; // 2nd recent value read from potentiometer
float a3; // 3rd recent value read from potentiometer
float a4; // Most recent value read from potentiometer
} AnalogData;
AnalogData analogData;
float ana_avg; // Average of recent 4 potentiometer values
float half_max; // Value used as a reference to glow the ERROR_LED

// Declare variables for the LED debouncing task
bool ledState = LOW; // State of LED for debouncing LED task
bool buttonState; // Boolean variable used to check state of button
bool lastButtonState;
uint8_t event; // Event variable used in the LED debouncing task
bool ledOn = false;

// Declare queue handlers
QueueHandle_t q1, q2;

// Task 1: Generate a digital signal and pulse it accordingly
void task1(void *pvParameters)
{
while(1)
{
digitalWrite(t1_out, HIGH);
delayMicroseconds(200);
digitalWrite(t1_out, LOW);
delayMicroseconds(50);
digitalWrite(t1_out, HIGH);
delay
