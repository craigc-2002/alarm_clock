/* alarm_clock
 * Craig Cochrane, 2024
 *
 * alarm_handler.hpp
 *
 * Implement ISR funcion for the RTC alarm 
 */

#include "event_queue.hpp"

void setup_alarm(EventQueue* queue);
void alarm_irq_handler(void);
