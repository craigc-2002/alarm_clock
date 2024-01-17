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

class AlarmClock{
    public:
        AlarmClock(void);

        void process_event();
        void display_task(pico_ssd1306::SSD1306* display) {current_state->display_task(display);}

    private:
        State* current_state;
};

#endif