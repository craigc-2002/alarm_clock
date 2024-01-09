/* alarm_clock
 * Craig Cochrane, 2023
 *
 * main.cpp
 *
 * Main program loop for reading inputs, logic and writing to display
 * 
 * To Do:
 * - use timer to update display with time every 100ms
 * - sleep the processor between updates
 * - implement holding buttons
 * - display function of each button on screen
 */

#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "hardware/rtc.h"
#include "hardware/irq.h"
#include "pico/stdlib.h"
#include "ssd1306.h"
#include "textRenderer/TextRenderer.h"
#include "shapeRenderer/ShapeRenderer.h"
#include <cstdio>

#include "hal.hpp"

enum mode{
    TIME_DISPLAY,
    TIME_EDIT
};

enum time_edit_part{
    HOUR,
    MIN,
    SEC,
    DAY,
    MONTH,
    YEAR
};

int main()
{
    // initialise the RTC
    // set clock to start at 00:00 on Mon, 1st Jan 2024
    datetime_t t {
            .year = 2024,
            .month = 01,
            .day = 01,
            .dotw = 01,
            .hour = 00,
            .min = 00,
            .sec = 00
    };
    rtc_init();
    rtc_set_datetime(&t);

    pico_ssd1306::SSD1306 display = initialise_display();

    setup_buttons();

    // set output pin for Pico on-board LED on Pin 25
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    mode current_mode = TIME_DISPLAY;
    time_edit_part current_edit_part = HOUR;

    // main program loop
    while (1)
    {
        rtc_get_datetime(&t);
        display.clear();

        // parse button inputs and send information to display depending on current mode
        switch (current_mode)
        {
            case TIME_DISPLAY:
            {
                display_date_time(&display, &t);

                if (button_1_pressed)
                {
                    current_mode = TIME_EDIT;
                    button_1_pressed = false;
                }
                if (button_2_pressed) button_2_pressed = false;
                if (button_3_pressed) button_3_pressed = false;
                if (button_4_pressed) button_4_pressed = false;

                break;
            }

            case TIME_EDIT:
            {
                bool time_updated = false;

                if (button_1_pressed)
                {
                    if (current_edit_part == HOUR)
                    {
                        current_mode = TIME_DISPLAY; // exit from time edit mode
                    }else                    
                    {
                        // change to editing the previous part of the time value
                        switch(current_edit_part)   
                        {
                            case MIN:
                            {
                                current_edit_part = HOUR;
                                break;
                            }
                        }
                    }
                    
                    button_1_pressed = false; // clear button press flag
                }

                if (button_2_pressed)
                {
                    switch (current_edit_part)
                    {
                        case HOUR:
                        {
                            t.hour += 1;
                            break;
                        }

                        case MIN:
                        {
                            t.min += 1;
                            break;
                        }
                    }
                    
                    time_updated = true;
                    button_2_pressed = false;
                }

                if (button_3_pressed)
                {
                    switch (current_edit_part)
                    {
                        case HOUR:
                        {
                            t.hour -= 1;
                            break;
                        }

                        case MIN:
                        {
                            t.min -= 1;
                            break;
                        }
                    }
                    
                    time_updated = true;
                    button_3_pressed = false;
                }

                if (button_4_pressed)
                {
                    if (current_edit_part == MIN)
                    {
                        current_mode = TIME_DISPLAY; // exit from time edit mode
                    }else                    
                    {
                        // change to editing the next part of the time value
                        switch(current_edit_part)   
                        {
                            case HOUR:
                            {
                                current_edit_part = MIN;
                                break;
                            }
                        }
                    }

                    button_4_pressed = false;
                }

                if (time_updated)
                {
                    rtc_set_datetime(&t);
                }

                display_date_time(&display, &t);

                char mode_display[] = {"Edit Mode"};
                pico_ssd1306::drawText(&display, font_8x8, mode_display, 0, 8);

                // draw line over part of the time currently being edited
                switch (current_edit_part)
                {
                    case HOUR:
                    {
                        pico_ssd1306::drawLine(&display, TIME_X, TIME_Y-2, TIME_X+32, TIME_Y-2);
                        break;
                    }

                    case MIN:
                    {
                        pico_ssd1306::drawLine(&display, TIME_X+48, TIME_Y-2, TIME_X+72, TIME_Y-2);
                        break;
                    }
                }
                
                break;
            }
        }
        
        display.sendBuffer();
        sleep_ms(100);
    }
}

