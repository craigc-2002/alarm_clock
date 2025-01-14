/* alarm_clock
 * Craig Cochrane, 2024
 *
 * time_modification_state.hpp
 *
 * Implement a base class for the states of the alarm clock that involve changing a time value to inherit
 * Defines public methods for dealing with button presses and protected methods for changing time values
 */

#ifndef TIME_EDIT_STATE_H
#define TIME_EDIT_STATE_H

#include "state.hpp"

#include "hardware/rtc.h"

// subclass of state for states where a time value is being changed
class TimeModificationState : public State
{
    public:
        virtual void entry(void);

        virtual void display_task(pico_ssd1306::SSD1306* display, bool display_date);

        virtual State* button_1_press(void);
        virtual State* button_2_press(void);
        virtual State* button_3_press(void);
        virtual State* button_4_press(void);
        
        virtual State* button_1_hold(void);
        virtual State* button_2_hold(void);
        virtual State* button_3_hold(void);
        virtual State* button_4_hold(void);

    protected:
        enum time_part{HOUR, MINUTE, SECOND, DOTW, DAY, MONTH, YEAR}; // to keep track of what part of the time is being modified
        time_part current_time_part;
        void next_time_part();
        void previous_time_part();

        datetime_t modified_time;
        virtual void increment_time(void);
        virtual void decrement_time(void);
        virtual void check_time(void);

    private:
        bool allow_hold; // used to disable reacting to button 1 holds when the state has just been entered
};

#endif
