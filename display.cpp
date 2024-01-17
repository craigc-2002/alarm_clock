/* alarm_clock
 * Craig Cochrane, 2024
 *
 * display.cpp
 *
 * Convenience functions for the alarm clock display
 */

#include "display.hpp"

#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "pico/time.h"
#include "ssd1306.h"
#include "textRenderer/TextRenderer.h"
#include <cstdio>

//static pico_ssd1306::SSD1306* display;

pico_ssd1306::SSD1306 initialise_display(void)
{
    // initialise i2c0
    i2c_init(i2c0, 1000000);

    // Set up default i2c pins (Pins GP4 and GP5)
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    
    // delay to allow the display to initialise
    sleep_ms(250);

    // set up display object for 128x64 display with address 0x3C
    static pico_ssd1306::SSD1306 display = pico_ssd1306::SSD1306(i2c0, 0x3C, pico_ssd1306::Size::W128xH64);
    display.setOrientation(0); // set display to correct orientation

    return display;
}

void display_date_time(pico_ssd1306::SSD1306* display, datetime_t* t)
{
    // prepare the date and time strings to display on the screen
    char date_display[11] = {0};
    snprintf(date_display, 11, "%.2d/%.2d/%.4d", t->day, t->month, t->year);

    char time_display[6] = {0};
    snprintf(time_display, 6, "%.2d:%.2d", t->hour, t->min);

    char sec_display[4] = {0};
    snprintf(sec_display, 4, ":%.2d", t->sec);

    // send temperature to display
    pico_ssd1306::drawText(display, font_8x8, date_display, 0, 0);
    pico_ssd1306::drawText(display, font_16x32, time_display, TIME_X, TIME_Y);
    pico_ssd1306::drawText(display, font_12x16, sec_display, SEC_X, SEC_Y);
}