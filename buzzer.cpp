/* alarm_clock
 * Craig Cochrane, 2024
 *
 * buzzer.cpp
 *
 * Hardware abstraction layer for passive buzzer output
 * Tones can be played on the buzzer by outputting a square wave at the desired frequency
 */

#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#include "buzzer.hpp"

#define CLK_DIV 255

Buzzer::Buzzer(int pin_num)
{
    pwm_pin = pin_num;
    gpio_set_function(pwm_pin, GPIO_FUNC_PWM);
    pwm_slice = pwm_gpio_to_slice_num(pwm_pin);

    // set the clock divider to 255
    // max audible range is 20kHz so high output frequencies not needed
    pwm_set_clkdiv(pwm_slice, CLK_DIV);
    
    this->off();
}

void Buzzer::tone(int frequency)
{
    if (frequency > 0) // prevent divide by 0
    {
        // set PWM registers to output square wave at correct frequency
        
        // pwm max count = pwm clock / buzzer frequency
        uint32_t pwm_clock_hz = clock_get_hz(clk_sys) / CLK_DIV;
        int pwm_period = pwm_clock_hz / frequency;
        int pwm_pulse = pwm_period / 2; // 50% duty cycle

        pwm_set_wrap(pwm_slice, pwm_period);
        pwm_set_gpio_level(pwm_pin, pwm_pulse);

        pwm_set_enabled(pwm_slice, true);
    }else
    {
        this->off();
    }
}

void Buzzer::off(void)
{
    pwm_set_enabled(pwm_slice, false);

    // initialise PWM top, compare and counter registers to 0
    pwm_set_wrap(pwm_slice, 0);
    pwm_set_gpio_level(pwm_pin, 0);
    pwm_set_counter(pwm_slice, 0);

    // toggle the PWM output on and off to set output to 0
    pwm_set_enabled(pwm_slice, true);
    pwm_set_enabled(pwm_slice, false);
}

Buzzer get_buzzer(void)
{
    static Buzzer buzzer(10);
    return buzzer;
}
