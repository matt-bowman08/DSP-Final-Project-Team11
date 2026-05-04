#include "band_processor.h"

void normalize_bands(uint32_t *bands, size_t num_bands) {
    uint32_t max_value = 1;

    for (size_t i = 0; i < num_bands; i++) {
        if (bands[i] > max_value) {
            max_value = bands[i];
        }
    }

    for (size_t i = 0; i < num_bands; i++) {
        bands[i] = (bands[i] * 8) / max_value;
    }
}