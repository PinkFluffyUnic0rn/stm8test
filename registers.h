#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>
#include <stddef.h>

#include "stm8l.h"

#define OCSFREQ 16000000

#define setbit(r, b, v)		\
	((r) = (v) ? ((r) | (1 << (b))) : ((r) & ~(1 << (b))))

#define setval(r, b, v, l)	\
	((r) = ((0xff >> (8 - b - l)) & (v << (b))))

#define getbit(r, b) ((r & (1 << b)) >> b)

#define set8b(r, v) (r = (v))

#define SET16B(r, v)			\
do {					\
	r##H = (v) >> 8;		\
	r##L = (v) & 0x00ff;		\
} while (0);

#define uartwrites(s) uartwrite(s, strlen(s));

#define tim1start() setbit(TIM1_CR1, TIMX_CR1_CEN, 1)
#define tim2start() setbit(TIM2_CR1, TIMX_CR1_CEN, 1)
#define tim4start() setbit(TIM3_CR1, TIMX_CR1_CEN, 1)

#define tim1stop() setbit(TIM1_CR1, TIMX_CR1_CEN, 0)
#define tim2stop() setbit(TIM2_CR1, TIMX_CR1_CEN, 0)
#define tim4stop() setbit(TIM3_CR1, TIMX_CR1_CEN, 0)

enum PIN_GROUP {
	PIN_GROUP_A = 0,
	PIN_GROUP_B = 1,
	PIN_GROUP_C = 2,
	PIN_GROUP_D = 3
};

enum PIN_DIR {
	PIN_DIR_O = 1,
	PIN_DIR_I = 0
};

enum PIN_IM {
	PIN_IM_FLOAT	= 0,
	PIN_IM_PU	= 1,
	PIN_IM_EXDIS	= 0,
	PIN_IM_EXEN	= 1
};

enum PIN_OM {
	PIN_OM_OD	= 0,
	PIN_OM_PP	= 1,
	PIN_OM_OS2	= 0,
	PIN_OM_OS10	= 1
};

enum EXTI_MODE {
	EXTI_MODE_FALLLOW	= EXTI_SENSBITS_FALLLOW,
	EXTI_MODE_RAIS		= EXTI_SENSBITS_RAIS,
	EXTI_MODE_FALL		= EXTI_SENSBITS_FALL,
	EXTI_MODE_RAISFALL	= EXTI_SENSBITS_RAISFALL
};

enum CLOCK_DIV {
	CLOCK_DIV_0	= CLOCK_HSIDIV_0,
	CLOCK_DIV_2	= CLOCK_HSIDIV_2,
	CLOCK_DIV_4	= CLOCK_HSIDIV_4,
	CLOCK_DIV_8	= CLOCK_HSIDIV_8
};

enum TIM_PRESCALER {
	TIM_PRESCALER_1		= TIMX_PRESCALER_1,
	TIM_PRESCALER_2		= TIMX_PRESCALER_2,
	TIM_PRESCALER_4		= TIMX_PRESCALER_4,
	TIM_PRESCALER_8		= TIMX_PRESCALER_8,
	TIM_PRESCALER_16	= TIMX_PRESCALER_16,
	TIM_PRESCALER_32	= TIMX_PRESCALER_32,
	TIM_PRESCALER_64	= TIMX_PRESCALER_64,
	TIM_PRESCALER_128	= TIMX_PRESCALER_128,
	TIM_PRESCALER_256	= TIMX_PRESCALER_256,
	TIM_PRESCALER_512	= TIMX_PRESCALER_512,
	TIM_PRESCALER_1024	= TIMX_PRESCALER_1024,
	TIM_PRESCALER_2048	= TIMX_PRESCALER_2048,
	TIM_PRESCALER_4096	= TIMX_PRESCALER_4096,
	TIM_PRESCALER_8192	= TIMX_PRESCALER_8192,
	TIM_PRESCALER_16384	= TIMX_PRESCALER_16384
};

void setclockdiv(enum CLOCK_DIV d);

void usdelay(unsigned char c);
void msdelay(uint16_t c);

void setpin(enum PIN_GROUP g, unsigned char p, unsigned char d,
		unsigned char cr1v, unsigned char cr2v);
unsigned char getpinval(enum PIN_GROUP g, unsigned char p);
void setpinval(enum PIN_GROUP g, unsigned char p, unsigned char v);

void setexti(enum PIN_GROUP g, enum EXTI_MODE sb);

void tim1cntmode(uint16_t psc, uint16_t arr);
uint16_t tim1getcnt(void);
void tim1clearcnt(void);

void tim2cntmode(enum TIM_PRESCALER psc, uint16_t arr);
void tim2pwmmode(enum TIM_PRESCALER psc, uint16_t arr, uint16_t ccr);
void tim2pwmduty(uint16_t d);

void tim4cntmode(enum TIM_PRESCALER psc, uint8_t arr);

void uartinit(uint32_t br);
void uartwrite(char *s, size_t l);
void uartread(char *s, size_t l);

void adcinit(unsigned char ch);
void adcstart(void);
uint16_t adcgetval(void);

int i2cinit();
int i2cmemwrite(uint8_t addr, uint8_t reg, const uint8_t *data,
	uint8_t len, int to);
int i2cmemread(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len,
	int to);

#endif
