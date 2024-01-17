/* alarm_clock
 * Craig Cochrane, 2024
 *
 * time_modification_state.cpp
 *
 * Implement a base class for the states of the alarm clock that involve changing a time value to inherit
 * Defines public methods for dealing with button presses and protected methods for changing time values
 */

#include "state_machine/time_modification_state.hpp"

#include "state_machine/display_time_state.hpp"
#include "textRenderer/TextRenderer.h"
#include "shapeRenderer/ShapeRenderer.h"
#include "display.hpp"

// class for states that edit a time value one part at a time
TimeModificationState::TimeModificationState()
{
    current_time_part = TimeModificationState::HOUR;
}

void TimeModificationState::display_task(pico_ssd1306::SSD1306* display)
{
    display_date_time(display, &modified_time);

    // draw line over part of the time currently being edited
    switch (current_time_part)
    {
        case HOUR:
        {
            pico_ssd1306::drawLine(display, TIME_X, TIME_Y-2, TIME_X+32, TIME_Y-2);
            break;
        }

        case MINUTE:
        {
            pico_ssd1306::drawLine(display, TIME_X+48, TIME_Y-2, TIME_X+72, TIME_Y-2);
            break;
        }
    }
}

void TimeModificationState::next_time_part(void)
{
    switch (current_time_part)
    {
        case HOUR:
            current_time_part = MINUTE;
            break;
        case MINUTE:
            current_time_part = HOUR;
            break;
    }
}

State* TimeModificationState::button_1_press(void)
{
    if (current_time_part == HOUR)
    {
        return DisplayTimeState::get_instance();
    }else
    {
        next_time_part();
        return NULL;
    }
}

State* TimeModificationState::button_2_press(void)
{
    rtc_get_datetime(&modified_time);
    increment_time();
    rtc_set_datetime(&modified_time);
    return NULL;
}

State* TimeModificationState::button_3_press(void)
{
    rtc_get_datetime(&modified_time);
    decrement_time();
    rtc_set_datetime(&modified_time);
    return NULL;
}

State* TimeModificationState::button_4_press(void)
{
    if (current_time_part == MINUTE)
    {
        current_time_part = HOUR;
        return DisplayTimeState::get_instance();
    }else
    {
        next_time_part();
        return NULL;
    }
}

void TimeModificationState::increment_time(void)
{
    switch (current_time_part)
    {
        case HOUR: 
            {
                modified_time.hour += 1;
                break;
            }
        case MINUTE:
            {
                modified_time.min += 1;
                break;
            }
    }
}

void TimeModificationState::decrement_time(void)
{
    switch (current_time_part)
    {
        case HOUR: 
            {
                modified_time.hour -= 1;
                break;
            }
        case MINUTE:
            {
                modified_time.min -= 1;
                break;
            }
    }
}
