/* alarm_clock
 * Craig Cochrane, 2024
 *
 * edit_time_state.hpp
 *
 * Implement a concrete class for the state for changing the clock time value
 * Overloads the button 2 and 3 press methods to get the time from the RTC and update it
 */

#ifndef EDIT_TIME_STATE_H
#define EDIT_TIME_STATE_H

#include "time_modification_state.hpp"


class EditTimeState : public TimeModificationState
{
    public:
        EditTimeState() = default;

        virtual void entry(void);
        virtual void exit(void);
        
        void display_task(pico_ssd1306::SSD1306* display);
        virtual State* button_2_press(void);
        virtual State* button_3_press(void);

        static State* get_instance(void);
};

#endif
