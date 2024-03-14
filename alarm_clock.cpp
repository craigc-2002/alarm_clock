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
#include "buttons.hpp"
#include "event.hpp"
#include "event_queue.hpp"

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

    current_state = DisplayTimeState::get_instance();
}

void AlarmClock::process_events(EventQueue* event_queue)
{
    State* new_state = NULL;

    Event event = event_queue->get_event();
    while (event.type != NONE)
    {
        switch (event.type)
        {
            case BUTTON_PRESS:
            {
                Button* button = static_cast<Button*>(event.event_data);
                new_state = dispatch_button_press(button);
                break;
            }

            case BUTTON_LONG_PRESS:
            {
                Button* button = static_cast<Button*>(event.event_data);
                new_state = dispatch_button_long_press(button);
                break;
            }

            case BUTTON_HOLD:
            {
                Button* button = static_cast<Button*>(event.event_data);
                new_state = displatch_button_hold(button);
                break;
            }

            case ALARM:
            {
                new_state = current_state->alarm_ring();
                break;
            }
        }

        event = event_queue->get_event();
    }

    if (new_state != NULL)
    {
        current_state->exit();
        current_state = new_state;
        new_state->entry();
    }
}

State* AlarmClock::dispatch_button_press(Button* button)
{
    State* new_state = NULL;
    switch(button->num)
    {
        case 1:
            new_state = current_state->button_1_press();
            break;
        case 2:
            new_state = current_state->button_2_press();
            break;
        case 3:
            new_state = current_state->button_3_press();
            break;
        case 4:
            new_state = current_state->button_4_press();
            break;
    }

    return new_state;
}

State* AlarmClock::dispatch_button_long_press(Button* button)
{
    State* new_state = NULL;
    switch(button->num)
    {
        case 1:
            new_state = current_state->button_1_long_press();
            break;
        case 2:
            new_state = current_state->button_2_long_press();
            break;
        case 3:
            new_state = current_state->button_3_long_press();
            break;
        case 4:
            new_state = current_state->button_4_long_press();
            break;
    }

    return new_state;
}

State* AlarmClock::displatch_button_hold(Button* button)
{
    State* new_state = NULL;
    switch(button->num)
    {
        case 1:
            new_state = current_state->button_1_hold();
            break;
        case 2:
            new_state = current_state->button_2_hold();
            break;
        case 3:
            new_state = current_state->button_3_hold();
            break;
        case 4:
            new_state = current_state->button_4_hold();
            break;
    }

    return new_state;
}
