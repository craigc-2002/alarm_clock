/* alarm_clock
 * Craig Cochrane, 2024
 *
 * main.cpp
 *
 * Main program loop for reading inputs, logic and writing to display
 * 
 * To Do:
 * - display function of each button on screen
 * - add stopwatch mode
 * - add thermometer
 * - add RGB
 */

#include "pico/stdlib.h"

#include "alarm_clock.hpp"
#include "event_queue.hpp"
#include "buttons.hpp"
#include "display.hpp"
#include "alarm_handler.hpp"

int main()
{
    AlarmClock alarm_clock;
    EventQueue event_queue;
    pico_ssd1306::SSD1306 display = initialise_display();

    setup_buttons(&event_queue);
    setup_alarm(&event_queue);

    // main program loop
    while (1)
    {
        display.clear();

        alarm_clock.process_events(&event_queue);
        alarm_clock.display_task(&display);

        display.sendBuffer();
        sleep_ms(100);
    }
}

