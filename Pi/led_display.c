#include "led_display.h"
#include <stdio.h>

void led_display_init(void) {
    // Add real LED matrix setup later.
}

void update_led_display(const uint32_t *bands, size_t num_bands) {
    printf("Bands: ");

    for (size_t i = 0; i < num_bands; i++) {
        printf("%lu ", bands[i]);
    }

    printf("\n");
}