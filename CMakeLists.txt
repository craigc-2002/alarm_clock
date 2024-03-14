cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(alarm_clock C CXX ASM)

pico_sdk_init()

add_subdirectory(lib/alarm_clock_hw_lib)

add_executable(alarm_clock
        main.cpp
        alarm_clock.cpp
        ring_alarm.cpp
        alarm_handler.cpp
        time_modification_state.cpp
        display_time_state.cpp
        edit_time_state.cpp
        edit_alarm_state.cpp
        alarm_state.cpp
        change_contrast_state.cpp)

target_include_directories(alarm_clock
        PRIVATE include
)

# target_link_libraries(alarm_clock
#         hardware_i2c
#         hardware_gpio
#         hardware_timer
#         hardware_rtc
#         hardware_irq
#         hardware_pwm
#         hardware_clocks
#         pico_ssd1306)

target_link_libraries(alarm_clock
        hardware_rtc
        alarm-clock-hw-lib
        pico_ssd1306)

pico_add_extra_outputs(alarm_clock)
