/* alarm_clock
 * Craig Cochrane, 2024
 *
 * alarm_handler.hpp
 *
 * Implement ISR funcion for the RTC alarm 
 */

#include "alarm_handler.hpp"

#include "event_queue.hpp"

static EventQueue* event_queue;

void setup_alarm(EventQueue* queue)
{
    event_queue = queue;
}

void alarm_irq_handler(void)
{
    event_queue->add_event(ALARM, nullptr);
}
