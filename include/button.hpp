/* alarm_clock
 * Craig Cochrane, 2024
 *
 * button.hpp
 *
 * Hardware abstraction layer for alarm clock button inputs
 */

#ifndef ALARM_CLOCK_HAL_HPP
#define ALARM_CLOCK_HAL_HPP

#include "pico/time.h"

#include "event_queue.hpp"

// pins with input buttons
#define BUTTON_1 12
#define BUTTON_2 13
#define BUTTON_3 14
#define BUTTON_4 15

class Button{
    public:
        int num;

        Button(int button_num);

        bool long_pressed;
        bool held;

        uint64_t get_press_duration_us(void);
        alarm_id_t get_press_timer_alarm_id(void) {return press_timer_alarm_id;}
        alarm_id_t get_press_repeat_alarm_id(void) {return press_repeat_alarm_id;}

        void button_pressed(void);
        void button_released(void);
        void button_held(void);
        void long_press_timer_expired(void);

        void attach_event_queue(EventQueue* queue);

    private:
        absolute_time_t time_pressed;

        alarm_id_t press_repeat_alarm_id = 0;
        alarm_id_t press_timer_alarm_id = 0;

        EventQueue* event_queue;
};

// button HAL functions
void button_irq_handler(void);
int64_t button_press_timer_callback(alarm_id_t id, void* data);
int64_t button_repeat_timer_callback(alarm_id_t id, void* data);
void setup_buttons(EventQueue* event_queue);

#endif
