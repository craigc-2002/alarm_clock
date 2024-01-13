/* alarm_clock
 * Craig Cochrane, 2023
 *
 * button.hpp
 *
 * Hardware abstraction layer for alarm clock inputs and outputs
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
        bool held;
        int get_press_duration(void);

    private:
        int time_pressed;
};

// global button variables to store button presses and holds
extern Button button_1;
extern Button button_2;
extern Button button_3;
extern Button button_4;

// button HAL functions
void button_irq_handler(void);
void setup_buttons(void);

// button event functions
void clear_button_events();

#endif
