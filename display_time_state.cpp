/* alarm_clock
 * Craig Cochrane, 2024
 *
 * display_time_state.cpp
 *
 * Implement a concrete class for the state for displaying the current time and date
 * Overloads the display_task method to display the time and date
 * Overloads the button long press methods to change to the correct states
 */

#include "state_machine/display_time_state.hpp"

#include "hardware/rtc.h"
#include "ssd1306.h"

#include "state_machine/edit_time_state.hpp"
#include "state_machine/change_contrast_state.hpp"
#include "display.hpp"

void DisplayTimeState::display_task(pico_ssd1306::SSD1306* display)
{
    datetime_t t;
    rtc_get_datetime(&t);
    display_date_time(display, &t);
}

State* DisplayTimeState::button_1_long_press()
{
    return EditTimeState::get_instance();
}

State* DisplayTimeState::button_4_long_press()
{
    return ChangeContrastState::get_instance();
}

State* DisplayTimeState::get_instance(void)
{
    static DisplayTimeState instance;
    return &instance;
}