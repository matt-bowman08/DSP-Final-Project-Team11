#include <stdio.h>
#include "pico/stdlib.h"

#include "adc_sampler.h"
#include "fpga_spi.h"
#include "band_processor.h"
#include "max7219_display.h"

#define NUM_SAMPLES 1024
#define NUM_BANDS 8

int16_t samples[NUM_SAMPLES];
uint32_t band_values[NUM_BANDS];

int main() {
    stdio_init_all();

    adc_sampler_init();
    fpga_spi_init();
    max7219_display_init();

    while (true) {
        collect_audio_samples(samples, NUM_SAMPLES);

        fpga_send_samples(samples, NUM_SAMPLES);

        fpga_wait_done();

        fpga_read_band_values(band_values, NUM_BANDS);

        normalize_bands(band_values, NUM_BANDS);

        max7219_display_bars(band_values, NUM_BANDS);

        sleep_ms(10);
    }
}