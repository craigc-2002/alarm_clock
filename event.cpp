/* alarm_clock
 * Craig Cochrane, 2024
 *
 * event.cpp
 *
 * Provide an event class that can be added to a queue 
 */

#include "event.hpp"

Event::Event(event_type new_event_type, void* data): type(new_event_type), event_data(data)
{}

Event::Event(void): type(NONE), event_data(nullptr)
{}
