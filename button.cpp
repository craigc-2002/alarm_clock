/* alarm_clock
 * Craig Cochrane, 2023
 *
 * button.cpp
 *
 * Hardware abstraction layer for alarm clock inputs and outputs
 */

#include "button.hpp"

#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "pico/time.h"
#include "ssd1306.h"
#include "textRenderer/TextRenderer.h"
#include <cstdio>

// global button variables to store button presses and holds
Button button_1;
Button button_2;
Button button_3;
Button button_4;

// GPIO IRQ handler for button press events
void button_irq_handler(void)
{
    // check for button 1 events
    uint32_t event_mask = gpio_get_irq_event_mask(BUTTON_1);
    if (event_mask & GPIO_IRQ_EDGE_RISE)
    {
        gpio_acknowledge_irq(BUTTON_1, GPIO_IRQ_EDGE_RISE);
        button_1.pressed = true;
        button_1.held = true;
    }else if (event_mask & GPIO_IRQ_EDGE_FALL)
    {
        gpio_acknowledge_irq(BUTTON_1, GPIO_IRQ_EDGE_FALL);
        button_1.held = false;
    }

    event_mask = gpio_get_irq_event_mask(BUTTON_2);
    if (gpio_get_irq_event_mask(BUTTON_2) & GPIO_IRQ_EDGE_RISE)
    {
        gpio_acknowledge_irq(BUTTON_2, GPIO_IRQ_EDGE_RISE);
        button_2.pressed = true;
        button_2.held = true;
    }
    else if (event_mask & GPIO_IRQ_EDGE_FALL)
    {
        gpio_acknowledge_irq(BUTTON_2, GPIO_IRQ_EDGE_FALL);
        button_2.held = false;
    }

    event_mask = gpio_get_irq_event_mask(BUTTON_3);
    if (gpio_get_irq_event_mask(BUTTON_3) & GPIO_IRQ_EDGE_RISE)
    {
        gpio_acknowledge_irq(BUTTON_3, GPIO_IRQ_EDGE_RISE);
        button_3.pressed = true;
        button_3.held = true;
    }
    else if (event_mask & GPIO_IRQ_EDGE_FALL)
    {
        gpio_acknowledge_irq(BUTTON_3, GPIO_IRQ_EDGE_FALL);
        button_3.held = false;
    }

    event_mask = gpio_get_irq_event_mask(BUTTON_4);
    if (gpio_get_irq_event_mask(BUTTON_4) & GPIO_IRQ_EDGE_RISE)
    {
        gpio_acknowledge_irq(BUTTON_4, GPIO_IRQ_EDGE_RISE);
        button_4.pressed = true;
        button_4.held = true;
    }
    else if (event_mask & GPIO_IRQ_EDGE_FALL)
    {
        gpio_acknowledge_irq(BUTTON_4, GPIO_IRQ_EDGE_FALL);
        button_4.held = false;
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

    gpio_set_irq_enabled(BUTTON_1, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BUTTON_2, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BUTTON_3, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BUTTON_4, GPIO_IRQ_EDGE_FALL, true);

    irq_set_enabled(IO_IRQ_BANK0, true);
}
