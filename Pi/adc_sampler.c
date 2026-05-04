#include "adc_sampler.h"

#include "pico/stdlib.h"
#include "hardware/adc.h"

#define MIC_ADC_GPIO 26
#define MIC_ADC_INPUT 0

// Temporary sample rate guess.
// Change this once your team decides the real sample rate.
#define SAMPLE_PERIOD_US 25   // 25 us = 40 kHz sample rate

void adc_sampler_init(void) {
    adc_init();
    adc_gpio_init(MIC_ADC_GPIO);
    adc_select_input(MIC_ADC_INPUT);
}

void collect_audio_samples(int16_t *samples, size_t num_samples) {
    for (size_t i = 0; i < num_samples; i++) {
        uint16_t raw_adc = adc_read();

        // Convert 0–4095 unsigned ADC value to signed audio value.
        samples[i] = (int16_t)raw_adc - 2048;

        sleep_us(SAMPLE_PERIOD_US);
    }
}