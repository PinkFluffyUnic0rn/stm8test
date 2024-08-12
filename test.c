#include <stdint.h>

#include "stm8l.h"
#include "string.h"
#include "registers.h"

#define freq 2000

volatile uint16_t adcval;

void gpioinit(void)
{
	setpin(PIN_GROUP_B, 6, PIN_DIR_O, PIN_OM_PP, PIN_OM_OS2);
	setpin(PIN_GROUP_D, 4, PIN_DIR_O, PIN_OM_PP, PIN_OM_OS2);
	setpin(PIN_GROUP_B, 7, PIN_DIR_I, PIN_IM_FLOAT, PIN_IM_EXEN);
}

void EXTI_PORTB_IRQHandler(void) __interrupt(4)
{
	setpinval(PIN_GROUP_B, 6, !getpinval(PIN_GROUP_B, 6));
}

void UART_RXE(void) __interrupt(UARTRX)
{
	char c;

	uartread(&c, 1);
}

void ADC_IRQHandler(void) __interrupt(ADC1)
{
	adcval = adcgetval();
}

int main(void)
{
	disable_interrupt();
	
	setexti(PIN_GROUP_B, EXTI_MODE_FALL);
	gpioinit();
	setclockdiv(CLOCK_DIV_2);
	uartinit(500000);
	tim1cntmode(0x7, 0xffff);
	tim2pwmmode(TIM_PRESCALER_64, freq, freq/10);
	tim4cntmode(TIMX_PRESCALER_8, 0xff);
	adcinit(2);
	i2cinit();

	tim1start();
	tim2start();

	enable_interrupt();

	uint8_t r;
	char s[16];

	r = 0;

	i2cmemread((uint8_t) (0x68 << 1), 117, &r, 1, 10000);

	uint16toa(r, s, 16);
	uartwrites(s);
	uartwrite("\n", 1);

	r = 0x10;
	i2cmemwrite((uint8_t) (0x68 << 1), 28, &r, 1, 10000);

	uint32_t us, us2;

	us = us2 = 0;

	do {
		uint16_t c;

		tim1clearcnt();

		msdelay(1);

		if (us > 10000) {
			uint32_t v;
		
			adcstart();

			v = adcval * (uint32_t) freq / 1024;

			tim2pwmduty(v - 88);

			us = 0;
		}

		//if (us2 >= 250000) {
		if (us2 >= 100000) {
			char s[16];

			uint16toa(adcval, s, 16);
		
			uartwrites(s);
			uartwrite("\n", 1);

			uint8_t data[14];

			memset(data, 0, 14);

			i2cmemread((uint8_t) (0x68 << 1), 59, data, 6,
				10000);

			int16toa(data[0] << 8 | data[1], s, 16);
			uartwrites(s);
			uartwrite("\t", 1);

			int16toa(data[2] << 8 | data[3], s, 16);
			uartwrites(s);
			uartwrite("\t", 1);

			int16toa(data[4] << 8 | data[5], s, 16);
			uartwrites(s);
			uartwrite("\n", 1);

			us2 = 0;
		}
	
		c = tim1getcnt();

		us += (uint32_t) c;
		us2 += (uint32_t) c;
	} while (1);
}
