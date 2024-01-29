/* alarm_clock
 * Craig Cochrane, 2024
 *
 * edit_alarm_state.hpp
 *
 * Implement a concrete class for the state for changing the alarm time value
 * Overloads the button press methods to update the time set for the alarm
 */

#include "state_machine/edit_alarm_state.hpp"

#include "hardware/rtc.h"
#include "hardware/gpio.h"
#include "textRenderer/TextRenderer.h"
#include "shapeRenderer/ShapeRenderer.h"
#include "alarm_handler.hpp"
#include "state_machine/display_time_state.hpp"
#include <cstdio>

void EditAlarmState::exit(void)
{
    // set the date parts of the alarm to -1, meaning the alarm will run every day
    modified_time.day = -1;
    modified_time.dotw = -1;
    modified_time.month = -1;
    modified_time.year = -1;

    rtc_set_alarm(&modified_time, alarm_irq_handler); // set new time to RTC alarm

    if (alarm_active)
    {
        rtc_enable_alarm();
        gpio_put(PICO_DEFAULT_LED_PIN, true);
    }else
    {
        gpio_put(PICO_DEFAULT_LED_PIN, false);
        rtc_disable_alarm();
    }

    sleep_ms(64); // delay to allow the RTC alarm to update
}

void EditAlarmState::display_task(pico_ssd1306::SSD1306* display)
{
    char mode_display[] = {"Alarm Edit Mode"};
    pico_ssd1306::drawText(display, font_8x8, mode_display, 0, 16);

    char alarm_set_display[10];
    if (alarm_active)
    {
        strcpy(alarm_set_display, "Alarm set");
    }else
    {
        strcpy(alarm_set_display, "Alarm off");
    }
    pico_ssd1306::drawText(display, font_8x8, alarm_set_display, 0, 0);

    if (setting_alarm)
    {
        pico_ssd1306::drawLine(display, 0, 10, 72, 10);
    }

    TimeModificationState::display_task(display, false);
}

/* 
 * since the alarms don't check for any of the date fields,
 * the button press and hold methods need to be overridden to 
 * check whether they have reached the end of the time fields
 * 
 * An additional state is also added to allow the user to select the alarm on/off
 */

State* EditAlarmState::button_1_press(void)
{
    if (setting_alarm)
    {
        setting_alarm = false;
        current_time_part = SECOND;
        return NULL;
    }

    return TimeModificationState::button_1_press();
}

State* EditAlarmState::button_2_press(void)
{
    if (setting_alarm)
    {
        alarm_active = !alarm_active;
        return NULL;
    }

    return TimeModificationState::button_2_press();
}

State* EditAlarmState::button_3_press(void)
{
    if (setting_alarm)
    {
        alarm_active = !alarm_active;
        return NULL;
    }
    
    return TimeModificationState::button_3_press();
}

State* EditAlarmState::button_4_press(void)
{
    if (setting_alarm)
    {
        setting_alarm = false;
        return DisplayTimeState::get_instance();
    }

    if (current_time_part == SECOND)
    {
        setting_alarm = true;
    }
    
    return TimeModificationState::button_4_press();
}

State* EditAlarmState::button_1_hold(void)
{
    if (setting_alarm)
    {
        current_time_part = SECOND;
        setting_alarm = false;
        return NULL;
    }else if (current_time_part == HOUR)
    {
        setting_alarm = true;
        return NULL;
    }

    return TimeModificationState::button_1_hold();
}

State* EditAlarmState::button_2_hold(void)
{
    if (setting_alarm)
    {
        alarm_active = !alarm_active;
        return NULL;
    }

    return TimeModificationState::button_2_hold();
}

State* EditAlarmState::button_3_hold(void)
{
    if (setting_alarm)
    {
        alarm_active = !alarm_active;
        return NULL;
    }
    
    return TimeModificationState::button_3_hold();
}


State* EditAlarmState::button_4_hold(void)
{
    if (setting_alarm)
    {
        current_time_part = HOUR;
        setting_alarm = false;
        return NULL;
    }

    if (current_time_part == SECOND)
    {
        setting_alarm = true;
    }
    
    return TimeModificationState::button_4_hold();
}

// getter for a pointer to a static state instance
State* EditAlarmState::get_instance(void)
{
    static EditAlarmState instance;
    return &instance;
}
