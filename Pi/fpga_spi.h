#ifndef FPGA_SPI_H
#define FPGA_SPI_H

#include <stdint.h>
#include <stddef.h>

void fpga_spi_init(void);
void fpga_send_samples(const int16_t *samples, size_t num_samples);
void fpga_wait_done(void);
void fpga_read_band_values(uint32_t *bands, size_t num_bands);

#endif