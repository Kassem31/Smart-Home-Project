#include <avr/io.h>
#include "SPI.h"
#include "STD_MESSAGES.h"
#include "std_macros.h"

void SPI_vInitMaster (void)
{
	DDRB |= (1 << DDB5) | (1 << DDB7) | (1 << DDB4);//Set the port B mosi(master out slave in ) ,port B ss(slave select),sck(spi clock)  pins as output
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);//Enable the SPI,master mode ,Set the clock speed to F/16
}

void SPI_vInitSlave (void)
{
	DDRB |= (1<<SPI_MOSI) ;//Set the port B miso(master in slave out ) pin as output
	SPCR |= (1<<SPE);//Enable the SPI
}

uint8 SPI_ui8TransmitRecive (uint8 data)
{
	PORTB &= ~(1 << DDB4);
	//_delay_ms(2);
	SPDR = data;
	while(!(SPSR & (1 << SPIF)));
	PORTB |= (1 << DDB4);
	//_delay_ms(2);
	return SPDR;
}