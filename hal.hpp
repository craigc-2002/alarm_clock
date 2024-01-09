/* alarm_clock
 * Craig Cochrane, 2023
 *
 * hal.h
 *
 * Hardware abstraction layer for alarm clock inputs and outputs
 */

#ifndef ALARM_CLOCK_HAL_HPP
#define ALARM_CLOCK_HAL_HPP

#include "ssd1306.h"
#include "pico/time.h"

// pins with input buttons
#define BUTTON_1 12
#define BUTTON_2 13
#define BUTTON_3 14
#define BUTTON_4 15

// button press flags
extern bool button_1_pressed;
extern bool button_2_pressed;
extern bool button_3_pressed;
extern bool button_4_pressed;

// button HAL functions
void button_irq_handler(void);
void setup_buttons(void);

// button event functions
void clear_button_events();

// text positions on the display
static constexpr int TIME_X = 6;
static constexpr int SEC_X = TIME_X + 80;
static constexpr int TIME_Y = 32;
static constexpr int SEC_Y = TIME_Y + 11;

// display HAL functions
pico_ssd1306::SSD1306 initialise_display(void);
void display_date_time(pico_ssd1306::SSD1306* display, datetime_t* t);

#endif
