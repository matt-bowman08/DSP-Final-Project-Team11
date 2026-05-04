#ifndef MAX7219_DISPLAY_H
#define MAX7219_DISPLAY_H

#include <stdint.h>
#include <stddef.h>

void max7219_display_init(void);
void max7219_display_clear(void);
void max7219_display_bars(const uint32_t *bands, size_t num_bands);

#endif