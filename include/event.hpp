/* alarm_clock
 * Craig Cochrane, 2024
 *
 * event.hpp
 *
 * Provide an event class that can be added to a queue 
 */

#ifndef EVENT_H
#define EVENT_H

enum event_type
{
    NONE,
    BUTTON_PRESS,
    BUTTON_LONG_PRESS,
    BUTTON_HOLD
};

class Event{
    public:
        Event(void);
        Event(event_type new_event_type, void* data);

        event_type type;
        void* event_data;
};

#endif
