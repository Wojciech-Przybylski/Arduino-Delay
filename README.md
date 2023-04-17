# Project Title

PWM Signal Processing with Atmel AVR Microcontroller

## Description

This project contains an example code for setting up an Atmel AVR microcontroller to read analog input data, store it in a delay buffer, and output a Pulse Width Modulation (PWM) signal based on the stored data.

## Requirements

- Atmel AVR microcontroller (tested on ATmega328P)
- AVR-GCC compiler
- AVRDUDE programmer

## Usage

1. Clone the repository to your local machine.
2. Open the `pwm_signal_processing.c` file in your favorite text editor or IDE.
3. Adjust the `MAX_DELAY` constant to set the desired length of the delay buffer (up to 2000 samples).
4. Compile the code using the AVR-GCC compiler: `avr-gcc -mmcu=atmega328p -Wall -Os -o pwm_signal_processing.elf pwm_signal_processing.c`
5. Convert the ELF file to a HEX file using the AVR objcopy tool: `avr-objcopy -j .text -j .data -O ihex pwm_signal_processing.elf pwm_signal_processing.hex`
6. Program the HEX file to the AVR microcontroller using AVRDUDE: `avrdude -p atmega328p -c stk500v2 -P /dev/ttyUSB0 -U flash:w:pwm_signal_processing.hex`
   * Note: adjust the AVRDUDE command to match your specific programmer and AVR microcontroller configuration.

Once the code is programmed to the AVR microcontroller, it will continuously read analog input data on ADC channel 0 and store the high byte of the result in a delay buffer. The delay buffer acts as a simple delay line, allowing for a delay of up to `MAX_DELAY` samples. The PWM output is updated in the interrupt service routine, where the high and low bytes of the delay buffer value are concatenated and added to a constant value of 0x8000 to make "input" a signed 16-bit value. The calculated "input" value is then used to update the PWM output.

## License

This code is released under the MIT License. See the `LICENSE` file for more details.
