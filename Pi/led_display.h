#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H

#include <stdint.h>
#include <stddef.h>

void led_display_init(void);
void update_led_display(const uint32_t *bands, size_t num_bands);

#endif