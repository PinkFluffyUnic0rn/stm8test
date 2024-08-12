#include "registers.h"

#define WAITWHILE(v, t)  		\
do {					\
	int i;				\
					\
	i = 0;				\
	while (v) {			\
		usdelay(t / 100);	\
		++i;			\
	}				\
					\
	if (i >= 100)			\
		return 1;		\
} while (0);

static int clkdiv = 8;

void setclockdiv(enum CLOCK_HSIDIV d)
{
	int i;

	clkdiv = 1;
	for (i = 0; i < d; ++i)
		clkdiv *= 2;

	setbit(CLK_ICKR, CLK_ICKR_HSIEN, 1);

	setval(CLK_CKDIVR, CLK_CKDIVR_HSIDIV, d, 2);

	while (!getbit(CLK_ICKR, CLK_ICKR_HSIRDY));

	set8b(CLK_SWR, CLOCK_MASTER_HSI);

	setbit(CLK_SWCR, CLK_SWCR_SWEN, 1);
}

void usdelay(unsigned char c)
{
	setbit(TIM4_EGR, TIMX_EGR_UG, 1);

	set8b(TIM4_CNTR, 0);

	setbit(TIM4_CR1, TIMX_CR1_CEN, 1);

	while (TIM4_CNTR < c);

	setbit(TIM4_CR1, TIMX_CR1_CEN, 0);
	setbit(TIM4_SR, TIMX_SR_UIF, 0);
}

void _msdelay(unsigned char c)
{
	int i;

	for (i = 0; i < 10 * c; ++i)
		usdelay(100);
}

void msdelay(uint16_t c)
{
	int i;

	for (i = 0; i < (c / 100); ++i)
		_msdelay(100);

	_msdelay(c % 100);
}

#define GETGROUPREG(p, g, r)					\
	switch (g) {						\
	case PIN_GROUP_A:	p = &(PA##_##r);	break;	\
	case PIN_GROUP_B:	p = &(PB##_##r);	break;	\
	case PIN_GROUP_C:	p = &(PC##_##r);	break;	\
	case PIN_GROUP_D:	p = &(PD##_##r);	break;	\
	default:		p = NULL;			\
	}

void setpin(enum PIN_GROUP g, unsigned char p, unsigned char d,
	unsigned char cr1v, unsigned char cr2v)
{
	unsigned char *ddr, *cr1, *cr2;

	GETGROUPREG(ddr, g, DDR)
	GETGROUPREG(cr1, g, CR1)
	GETGROUPREG(cr2, g, CR2)

	setbit(*ddr, p, d);
	setbit(*cr1, p, cr1v);
	setbit(*cr2, p, cr2v);
}

unsigned char getpinval(enum PIN_GROUP g, unsigned char p)
{
	unsigned char *odr;

	GETGROUPREG(odr, g, ODR)
	
	return getbit(*odr, p);
}

void setpinval(enum PIN_GROUP g, unsigned char p, unsigned char v)
{
	unsigned char *odr;

	GETGROUPREG(odr, g, ODR)
	
	setbit(*odr, p, v);
}

void setexti(enum PIN_GROUP g, enum EXTI_SENSBITS sb)
{
	switch (g) {
	case PIN_GROUP_A:
		setval(EXTI_CR1, EXTI_CR1_PAIS, sb, 2);
		break;
	case PIN_GROUP_B:
		setval(EXTI_CR1, EXTI_CR1_PBIS, sb, 2);
		break;
	case PIN_GROUP_C:
		setval(EXTI_CR1, EXTI_CR1_PCIS, sb, 2);
		break;
	case PIN_GROUP_D:
		setval(EXTI_CR1, EXTI_CR1_PDIS, sb, 2);
		break;
	}

	setbit(EXTI_CR2, EXTI_CR2_TLIS, 0);
}

void _tim1init(uint16_t psc, uint16_t arr)
{
	SET16B(TIM1_CNTR, 0x0);
	SET16B(TIM1_PSCR, psc);
	SET16B(TIM1_ARR, arr);	
}

void tim1cntmode(uint16_t psc, uint16_t arr)
{
	_tim1init(psc, arr);

	setbit(TIM1_CR1, TIMX_CR1_URS, 1);
	setbit(TIM1_IER, TIMX_IER_UIE, 0);
	setbit(TIM1_EGR, TIMX_EGR_UG, 1);
}

uint16_t tim1getcnt(void)
{
	uint16_t c;

	c = TIM1_CNTRH << 8;
	c |= TIM1_CNTRL;
	setbit(TIM1_SR1, TIMX_SR_UIF, 0);

	return c;
}

void tim1clearcnt(void)
{
	setbit(TIM1_EGR, TIMX_EGR_UG, 1);
	SET16B(TIM1_CNTR, 0)
}


void _tim2init(enum TIM_PRESCALER psc, uint16_t arr)
{
	SET16B(TIM1_CNTR, 0);
	set8b(TIM2_PSCR, psc);
	SET16B(TIM2_ARR, arr)
}

void tim2cntmode(enum TIM_PRESCALER psc, uint16_t arr)
{
	_tim2init(psc, arr);

	setbit(TIM2_CR1, TIMX_CR1_URS, 1);
	setbit(TIM2_IER, TIMX_IER_UIE, 0);
	setbit(TIM2_EGR, TIMX_EGR_UG, 1);
}

void tim2pwmmode(enum TIM_PRESCALER psc, uint16_t arr, uint16_t ccr)
{
	_tim2init(psc, arr);
	
	SET16B(TIM2_CCR1, ccr)

	setbit(TIM2_CCER1, TIMX_CCER1_CC1P, 1);
	setbit(TIM2_CCER1, TIMX_CCER1_CC1E, 1);
	setval(TIM2_CCMR1, TIMX_CCMR1_OC1M, TIMX_COMPMODE_PWM1, 3);
}

void tim2pwmduty(uint16_t d)
{
	SET16B(TIM2_CCR1, d)
}

void _tim4init(enum TIM_PRESCALER psc, uint8_t arr)
{
	set8b(TIM4_CNTR, 0x0);
	set8b(TIM4_PSCR, psc);
	set8b(TIM4_ARR, arr);
}

void tim4cntmode(enum TIM_PRESCALER psc, uint8_t arr)
{
	_tim4init(psc, arr);

	setbit(TIM4_CR1, TIMX_CR1_URS, 1);
	setbit(TIM4_IER, TIMX_IER_UIE, 0);
	setbit(TIM4_EGR, TIMX_EGR_UG, 1);
}

void uartinit(uint32_t br)
{
	uint32_t uartdiv;
	
	setbit(PD_DDR, 5, 1);
	setbit(PD_DDR, 6, 0);

	setbit(CLK_PCKENR1, CLK_PCKENR1_13, 1);

	uartdiv = OCSFREQ / clkdiv / br;

	set8b(UART1_BRR2, (uartdiv & 0xf) | ((uartdiv & 0xf000) >> 4));
	set8b(UART1_BRR1, (uartdiv & 0x0ff0) >> 4);

	setbit(UART1_CR2, UART_CR2_REN, 1);
	setbit(UART1_CR2, UART_CR2_TEN, 1);
	setbit(UART1_CR2, UART_CR2_RIEN, 1);
}

void uartwrite(char *s, size_t l)
{
	int i;

	for (i = 0; i < l; ++i) {
		while (!getbit(UART1_SR, UART_SR_TXE));
	
		UART1_DR = s[i];
	}
}

void uartread(char *s, size_t l)
{
	int i;

	for (i = 0; i < l; ++i)
		s[i] = UART1_DR;
}

void adcinit(unsigned char ch)
{
	setbit(CLK_PCKENR2, CLK_PCKENR2_23, 1);

	setbit(ADC_CR2, ADC_CR2_ALIGN, 1);
	setval(ADC_CSR, ADC_CSR_CH, ch, 3);

	setval(ADC_CR1, ADC_CR1_SPSEL, ADC_PRESCALER_2, 3);
	setbit(ADC_CR1, ADC_CR1_CONT, 0);
	
	setbit(ADC_CR2, ADC_CR2_EXTTRIG, 0);

	setbit(ADC_TDRL, ch, 1);
	
	setbit(ADC_CSR, ADC_CSR_EOCIE, 1);
}

void adcstart(void)
{
	setbit(ADC_CR1, ADC_CR1_ADON, 1);
}

uint16_t adcgetval(void)
{
	uint16_t r;

	r = ((ADC_DRH << 8) | ADC_DRL) & 0x03ff;

	setbit(ADC_CSR, ADC_CSR_EOC, 0);

	return r;
}

int i2cinit()
{
	uint16_t ccr;
	
	setpin(PIN_GROUP_B, 4, PIN_DIR_I, PIN_IM_FLOAT, PIN_IM_EXDIS);
	setpin(PIN_GROUP_B, 5, PIN_DIR_I, PIN_IM_FLOAT, PIN_IM_EXDIS);

	setval(I2C_FREQR, I2C_FREQR_FREQ, 12, 6);
	setbit(I2C_CR1, I2C_CR1_PE, 0);

	setbit(I2C_CCRH, I2C_CCRH_FS, 0);
	
	ccr = 60;

	setval(I2C_TRISER, I2C_TRISER_TRISE, (12+1), 6);

	setval(I2C_CCRL, 0, (ccr & 0xff), 8);
	setval(I2C_CCRH, I2C_CCRH_CCR, ((ccr >> 8) & 0x0f), 4);

	setbit(I2C_CR1, I2C_CR1_PE, 1);
	setbit(I2C_CR2, I2C_CR2_ACK, 1);

	return 0;
}

int i2cmemwrite(uint8_t addr, uint8_t reg, const uint8_t *data,
	uint8_t len, int to)
{
	WAITWHILE(getbit(I2C_SR3, I2C_SR3_BUSY), to);

	setbit(I2C_CR2, I2C_CR2_START, 1);
	WAITWHILE(!getbit(I2C_SR1, I2C_SR1_SB), to);

	I2C_DR = addr & 0xfe;
	WAITWHILE(!getbit(I2C_SR1, I2C_SR1_ADDR), to);	

	if (!I2C_SR3)
		return 1;

	WAITWHILE(!getbit(I2C_SR1, I2C_SR1_TXE), to);

	I2C_DR = reg;

	while (len--) {
		WAITWHILE(!getbit(I2C_SR1, I2C_SR1_TXE), to);
		I2C_DR = *data++;
	}

	WAITWHILE(!(getbit(I2C_SR1, I2C_SR1_TXE) 
		&& getbit(I2C_SR1, I2C_SR1_BTF)), to);
	
	setbit(I2C_CR2, I2C_CR2_STOP, 1);
	WAITWHILE(getbit(I2C_CR2, I2C_CR2_STOP), to);
	
	return 0;
}

int i2cmemread(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len,
	int to)
{
	WAITWHILE(getbit(I2C_SR3, I2C_SR3_BUSY), to);

	setbit(I2C_CR2, I2C_CR2_ACK, 1);
	setbit(I2C_CR2, I2C_CR2_START, 1);

	WAITWHILE(!getbit(I2C_SR1, I2C_SR1_SB), to);

	I2C_DR = addr & 0xfe;
	WAITWHILE(!getbit(I2C_SR1, I2C_SR1_ADDR), to);	

	I2C_SR3;

	WAITWHILE(!getbit(I2C_SR1, I2C_SR1_TXE), to);

	I2C_DR = reg;

	WAITWHILE(!(getbit(I2C_SR1, I2C_SR1_TXE) 
		&& getbit(I2C_SR1, I2C_SR1_BTF)), to);
	
	setbit(I2C_CR2, I2C_CR2_START, 1);
	WAITWHILE(!getbit(I2C_SR1, I2C_SR1_SB), to);

	I2C_DR = addr | 0x01;
	
	if (len == 1) {
		setbit(I2C_CR2, I2C_CR2_ACK, 0);
	
		WAITWHILE(!getbit(I2C_SR1, I2C_SR1_ADDR), to);

		disable_interrupt();
		
		I2C_SR3;

		setbit(I2C_CR2, I2C_CR2_STOP, 1);

		enable_interrupt();

		WAITWHILE(!getbit(I2C_SR1, I2C_SR1_RXNE), to);

		*data = I2C_DR;
	}
	else if (len == 2) {
		setbit(I2C_CR2, I2C_CR2_POS, 1);

		WAITWHILE(!getbit(I2C_SR1, I2C_SR1_ADDR), to);
		
		disable_interrupt();

		I2C_SR3;	

		setbit(I2C_CR2, I2C_CR2_ACK, 0);

		enable_interrupt();

		WAITWHILE(!getbit(I2C_SR1, I2C_SR1_BTF), to);

		disable_interrupt();

		setbit(I2C_CR2, I2C_CR2_STOP, 1);
		*data++ = I2C_DR;
	
		enable_interrupt();
		*data++ = I2C_DR;
	} else { 
		WAITWHILE(!getbit(I2C_SR1, I2C_SR1_ADDR), to);
		
		disable_interrupt();

		I2C_SR3;

		enable_interrupt();

		while (len > 3) {
			WAITWHILE(!getbit(I2C_SR1, I2C_SR1_BTF), to);
			*data++ = I2C_DR;

			len--;
		}

		WAITWHILE(!getbit(I2C_SR1, I2C_SR1_BTF), to);
	
		setbit(I2C_CR2, I2C_CR2_ACK, 0);

		disable_interrupt();

		*data++ = I2C_DR;

		setbit(I2C_CR2, I2C_CR2_STOP, 1);
		*data++ = I2C_DR;
	
		enable_interrupt();
		WAITWHILE(!getbit(I2C_SR1, I2C_SR1_RXNE), to);

		*data++ = I2C_DR;
	}

	while (getbit(I2C_CR2, I2C_CR2_STOP));
	setbit(I2C_CR2, I2C_CR2_POS, 0);

	return 0;
}
