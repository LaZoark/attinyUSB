#define LAYOUT_US_INTERNATIONAL
#include <Arduino.h>
#include <DigiKeyboard.h>
#include "timer.h"

uint8_t led_state = LOW;
TickTimer led_task(100);
TickTimer usb_demo_task(5000);
TickTimer press_shift_task(10000);

void test_usb_hello();
void press_shift();


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  DigiKeyboard.enableLEDFeedback();
}

void loop() {
  led_task.loop([]() {
    led_state = !led_state;
    digitalWrite(LED_BUILTIN, led_state);
    }
  );

  usb_demo_task.loop(&test_usb_hello);
  press_shift_task.loop(&press_shift);

}

void test_usb_hello() {
  digitalWrite(LED_BUILTIN, HIGH);
  // DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.print("[");
  DigiKeyboard.print(millis());
  DigiKeyboard.print("]: Hello!");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  digitalWrite(LED_BUILTIN, LOW);
  // DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  // DigiKeyboard.delay(500);
}

void press_shift() {
  digitalWrite(LED_BUILTIN, HIGH);
  DigiKeyboard.sendKeyStroke(0, KEY_LEFT_SHIFT);
  digitalWrite(LED_BUILTIN, LOW);
}