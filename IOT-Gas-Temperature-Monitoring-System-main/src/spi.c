//spi.c
#include "types.h"
#include <LPC21xx.h>
#include "spi_defines.h"

void Init_SPI0(void)
{
	//Cfg p0.4,p0.5,p0.6 as sck0,miso0,mosi0 pins
	
	PINSEL0|=SCK0_PIN|MISO0_PIN|MOSI0_PIN;
	//Cfg SPI settings
	//as Master,Mode3,MSBF
	S0SPCR=(1<<CPHA_BIT)|(1<<CPOL_BIT)|(1<<MSTR_BIT);
	//cfg spi clock freq
	S0SPCCR=14;
	//cfg slave select pin as gpio out pin
	//& ensuring pin is initially high
	IOSET0=1<<SS0_PIN;
	IODIR0|=1<<SS0_PIN;
}

u8 spi0(u8 sByte)
{
	//write to tx/rx buffer
	//which initiates serialization via mosi0 & miso0 
	S0SPDR=sByte;
	//wait until serialization complete
	while(((S0SPSR>>SPIF_BIT)&1)==0);
	//read & return recvd byte,
	//which also automatically clears SPIF_BIT
	return S0SPDR;	
}

