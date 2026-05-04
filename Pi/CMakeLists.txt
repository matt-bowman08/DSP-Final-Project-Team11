cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico2)

include(pico_sdk_import.cmake)

project(pico_fft_display C CXX ASM)

pico_sdk_init()

add_executable(pico_fft_display
    src/main.c
    src/adc_sampler.c
    src/fpga_spi.c
    src/band_processor.c
    src/max7219_display.c
)

target_include_directories(pico_fft_display PRIVATE
    src
)

target_link_libraries(pico_fft_display
    pico_stdlib
    hardware_adc
    hardware_spi
)

pico_enable_stdio_usb(pico_fft_display 1)
pico_enable_stdio_uart(pico_fft_display 0)

pico_add_extra_outputs(pico_fft_display)