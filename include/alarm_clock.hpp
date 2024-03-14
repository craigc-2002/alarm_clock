/* alarm_clock
 * Craig Cochrane, 2024
 *
 * alarm_clock.hpp
 *
 * Implement a state handler class for the alarm clock
 * Contains a state member to keep track of the current state and disptatch method calls accordingly
 */

#ifndef ALARMCLOCK_H
#define ALARMCLOCK_H

#include "state_machine/state.hpp"
#include "event_queue.hpp"
#include "buttons.hpp"

class AlarmClock{
    public:
        AlarmClock(void);

        void process_events(EventQueue* event_queue);
        void display_task(pico_ssd1306::SSD1306* display) {current_state->display_task(display);}

    private:
        State* current_state;

        // TO DO: move these functions to the State - only one function will need to be called with a button number passed in
        State* dispatch_button_press(Button* button);
        State* dispatch_button_long_press(Button* button);
        State* displatch_button_hold(Button* button);
};

#endif