/* alarm_clock
 * Craig Cochrane, 2024
 *
 * edit_alarm_state.hpp
 *
 * Implement a concrete class for the state for changing the alarm time value
 * Overloads the button press methods to get the update the time set for the alarm
 */

#ifndef EDIT_ALARM_STATE_H
#define EDIT_ALARM_STATE_H

#include "time_modification_state.hpp"

class EditAlarmState : public TimeModificationState
{
    public:
        void exit(void) override;
        
        void display_task(pico_ssd1306::SSD1306* display) override;

        State* button_1_press(void) override;
        State* button_2_press(void) override;
        State* button_3_press(void) override;
        State* button_4_press(void) override;

        State* button_1_hold(void) override;
        State* button_2_hold(void) override;
        State* button_3_hold(void) override;
        State* button_4_hold(void) override;

        static State* get_instance(void);

    private:
        bool alarm_active;
        bool setting_alarm;
};

#endif
