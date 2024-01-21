/* alarm_clock
 * Craig Cochrane, 2024
 *
 * event_queue.hpp
 *
 * Provide an event queue that can be accessed from the main program to get input events
 * Uses the queue structure provided in pico/util/queue.h to queue Event objects
 */

#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include "pico/util/queue.h"

#include "event.hpp"

class EventQueue
{
    public:
        EventQueue(void);

        void add_event(event_type new_event_type, void* data);
        Event get_event();

    private:
        static constexpr int max_event_count = 128;
        queue_t event_queue;
};

#endif
