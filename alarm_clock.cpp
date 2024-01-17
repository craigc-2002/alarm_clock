/* alarm_clock
 * Craig Cochrane, 2024
 *
 * alarm_clock.cpp
 *
 * Implement a state handler class for the alarm clock
 * Contains a state member to keep track of the current state and disptatch method calls accordingly
 */

#include "alarm_clock.hpp"

#include "hardware/rtc.h"
#include "hardware/gpio.h"

#include "state_machine/display_time_state.hpp"
#include "button.hpp"

AlarmClock::AlarmClock(void)
{
    // initialise the RTC
    // set clock to start at 00:00 on Mon, 1st Jan 2024
    datetime_t t {
            .year = 2024,
            .month = 01,
            .day = 01,
            .dotw = 01,
            .hour = 00,
            .min = 00,
            .sec = 00
    };

    rtc_init();
    rtc_set_datetime(&t);

    // set output pin for Pico on-board LED on Pin 25
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    current_state = new DisplayTimeState;
}

void AlarmClock::process_event()
{
    State* new_state = NULL;

    if (button_1.held) new_state = current_state->button_1_hold();
    if (button_2.held) new_state = current_state->button_2_hold();
    if (button_3.held) new_state = current_state->button_3_hold();
    if (button_4.held) new_state = current_state->button_4_hold();

    if (button_1.pressed) 
    {
        new_state = current_state->button_1_press();
        button_1.pressed = false;
    }

    if (button_2.pressed)
    {
        new_state = current_state->button_2_press();
        button_2.pressed = false;
    }

    if (button_3.pressed)
    {
        new_state = current_state->button_3_press();
        button_3.pressed = false;
    }

    if (button_4.pressed)
    {
        new_state = current_state->button_4_press();
        button_4.pressed = false;
    }

    if (button_1.long_pressed) 
    {
        new_state = current_state->button_1_long_press();
        button_1.long_pressed = false;
    }

    if (button_2.long_pressed)
    {
        new_state = current_state->button_2_long_press();
        button_2.long_pressed = false;
    }

    if (button_3.long_pressed)
    {
        new_state = current_state->button_3_long_press();
        button_3.long_pressed = false;
    }

    if (button_4.long_pressed)
    {
        new_state = current_state->button_4_long_press();
        button_4.long_pressed = false;
    }

    if (new_state != NULL)
    {
        current_state = new_state;
    }
}
