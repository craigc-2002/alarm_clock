/* alarm_clock
 * Craig Cochrane, 2024
 *
 * ring_alarm.cpp
 *
 * Functions to play an alarm sound using the buzzer
 */

#include "ring_alarm.hpp"

#include "buzzer.hpp"
#include "hardware/gpio.h"
#include "hardware/irq.h"
#include "pico/time.h"

static alarm_id_t tone_timer_alarm_id;

// list of tones played for the alarm - each note is played sequentially for 500ms
static int alarm_tone_list[] = {220, 247, 277, 330, 370, 415, 370, 330, 277, 277, 277, 277, 247, 247, 247, 247, 0};
int tone_count = 17;
static int current_tone = 0;

#define TONE_DELAY 500000 // time between notes of the alarm tone in microseconds

// callback for timer to play the next tone
int64_t tone_timer_callback(alarm_id_t id, void* data)
{
    int* tone_list = (int*) data;
    get_buzzer().tone(tone_list[current_tone]);
    current_tone = (current_tone+1) % tone_count;
    return TONE_DELAY; // reset timer (in microseconds)
}

void ring_alarm(void)
{
    current_tone = 0;
    tone_timer_alarm_id = add_alarm_in_ms(200, tone_timer_callback, alarm_tone_list, false);
}

void alarm_off(void)
{
    cancel_alarm(tone_timer_alarm_id);
    get_buzzer().off();
}
