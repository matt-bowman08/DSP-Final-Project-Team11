#ifndef ADC_SAMPLER_H
#define ADC_SAMPLER_H

#include <stdint.h>
#include <stddef.h>

void adc_sampler_init(void);
void collect_audio_samples(int16_t *samples, size_t num_samples);

#endif