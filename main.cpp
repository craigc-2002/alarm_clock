/* alarm_clock
 * Craig Cochrane, 2024
 *
 * main.cpp
 *
 * Main program loop for reading inputs, logic and writing to display
 * 
 * To Do:
 * - make event queue for button presses and other events
 * - add alarm functionality
 * - improve contrast setting
 * 
 * - use timer to update display with time every 100ms
 * - sleep the processor between updates
 * - display function of each button on screen
 */

#include "pico/stdlib.h"
#include "alarm_clock.hpp"
#include "button.hpp"
#include "display.hpp"

int main()
{
    AlarmClock alarm_clock;
    pico_ssd1306::SSD1306 display = initialise_display();
    setup_buttons();

    // main program loop
    while (1)
    {
        display.clear();

        alarm_clock.process_event();
        alarm_clock.display_task(&display);

        display.sendBuffer();
        sleep_ms(100);
    }
}

