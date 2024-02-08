#include <Arduino.h>

/* Simplify the logic from:
```C++
if ((millis() - current_time) >= 200) {
  led_state = !led_state;
  digitalWrite(LED_BUILTIN, led_state);
  current_time = millis();
}
```
to:
```C++
TickTimer led_timer(200);
if ( led_timer.check() ) {
  led_state = !led_state;
  digitalWrite(LED_BUILTIN, led_state);
  led_timer.update();
}
```
*/
class TickTimer {
  private:
    unsigned long time_ms;
    unsigned long current_time;
    void init() {
      current_time = 0;
    }

  public:
    TickTimer(unsigned long _time_ms) {
      time_ms = _time_ms;
      init();
    }

    void update() { current_time = millis(); }
    bool check() { return ( millis() - current_time ) >= time_ms; }
    
    // void callback(void (*func_ptr)()) {
    //     (*func_ptr)();
    // }

/* Simplify the invoke...
```C++
if ( led_task.check() ) {
  led_state = !led_state;
  digitalWrite(LED_BUILTIN, led_state);
  led_task.update();
}
```*/
    void loop(void (*callback)()) {
      if ( this->check() ) {
        (*callback)();
        this->update();
      }
    }
    // void callback(void (*func_ptr)()) {
    //   if ( this->check() ) {
    //     (*func_ptr)();
    //     this->update();
    //   }
    // }
    // void task() {
    //   if ( ( millis() - current_time ) >= time_ms ) {
    //     led_state = !led_state;
    //     digitalWrite(LED_BUILTIN, led_state);
    //     current_time = millis();
    //   }
    // }
};
