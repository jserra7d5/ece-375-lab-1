
/*
This code will cause a TekBot connected to the AVR board to
move forward and when it touches an obstacle, it will reverse
and turn away from the obstacle and resume forward motion.

PORT MAP
Port B, Pin 5 -> Output -> Right Motor Enable
Port B, Pin 4 -> Output -> Right Motor Direction
Port B, Pin 6 -> Output -> Left Motor Enable
Port B, Pin 7 -> Output -> Left Motor Direction
Port D, Pin 5 -> Input -> Left Whisker
Port D, Pin 4 -> Input -> Right Whisker
*/

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define RIGHT_WHISKER (1 << 4) // shift the bit position by 4 to capture the right whisker input bit
#define LEFT_WHISKER (1 << 5) // shift the bit position by 4 to capture the left whisker input bit

int main(void)
{
      // initialize port D for whisker inputs
      DDRD = 0b00000000; // set all pins as inputs
      PORTD = 0b11111111; // enable pullup resistors

      // initialize port B for motor outputs
      DDRB = 0b11110000; // port B pin configuration
      PORTB = 0b11110000; // set the motor outputs to not move initially

      while (1) // loop forever
      {
            uint8_t whisker_state = PIND; // grab the current state of port D's pins

            // checking both whisker inputs, both active low
            if (!(whisker_state & RIGHT_WHISKER) && !(whisker_state & LEFT_WHISKER)) {
                  // both whisker inputs are active
                  PORTB = 0b00000000; // move backward
                  _delay_ms(1000); // wait for one second
                  PORTB = 0b10000000;; // turn right
                  _delay_ms(1000); // wait for one second
                  PORTB = 0b10010000; // resume moving forward
            }

            // only check right whisker input, active low
            else if (!(whisker_state & RIGHT_WHISKER)) {
                  // right whisker input is active
                  PORTB = 0b00000000; // move backward
                  _delay_ms(1000); // wait for one second
                  PORTB = 0b00010000; // turn left
                  _delay_ms(1000); // wait for one second
                  PORTB = 0b10010000; // resume moving forward
            }

            // only check left whisker input, active low
            else if (!(whisker_state & LEFT_WHISKER)) {
                  // left whisker input is active
                  PORTB = 0b00000000; // move backward
                  _delay_ms(1000); // wait for one second
                  PORTB = 0b10000000;; // turn right
                  _delay_ms(1000); // wait for one second
                  PORTB = 0b10010000; // resume moving forward
            }

            else {
                  PORTB = 0b10010000; // move forward
            }
      }
}
