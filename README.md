# DSP-Final-Project-Team11
Our project is a FFT audio sampler using a raspberry pi and an FPGA.

This is the github for our FFT audio sampler. We have a raspberry pi with an ADC converter that will take analog signals from a mic and send them to an FGPA. The FPGA will then do the FFT math and send it back to the pi through an SPI bus, which will then send the results out to a 8x8 matrix displaying the range of frequencies and how frequent they are.
