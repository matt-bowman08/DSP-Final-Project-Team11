#include "max7219_display.h"

#include "pico/stdlib.h"

// These are example GPIO pins.
// Change these to match your actual Pico wiring.
#define MAX7219_DIN_PIN  11
#define MAX7219_CS_PIN   13
#define MAX7219_CLK_PIN  10

#define MATRIX_SIZE 8

static void max7219_send_byte(uint8_t data) {
    for (int bit = 7; bit >= 0; bit--) {
        gpio_put(MAX7219_CLK_PIN, 0);

        gpio_put(MAX7219_DIN_PIN, (data >> bit) & 1);

        gpio_put(MAX7219_CLK_PIN, 1);
    }
}

static void max7219_send_command(uint8_t address, uint8_t data) {
    gpio_put(MAX7219_CS_PIN, 0);

    max7219_send_byte(address);
    max7219_send_byte(data);

    gpio_put(MAX7219_CS_PIN, 1);
}

void max7219_display_init(void) {
    gpio_init(MAX7219_DIN_PIN);
    gpio_init(MAX7219_CS_PIN);
    gpio_init(MAX7219_CLK_PIN);

    gpio_set_dir(MAX7219_DIN_PIN, GPIO_OUT);
    gpio_set_dir(MAX7219_CS_PIN, GPIO_OUT);
    gpio_set_dir(MAX7219_CLK_PIN, GPIO_OUT);

    gpio_put(MAX7219_CS_PIN, 1);
    gpio_put(MAX7219_CLK_PIN, 0);

    // MAX7219 setup commands.
    max7219_send_command(0x09, 0x00); // No decode mode
    max7219_send_command(0x0A, 0x04); // Brightness, 0x00 to 0x0F
    max7219_send_command(0x0B, 0x07); // Scan all 8 rows
    max7219_send_command(0x0C, 0x01); // Normal operation, not shutdown
    max7219_send_command(0x0F, 0x00); // Display test off

    max7219_display_clear();
}

void max7219_display_clear(void) {
    for (uint8_t row = 1; row <= 8; row++) {
        max7219_send_command(row, 0x00);
    }
}

void max7219_display_bars(const uint32_t *bands, size_t num_bands) {
    uint8_t rows[MATRIX_SIZE] = {0};

    if (num_bands > MATRIX_SIZE) {
        num_bands = MATRIX_SIZE;
    }

    // Convert 8 band heights into an 8x8 bar graph.
    // bands[col] should already be normalized from 0 to 8.
    for (size_t col = 0; col < num_bands; col++) {
        uint32_t height = bands[col];

        if (height > 8) {
            height = 8;
        }

        for (uint32_t level = 0; level < height; level++) {
            // Bottom row is row 7, top row is row 0.
            uint8_t row = 7 - level;

            // Column 0 is left side.
            rows[row] |= (1 << (7 - col));
        }
    }

    // Send each row to the MAX7219.
    // MAX7219 row addresses are 1 through 8.
    for (uint8_t row = 0; row < MATRIX_SIZE; row++) {
        max7219_send_command(row + 1, rows[row]);
    }
}