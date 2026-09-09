/*--delay.c--*/

/* ---------- MICROSECOND DELAY ---------- */
void delay_us(unsigned int tdly)
{
	// Approximate delay for microseconds
	// Multiplying to match CPU clock cycles
	tdly *= 12;

	// Busy-wait loop
	while(tdly--);
}

/* ---------- MILLISECOND DELAY ---------- */
void delay_ms(unsigned int tdly)
{
	// Approximate delay for milliseconds
	tdly *= 12000;

	// Busy-wait loop
	while(tdly--);
}

/* ---------- SECOND DELAY ---------- */
void delay_s(unsigned int tdly)
{
	// Approximate delay for seconds
	tdly *= 12000000;

	// Busy-wait loop
	while(tdly--);
}
