/* alarm_clock
 * Craig Cochrane, 2024
 *
 * alarm_state.hpp
 *
 * Implement a concrete class for the state where the alarm has gone off
 */

#ifndef ALARM_STATE_H
#define ALARM_STATE_H

#include "state_machine/display_time_state.hpp"
#include "ssd1306.h"

class AlarmState : public DisplayTimeState
{
    public:
        void display_task(pico_ssd1306::SSD1306* display) override;

        State* button_1_press(void) override;
        State* button_2_press(void) override;
        State* button_3_press(void) override;
        State* button_4_press(void) override;

        static State* get_instance(void);
};

#endif
