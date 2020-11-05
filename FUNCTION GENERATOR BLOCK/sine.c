/*
 * SineWave.c
 *
 * Created: 20/08/2018 4:11:10 PM
 * Author : Sid
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
/* Pin Layout:
	- C0 Bit0
	- C1 Bit1
	- C2 Bit2
	- C3 Bit3
	- C4 Bit4
	- C5 Bit5
	- D6 Bit6
	- D7 Bit7 */ 
uint8_t sine[360]; 
int i = 0;
#define PI 3.14159265

int main(void)
{
	DDRD |= 0b11000000; // Set two highest bits of port D
	DDRC |= 0b00111111; // Set six lowest bits of port C
	int offset = 0;
	for (i = 0; i < 360; i++) { // Calculate and store all sine values in a period
		sine[i] = sinevalues(setamplitude(1.0), setoffset(0), i);
	}
    while (1) {
		setport((uint8_t) (sine[i]));
		i = (i + 1)%360; // Reset i to 0 when array is full
	}
}

void setport(uint8_t a) { // a = byte, & with activated ports of D and C.
	PORTC = (a & 0b00111111);
	PORTD = (a & 0b11000000);
}

int setamplitude(double a) {
	// Scales the amplitude to the bitwise representation
	int b;
	a = a*51; // 51 = 1V
	b = a;
	return b;	
}

int setoffset(double a) {
	// Scales the offset to the bit representation
	int b;
	a = a*51;
	b = a;
	return b;
}

int sinevalues(int amplitude, int offset, int x) {
	/* Amplitude - A double floating point number between 0V - 3V
	   Offset - A double floating point number between -3V - 3V
	   x - An integer between 0 - 360 */
	int conv;
	double freq, y;
	freq = PI / 180;
	y = amplitude*(sin(x*freq)) + offset + amplitude; // Temporary
	conv = y;
	return conv;	
}