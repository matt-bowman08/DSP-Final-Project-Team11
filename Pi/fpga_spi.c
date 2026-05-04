#include "fpga_spi.h"

#include "pico/stdlib.h"
#include "hardware/spi.h"

#define SPI_PORT spi0

#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

#define PIN_FPGA_DONE 20

#define SPI_BAUDRATE 1000000  // 1 MHz to start safely

void fpga_spi_init(void) {
    spi_init(SPI_PORT, SPI_BAUDRATE);

    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    gpio_init(PIN_FPGA_DONE);
    gpio_set_dir(PIN_FPGA_DONE, GPIO_IN);
}

static void fpga_select(void) {
    gpio_put(PIN_CS, 0);
}

static void fpga_deselect(void) {
    gpio_put(PIN_CS, 1);
}

void fpga_send_samples(const int16_t *samples, size_t num_samples) {
    fpga_select();

    for (size_t i = 0; i < num_samples; i++) {
        int16_t real = samples[i];
        int16_t imag = 0;

        uint8_t tx_data[4];

        // Send real part high byte, real part low byte,
        // then imaginary high byte, imaginary low byte.
        tx_data[0] = (real >> 8) & 0xFF;
        tx_data[1] = real & 0xFF;
        tx_data[2] = (imag >> 8) & 0xFF;
        tx_data[3] = imag & 0xFF;

        spi_write_blocking(SPI_PORT, tx_data, 4);
    }

    fpga_deselect();
}

void fpga_wait_done(void) {
    while (gpio_get(PIN_FPGA_DONE) == 0) {
        tight_loop_contents();
    }
}

void fpga_read_band_values(uint32_t *bands, size_t num_bands) {
    fpga_select();

    for (size_t i = 0; i < num_bands; i++) {
        uint8_t rx_data[4] = {0};

        // SPI needs to send dummy bytes to receive data.
        spi_read_blocking(SPI_PORT, 0x00, rx_data, 4);

        bands[i] =
            ((uint32_t)rx_data[0] << 24) |
            ((uint32_t)rx_data[1] << 16) |
            ((uint32_t)rx_data[2] << 8)  |
            ((uint32_t)rx_data[3]);
    }

    fpga_deselect();
}