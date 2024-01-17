/* alarm_clock
 * Craig Cochrane, 2024
 *
 * state.hpp
 *
 * Implement a base State class for the different states of the alarm clock to inherit
 * Defines the public interface of a State object
 */

#ifndef STATE_H
#define STATE_H

#include "ssd1306.h"

// base state class for the alarm clock states
class State
{
    public:
        // method to implement the state writing to display
        virtual void display_task(pico_ssd1306::SSD1306* display) = 0;

        // methods to implement events
        // if the state is changed, the new state is returned, if not the NULL is returned 
        virtual State* alarm_ring(void) {return NULL;}

        virtual State* button_1_press(void) {return NULL;}
        virtual State* button_2_press(void) {return NULL;}
        virtual State* button_3_press(void) {return NULL;}
        virtual State* button_4_press(void) {return NULL;}
 
        virtual State* button_1_long_press(void) {return NULL;}
        virtual State* button_2_long_press(void) {return NULL;}
        virtual State* button_3_long_press(void) {return NULL;}
        virtual State* button_4_long_press(void) {return NULL;}

        virtual State* button_1_hold(void) {return NULL;}
        virtual State* button_2_hold(void) {return NULL;}
        virtual State* button_3_hold(void) {return NULL;}
        virtual State* button_4_hold(void) {return NULL;}
};

#endif
