/* alarm_clock
 * Craig Cochrane, 2024
 *
 * main.cpp
 *
 * Main program loop for reading inputs, logic and writing to display
 * 
 * To Do:
 * - add alarm functionality
 * - improve contrast setting
 * 
 * - use timer to update display with time every 100ms
 * - sleep the processor between updates
 * - display function of each button on screen
 */

#include "pico/stdlib.h"

#include "alarm_clock.hpp"
#include "event_queue.hpp"
#include "button.hpp"
#include "display.hpp"

int main()
{
    AlarmClock alarm_clock;
    EventQueue event_queue;
    pico_ssd1306::SSD1306 display = initialise_display();

    setup_buttons(&event_queue);

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

