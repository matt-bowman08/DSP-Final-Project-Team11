# DSP-Final-Project-Team11
Our project is a FFT audio visualizer using the Pico2-Ice development board, with the RP2350 microcontroller and the ICE40UP5K FPGA.

This is the github for our FFT audio sampler. We have a pico with an ADC converter that will take analog signals from a microphone and send them to an FGPA via SPI. The FPGA will then perform the FFT calculations, determine the magnitude of each frequency, and sum them in 8 frequency ranges. It then sends the 8 magnitude values back to the pi through the SPI bus, which will then output the results to an 8x8 matrix.
