/* alarm_clock
 * Craig Cochrane, 2024
 *
 * edit_time_state.cpp
 *
 * Implement a concrete class for the state for changing the clock time value
 * Overloads the button 2 and 3 press methods to get the time from the RTC and update it
 */

#include "state_machine/edit_time_state.hpp"

#include "hardware/rtc.h"
#include "textRenderer/TextRenderer.h"

void EditTimeState::entry(void)
{
    rtc_get_datetime(&modified_time);
    TimeModificationState::entry();
}

void EditTimeState::exit(void)
{
    rtc_set_datetime(&modified_time);
    sleep_ms(64); // delay to allow the RTC time to update
}

void EditTimeState::display_task(pico_ssd1306::SSD1306* display)
{
    char mode_display[] = {"Time Edit Mode"};
    pico_ssd1306::drawText(display, font_8x8, mode_display, 0, 16);

    TimeModificationState::display_task(display, true);
}

State* EditTimeState::get_instance(void)
{
    static EditTimeState instance;
    return &instance;
}
