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
#include <cstdio>

void ChangeContrastState::display_task(pico_ssd1306::SSD1306* display)
{
    char mode_display[] = {"Display contrast"};
    pico_ssd1306::drawText(display, font_8x8, mode_display, 0, 16);

    // display contrast in %
    char contrast_display[5];
    sprintf(contrast_display, "%d%%", ((contrast*100)/255));

    int contrast_x_pos = 104;
    if (contrast == 255) contrast_x_pos = 96;

    pico_ssd1306::drawText(display, font_8x8, contrast_display, contrast_x_pos, 28);

    display->setContrast(contrast);

    DisplayTimeState::display_task(display);
}

State* ChangeContrastState::button_1_press(void)
{
    return DisplayTimeState::get_instance();
}

State* ChangeContrastState::button_2_press(void)
{
    if (contrast < 255) contrast += 10;
    return NULL;
}

State* ChangeContrastState::button_3_press(void)
{
    if (contrast > 5) contrast -= 10;
    return NULL;
}

State* ChangeContrastState::button_2_hold(void)
{
    return button_2_press();
}

State* ChangeContrastState::button_3_hold(void)
{
    return button_3_press();
}

State* ChangeContrastState::get_instance(void)
{
    static ChangeContrastState instance;
    return &instance;
}
