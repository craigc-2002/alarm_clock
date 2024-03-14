/* alarm_clock
 * Craig Cochrane, 2024
 *
 * buzzer.hpp
 *
 * Hardware abstraction layer for passive buzzer output
 * Tones can be played on the buzzer by outputting a square wave at the desired frequency
 */

class Buzzer
{
    public:
        Buzzer(int pin_num);

        void tone(int frequency);
        void off(); // turn off the PWM output, leaving the output low

    private:
        int pwm_pin;
        int pwm_slice;
};

// getter for buzzer on alarm clock board
Buzzer get_buzzer(void);
