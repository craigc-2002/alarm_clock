/* alarm_clock
 * Craig Cochrane, 2024
 *
 * alarm_state.cpp
 *
 * Implement a concrete class for the state where the alarm has gone off
 */

#include "state_machine/alarm_state.hpp"

#include "ssd1306.h"
#include "textRenderer/TextRenderer.h"
#include "state_machine/display_time_state.hpp"

void AlarmState::display_task(pico_ssd1306::SSD1306* display)
{
    char mode_display[] = {"Alarm"};
    pico_ssd1306::drawText(display, font_8x8, mode_display, 0, 16);

    DisplayTimeState::display_task(display);
}

State* AlarmState::button_1_press(void)
{
    return DisplayTimeState::get_instance();
}

State* AlarmState::button_2_press(void)
{
    return DisplayTimeState::get_instance();
}


State* AlarmState::button_3_press(void)
{
    return DisplayTimeState::get_instance();
}


State* AlarmState::button_4_press(void)
{
    return DisplayTimeState::get_instance();
}

State* AlarmState::get_instance(void)
{
    static AlarmState instance;
    return &instance;
}

