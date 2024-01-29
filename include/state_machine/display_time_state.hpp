/* alarm_clock
 * Craig Cochrane, 2024
 *
 * display_time_state.hpp
 *
 * Implement a concrete class for the state for displaying the current time and date
 * Overloads the display_task method to display the time and date
 * Overloads the button long press methods to change to the correct states
 */

#ifndef DISPLAY_TIME_STATE_H
#define DISPLAY_TIME_STATE_H

#include "state.hpp"

class DisplayTimeState : public State
{
    public:
        void display_task(pico_ssd1306::SSD1306* display) override;

        State* button_1_long_press(void) override;
        State* button_2_long_press(void) override;
        State* button_4_long_press(void) override;

        State* alarm_ring(void) override;

        static State* get_instance(void);
};

#endif
