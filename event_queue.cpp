/* alarm_clock
 * Craig Cochrane, 2024
 *
 * event_queue.cpp
 *
 * Provide an event queue that can be accessed from the main program to get input events
 * Uses the queue structure provided in pico/util/queue.h to queue Event objects
 */

#include "event_queue.hpp"

#include "event.hpp"

EventQueue::EventQueue(void)
{
    queue_init(&event_queue, sizeof(Event), max_event_count);
}

void EventQueue::add_event(event_type new_event_type, void* data)
{
    Event new_event(new_event_type, data);
    
    // a non-blocking function is used to add to the event queue
    // if queue is full, the function will fail and the event will not be logged
    // the queue is long eneough that this won't be an issue
    queue_try_add(&event_queue, &new_event); 
}

Event EventQueue::get_event(void)
{
    Event next_event;
    queue_try_remove(&event_queue, &next_event); // if the queue is empty then the function will return and a NONE event will be returned
    return next_event;
}
