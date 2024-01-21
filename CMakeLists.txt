cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(alarm_clock C CXX ASM)

pico_sdk_init()

add_subdirectory(lib/pico-ssd1306)

add_executable(alarm_clock
        main.cpp
        alarm_clock.cpp
        display.cpp
        button.cpp
        event_queue.cpp
        event.cpp
        time_modification_state.cpp
        display_time_state.cpp
        edit_time_state.cpp
        change_contrast_state.cpp)

target_include_directories(alarm_clock
        PRIVATE include
)

target_link_libraries(alarm_clock
        hardware_i2c
        hardware_gpio
        hardware_timer
        hardware_rtc
        hardware_irq
        pico_ssd1306)

pico_add_extra_outputs(alarm_clock)

