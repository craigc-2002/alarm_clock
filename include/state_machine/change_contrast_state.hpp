/* alarm_clock
 * Craig Cochrane, 2024
 *
 * change_contrast_state.hpp
 *
 * Implement a concrete class for the state for changing the contrast
 * Overloads the button 2 and 3 press methods to change the display contrast
 */

#ifndef CHANGE_CONTRAST_STATE_H
#define CHANGE_CONTRAST_STATE_H

#include "state.hpp"
#include "state_machine/display_time_state.hpp"

class ChangeContrastState : public DisplayTimeState
{
    public:
        ChangeContrastState() : contrast(255) {}
        void display_task(pico_ssd1306::SSD1306* display);

        State* button_1_press(void) override;
        State* button_2_press(void) override;
        State* button_3_press(void) override;
        State* button_4_press(void) override;

        State* button_1_long_press(void) {return NULL;}
        State* button_2_long_press(void) {return NULL;}
        State* button_4_long_press(void) {return NULL;}

        State* button_2_hold(void) override;
        State* button_3_hold(void) override;

        static State* get_instance(void);

    private:
        uint8_t contrast;
};

#endif
