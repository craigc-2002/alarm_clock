/* alarm_clock
 * Craig Cochrane, 2023
 *
 * button.cpp
 *
 * Hardware abstraction layer for alarm clock button inputs
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

void Button::button_pressed(void)
{
    pressed = true;
    held = true;
    long_pressed = false;

    // start 1000ms timer for long press, if timer expires before button released then long press is true
    press_timer_alarm_id = add_alarm_in_ms(1000, button_press_timer_callback, this, false); // pointer to the button starting the timer is passed

    time_pressed = get_absolute_time();
}

void Button::button_released(void)
{
    held = false;
    if (press_timer_alarm_id)
    {
        cancel_alarm(press_timer_alarm_id);
        press_timer_alarm_id = 0;
    }
}

void Button::long_press_timer_expired(void)
{
    // if button is still being held after alarm called, then it is a long press
    if (held)
    {
        pressed = false;
        long_pressed = true;
    }else
    {
        long_pressed = false;
    }
}

uint64_t Button::get_press_duration_us(void)
{
    if (held)
    {
        return absolute_time_diff_us(time_pressed, get_absolute_time());
    }else return 0;
}

// GPIO IRQ handler for button press events
void button_irq_handler(void)
{
    // check for button 1 events
    uint32_t event_mask = gpio_get_irq_event_mask(BUTTON_1);
    if (event_mask & GPIO_IRQ_EDGE_RISE)
    {
        gpio_acknowledge_irq(BUTTON_1, GPIO_IRQ_EDGE_RISE);
        button_1.button_pressed();
    }else if (event_mask & GPIO_IRQ_EDGE_FALL)
    {
        gpio_acknowledge_irq(BUTTON_1, GPIO_IRQ_EDGE_FALL);
        button_1.button_released();
    }

    event_mask = gpio_get_irq_event_mask(BUTTON_2);
    if (gpio_get_irq_event_mask(BUTTON_2) & GPIO_IRQ_EDGE_RISE)
    {
        gpio_acknowledge_irq(BUTTON_2, GPIO_IRQ_EDGE_RISE);
        button_2.button_pressed();
    }
    else if (event_mask & GPIO_IRQ_EDGE_FALL)
    {
        gpio_acknowledge_irq(BUTTON_2, GPIO_IRQ_EDGE_FALL);
        button_2.button_released();
    }

    event_mask = gpio_get_irq_event_mask(BUTTON_3);
    if (gpio_get_irq_event_mask(BUTTON_3) & GPIO_IRQ_EDGE_RISE)
    {
        gpio_acknowledge_irq(BUTTON_3, GPIO_IRQ_EDGE_RISE);
        button_3.button_pressed();
    }
    else if (event_mask & GPIO_IRQ_EDGE_FALL)
    {
        gpio_acknowledge_irq(BUTTON_3, GPIO_IRQ_EDGE_FALL);
        button_3.button_released();
    }

    event_mask = gpio_get_irq_event_mask(BUTTON_4);
    if (gpio_get_irq_event_mask(BUTTON_4) & GPIO_IRQ_EDGE_RISE)
    {
        gpio_acknowledge_irq(BUTTON_4, GPIO_IRQ_EDGE_RISE);
        button_4.button_pressed();
    }
    else if (event_mask & GPIO_IRQ_EDGE_FALL)
    {
        gpio_acknowledge_irq(BUTTON_4, GPIO_IRQ_EDGE_FALL);
        button_4.button_released();
    }
}

int64_t button_press_timer_callback(alarm_id_t id, void* data)
{
    Button* button = (Button*) data;
    if (id == button->get_press_timer_alarm_id()) button->long_press_timer_expired();

    return 0; // don't automatically reschedule the alarm
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
