/* alarm_clock
 * Craig Cochrane, 2024
 *
 * display.hpp
 *
 * Convenience functions for the alarm clock display
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "ssd1306.h"
#include "pico/time.h"

// text positions on the display
static constexpr int TIME_X = 6;
static constexpr int SEC_X = TIME_X + 80;
static constexpr int TIME_Y = 32;
static constexpr int SEC_Y = TIME_Y + 11;

// display HAL functions
pico_ssd1306::SSD1306 initialise_display(void);
void display_date_time(pico_ssd1306::SSD1306* display, datetime_t* t);

#endif
