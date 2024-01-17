/* alarm_clock
 * Craig Cochrane, 2024
 *
 * button.hpp
 *
 * Hardware abstraction layer for alarm clock button inputs
 */

#ifndef ALARM_CLOCK_HAL_HPP
#define ALARM_CLOCK_HAL_HPP

#include "ssd1306.h"
#include "pico/time.h"

// pins with input buttons
#define BUTTON_1 12
#define BUTTON_2 13
#define BUTTON_3 14
#define BUTTON_4 15

class Button{
    public:
        bool pressed;
        bool long_pressed;
        bool held;

        uint64_t get_press_duration_us(void);
        alarm_id_t get_press_timer_alarm_id(void) {return press_timer_alarm_id;}

        void button_pressed(void);
        void button_released(void);
        void long_press_timer_expired(void);

    private:
        absolute_time_t time_pressed;
        alarm_id_t press_timer_alarm_id = 0;
};

// global button variables to store button presses and holds
extern Button button_1;
extern Button button_2;
extern Button button_3;
extern Button button_4;

// button HAL functions
void button_irq_handler(void);
int64_t button_press_timer_callback(alarm_id_t id, void* data);
void setup_buttons(void);

// button event functions
void clear_button_events();

#endif
