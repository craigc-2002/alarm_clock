/* alarm_clock
 * Craig Cochrane, 2024
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

#include "event_queue.hpp"

// global button variables to store button presses and holds
static Button button_1(1);
static Button button_2(2);
static Button button_3(3);
static Button button_4(4);

Button::Button(int button_num): num(button_num)
{}

// method called when the button is first pressed
void Button::button_pressed(void)
{
    held = true;

    // start 500ms timer for long press, if timer expires before button released then long press is true
    press_timer_alarm_id = add_alarm_in_ms(500, button_press_timer_callback, this, false); // pointer to the button starting the timer is passed
    time_pressed = get_absolute_time();

    // start 200ms timer to check if the button is still pressed to allow repeated button presses
    press_repeat_alarm_id = add_alarm_in_ms(200, button_repeat_timer_callback, this, false);
    
    // add button press event to the event queue with a pointer to the current button object
    event_queue->add_event(BUTTON_PRESS, this);
}

// method called when the button is released
void Button::button_released(void)
{
    held = false;
    long_pressed = false;

    if (press_timer_alarm_id)
    {
        cancel_alarm(press_timer_alarm_id);
        press_timer_alarm_id = 0;
    }
    if (press_repeat_alarm_id)
    {
        cancel_alarm(press_repeat_alarm_id);
        press_repeat_alarm_id = 0;
    }
}

// method called when the timer for a long press ahs expired and the button is still held down
void Button::long_press_timer_expired(void)
{
    // if button is still being held after alarm called, then it is a long press
    if (held)
    {
        long_pressed = true;

        // add long press event to the queue
        event_queue->add_event(BUTTON_LONG_PRESS, this);
    }else
    {
        long_pressed = false;
    }
}

// method called when the button is being held down after an initial press
void Button::button_held(void)
{
    // start 200ms timer to check if the button is still pressed to allow repeated button presses
    press_repeat_alarm_id = add_alarm_in_ms(200, button_repeat_timer_callback, this, false);

    // add button press event to the event queue with a pointer to the current button object
    // if the long press timer has already gone off, then send a long_press event instead
    event_queue->add_event(BUTTON_HOLD, this);
}

uint64_t Button::get_press_duration_us(void)
{
    if (held)
    {
        return absolute_time_diff_us(time_pressed, get_absolute_time());
    }else return 0;
}

void Button::attach_event_queue(EventQueue* queue)
{
    event_queue = queue;
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

// callback for long button press timer
int64_t button_press_timer_callback(alarm_id_t id, void* data)
{
    Button* button = (Button*) data;
    if (id == button->get_press_timer_alarm_id()) button->long_press_timer_expired();

    return 0; // don't automatically reschedule the alarm
}

// callback for button press repeat timer - checks every 200ms if a button is still being held down
int64_t button_repeat_timer_callback(alarm_id_t id, void* data)
{
    // if button is still being held then call the button press method again
    Button* button = (Button*) data;
    if (id == button->get_press_repeat_alarm_id())
    {
        if (button->held) button->button_held();
    }

    return 0; // don't automatically reschedule the alarm - the button press call will do that if neccessary
}

void setup_buttons(EventQueue* event_queue)
{
    // initialise Pins for button input
    uint32_t button_input_mask = 0;
    button_input_mask |= (1 << BUTTON_1) + (1 << BUTTON_2) + (1 << BUTTON_3) + (1 << BUTTON_4);
    gpio_init_mask(button_input_mask);
    gpio_set_dir_in_masked(button_input_mask);

    // attach EventQueue pointers to each Button object
    button_1.attach_event_queue(event_queue);
    button_2.attach_event_queue(event_queue);
    button_3.attach_event_queue(event_queue);
    button_4.attach_event_queue(event_queue);

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
