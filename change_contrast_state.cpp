/* alarm_clock
 * Craig Cochrane, 2024
 *
 * change_contrast_state.cpp
 *
 * Implement a concrete class for the state for changing the contrast
 * Overloads the button 2 and 3 press methods to change the display contrast
 */

#include "state_machine/change_contrast_state.hpp"

#include "textRenderer/TextRenderer.h"

void ChangeContrastState::display_task(pico_ssd1306::SSD1306* display)
{
    char mode_display[] = {"Contrast Mode"};
    pico_ssd1306::drawText(display, font_8x8, mode_display, 0, 8);
    display->setContrast(contrast);

    DisplayTimeState::display_task(display);
}

State* ChangeContrastState::button_1_press(void)
{
    return DisplayTimeState::get_instance();
}

State* ChangeContrastState::button_2_press(void)
{
    contrast = 1;
    return NULL;
}

State* ChangeContrastState::button_3_press(void)
{
    contrast = 255;
    return NULL;
}

State* ChangeContrastState::get_instance(void)
{
    static ChangeContrastState instance;
    return &instance;
}
