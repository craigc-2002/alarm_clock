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


void TimeModificationState::entry(void)
{
    current_time_part = TimeModificationState::HOUR;
}

void TimeModificationState::display_task(pico_ssd1306::SSD1306* display)
{
    display_date_time(display, &modified_time);

    // draw line over/under part of the time/date currently being edited
    switch (current_time_part)
    {
        case HOUR:
        {
            pico_ssd1306::drawLine(display, TIME_X, TIME_Y-2, TIME_X+32, TIME_Y-2);
            break;
        }
        case MINUTE:
        {
            pico_ssd1306::drawLine(display, TIME_X+48, TIME_Y-2, TIME_X+80, TIME_Y-2);
            break;
        }
        case SECOND:
        {
            pico_ssd1306::drawLine(display, SEC_X+12, SEC_Y-2, SEC_X+36, SEC_Y-2);
            break;
        }
        case DOTW:
        {
            pico_ssd1306::drawLine(display, 0, 10, 24, 10);
            break;
        }
        case DAY:
        {
            pico_ssd1306::drawLine(display, 32, 10, 48, 10);
            break;
        }
        case MONTH:
        {
            pico_ssd1306::drawLine(display, 56, 10, 72, 10);
            break;
        }
        case YEAR:
        {
            pico_ssd1306::drawLine(display, 80, 10, 112, 10);
            break;
        }
    }
}

void TimeModificationState::next_time_part(void)
{
    // increment the part of the time currently being changed
    // if it is YEAR, wrap back around to HOUR
    if (current_time_part == YEAR)
    {
        current_time_part = HOUR;
    }else
    {
        current_time_part = static_cast<time_part>((static_cast<int>(current_time_part) + 1));
    }
}

void TimeModificationState::previous_time_part(void)
{
    // decrement the part of the time currently being changed
    // if it is HOUR, wrap back around to YEAR
    if (current_time_part == HOUR)
    {
        current_time_part = YEAR;
    }else
    {
        current_time_part = static_cast<time_part>((static_cast<int>(current_time_part) - 1));
    }
}

State* TimeModificationState::button_1_press(void)
{
    if (current_time_part == HOUR)
    {
        return DisplayTimeState::get_instance();
    }else
    {
        previous_time_part();
        return NULL;
    }
}

State* TimeModificationState::button_2_press(void)
{
    increment_time();
    return NULL;
}

State* TimeModificationState::button_3_press(void)
{
    decrement_time();
    return NULL;
}

State* TimeModificationState::button_4_press(void)
{
    if (current_time_part == YEAR)
    {
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
        case SECOND:
        {
            modified_time.sec += 1;
            break;
        }
        case DOTW:
        {
            modified_time.dotw += 1;
            break;
        }
        case DAY:
        {
            modified_time.day += 1;
            break;
        }
        case MONTH:
        {
            modified_time.month += 1;
            break;
        }
        case YEAR:
        {
            modified_time.year += 1;
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
        case SECOND:
        {
            modified_time.sec -= 1;
            break;
        }
        case DOTW:
        {
            modified_time.dotw -= 1;
            break;
        }
        case DAY:
        {
            modified_time.day -= 1;
            break;
        }
        case MONTH:
        {
            modified_time.month -= 1;
            break;
        }
        case YEAR:
        {
            modified_time.year -= 1;
            break;
        }
    }
}