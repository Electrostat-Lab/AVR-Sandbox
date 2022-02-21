#include<avr/io.h>
int main(void) {
	   asm volatile("LDI R16, 0b11111111" "\n\t"
			"OUT 0x18, R16" );
 return 0;
}


