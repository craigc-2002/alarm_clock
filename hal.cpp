/* alarm_clock
 * Craig Cochrane, 2023
 *
 * hal.c
 *
 * Hardware abstraction layer for alarm clock inputs and outputs
 */

#include "hal.hpp"

#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "pico/time.h"
#include "ssd1306.h"
#include "textRenderer/TextRenderer.h"
#include <cstdio>

// globals
bool button_1_pressed = false;
bool button_2_pressed = false;
bool button_3_pressed = false;
bool button_4_pressed = false;

// GPIO IRQ handler for button press events
void button_irq_handler(void)
{
    if (gpio_get_irq_event_mask(BUTTON_1) & GPIO_IRQ_EDGE_RISE)
    {
        gpio_acknowledge_irq(BUTTON_1, GPIO_IRQ_EDGE_RISE);
        button_1_pressed = true;
    }

    if (gpio_get_irq_event_mask(BUTTON_2) & GPIO_IRQ_EDGE_RISE)
    {
        gpio_acknowledge_irq(BUTTON_2, GPIO_IRQ_EDGE_RISE);
        button_2_pressed = true;
    }

    if (gpio_get_irq_event_mask(BUTTON_3) & GPIO_IRQ_EDGE_RISE)
    {
        gpio_acknowledge_irq(BUTTON_3, GPIO_IRQ_EDGE_RISE);
        button_3_pressed = true;
    }

    if (gpio_get_irq_event_mask(BUTTON_4) & GPIO_IRQ_EDGE_RISE)
    {
        gpio_acknowledge_irq(BUTTON_4, GPIO_IRQ_EDGE_RISE);
        button_4_pressed = true;
    }
}

void setup_buttons(void)
{
    // initialise Pins for button input
    uint32_t button_input_mask = 0;
    button_input_mask |= (1 << BUTTON_1) + (1 << BUTTON_2) + (1 << BUTTON_3) + (1 << BUTTON_4);
    gpio_init_mask(button_input_mask);
    gpio_set_dir_in_masked(button_input_mask);

    // set up IRQ handlers for button inputs
    gpio_add_raw_irq_handler_masked(button_input_mask, button_irq_handler);
    gpio_set_irq_enabled(BUTTON_1, GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(BUTTON_2, GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(BUTTON_3, GPIO_IRQ_EDGE_RISE, true);
    gpio_set_irq_enabled(BUTTON_4, GPIO_IRQ_EDGE_RISE, true);
    irq_set_enabled(IO_IRQ_BANK0, true);
}

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
    pico_ssd1306::SSD1306 display = pico_ssd1306::SSD1306(i2c0, 0x3C, pico_ssd1306::Size::W128xH64);
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
