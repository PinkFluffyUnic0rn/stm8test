#ifndef STM8L_H
#define STM8L_H

enum TIMX_PRESCALER {
	TIMX_PRESCALER_1	= 0x0,
	TIMX_PRESCALER_2	= 0x1,
	TIMX_PRESCALER_4	= 0x2,
	TIMX_PRESCALER_8	= 0x3,
	TIMX_PRESCALER_16	= 0x4,
	TIMX_PRESCALER_32	= 0x5,
	TIMX_PRESCALER_64	= 0x6,
	TIMX_PRESCALER_128	= 0x7,
	TIMX_PRESCALER_256	= 0x8,
	TIMX_PRESCALER_512	= 0x9,
	TIMX_PRESCALER_1024	= 0xa,
	TIMX_PRESCALER_2048	= 0xb,
	TIMX_PRESCALER_4096	= 0xc,
	TIMX_PRESCALER_8192	= 0xe,
	TIMX_PRESCALER_16384	= 0xf
};

enum CLOCK_HSIDIV {
	CLOCK_HSIDIV_0		= 0x0,
	CLOCK_HSIDIV_2		= 0x1,
	CLOCK_HSIDIV_4		= 0x2,
	CLOCK_HSIDIV_8		= 0x3
};

enum CLOCK_MASTER {
	CLOCK_MASTER_HSI	= 0xe1,
	CLOCK_MASTER_LSI	= 0xd2,
	CLOCK_MASTER_HSE	= 0xb4
};

enum TIMX_COMPMODE {
	TIMX_COMPMODE_FROZEN	= 0,
	TIMX_COMPMODE_ACTMATCH	= 1,
	TIMX_COMPMODE_IACTMATCH	= 2,
	TIMX_COMPMODE_TOGGLE	= 3,
	TIMX_COMPMODE_FORCEIACT	= 4,
	TIMX_COMPMODE_FORCEACT	= 5,
	TIMX_COMPMODE_PWM1	= 6,
	TIMX_COMPMODE_PWM2	= 7
};

enum EXTI_SENSBITS {
	EXTI_SENSBITS_FALLLOW	= 0x0,
	EXTI_SENSBITS_RAIS	= 0x1,
	EXTI_SENSBITS_FALL	= 0x2,
	EXTI_SENSBITS_RAISFALL	= 0x3
};

enum ADC_PRESCALER {
	ADC_PRESCALER_2		= 0,
	ADC_PRESCALER_3		= 1,
	ADC_PRESCALER_4		= 2,
	ADC_PRESCALER_6		= 3,
	ADC_PRESCALER_8		= 4,
	ADC_PRESCALER_10	= 5,
	ADC_PRESCALER_12	= 6,
	ADC_PRESCALER_18	= 7
};

// Interrupt vector mapping
#define EXTI0			3
#define EXTI1			4
#define EXTI2			5
#define EXTI3			6
#define EXTI4			7
#define UARTRX			18
#define ADC1			22

// GPIO registers
#define PA_ODR			*(volatile unsigned char *) 0x5000
#define PA_IDR			*(volatile unsigned char *) 0x5001
#define PA_DDR			*(volatile unsigned char *) 0x5002
#define PA_CR1			*(volatile unsigned char *) 0x5003
#define PA_CR2			*(volatile unsigned char *) 0x5004

#define PB_ODR			*(volatile unsigned char *) 0x5005
#define PB_IDR			*(volatile unsigned char *) 0x5006
#define PB_DDR			*(volatile unsigned char *) 0x5007
#define PB_CR1			*(volatile unsigned char *) 0x5008
#define PB_CR2			*(volatile unsigned char *) 0x5009

#define PC_ODR			*(volatile unsigned char *) 0x500A
#define PC_IDR			*(volatile unsigned char *) 0x500B
#define PC_DDR			*(volatile unsigned char *) 0x500C
#define PC_CR1			*(volatile unsigned char *) 0x500D
#define PC_CR2			*(volatile unsigned char *) 0x500E

#define PD_ODR			*(volatile unsigned char *) 0x500F
#define PD_IDR			*(volatile unsigned char *) 0x5010
#define PD_DDR			*(volatile unsigned char *) 0x5011
#define PD_CR1			*(volatile unsigned char *) 0x5012
#define PD_CR2			*(volatile unsigned char *) 0x5013

#define PE_ODR			*(volatile unsigned char *) 0x5014
#define PE_IDR			*(volatile unsigned char *) 0x5015
#define PE_DDR			*(volatile unsigned char *) 0x5016
#define PE_CR1			*(volatile unsigned char *) 0x5017
#define PE_CR2			*(volatile unsigned char *) 0x5018

#define PF_ODR			*(volatile unsigned char *) 0x5019
#define PF_IDR			*(volatile unsigned char *) 0x501A
#define PF_DDR			*(volatile unsigned char *) 0x501B
#define PF_CR1			*(volatile unsigned char *) 0x501C
#define PF_CR2			*(volatile unsigned char *) 0x501D

// Clock registers
#define CLK_ICKR		*(volatile unsigned char *) 0x50c0
#define CLK_ECKR		*(volatile unsigned char *) 0x50c1
#define CLK_CMSR		*(volatile unsigned char *) 0x50c3
#define CLK_SWR 		*(volatile unsigned char *) 0x50c4
#define CLK_SWCR		*(volatile unsigned char *) 0x50c5
#define CLK_CKDIVR		*(volatile unsigned char *) 0x50c6
#define CLK_PCKENR1		*(volatile unsigned char *) 0x50c7
#define CLK_CSSR		*(volatile unsigned char *) 0x50c8
#define CLK_CCOR		*(volatile unsigned char *) 0x50c9
#define CLK_PCKENR2		*(volatile unsigned char *) 0x50ca
#define CLK_HSITRIMR		*(volatile unsigned char *) 0x50cc
#define CLK_SWIMCCR		*(volatile unsigned char *) 0x50cd

// Beeper
#define BEEP_CSR		*(volatile unsigned char *) 0x50f3

// TIM registers
#define TIM1_CR1		*(volatile unsigned char *) 0x5250
#define TIM1_CR2		*(volatile unsigned char *) 0x5251
#define TIM1_SMCR		*(volatile unsigned char *) 0x5252
#define TIM1_ETR		*(volatile unsigned char *) 0x5253
#define TIM1_IER		*(volatile unsigned char *) 0x5254
#define TIM1_SR1		*(volatile unsigned char *) 0x5255
#define TIM1_SR2		*(volatile unsigned char *) 0x5256
#define TIM1_EGR		*(volatile unsigned char *) 0x5257
#define TIM1_CCMR1		*(volatile unsigned char *) 0x5258
#define TIM1_CCMR2		*(volatile unsigned char *) 0x5259
#define TIM1_CCMR3		*(volatile unsigned char *) 0x525a
#define TIM1_CCMR4		*(volatile unsigned char *) 0x525b
#define TIM1_CCER1		*(volatile unsigned char *) 0x525c
#define TIM1_CCER2		*(volatile unsigned char *) 0x525d
#define TIM1_CNTRH		*(volatile unsigned char *) 0x525e
#define TIM1_CNTRL		*(volatile unsigned char *) 0x525f
#define TIM1_PSCRH		*(volatile unsigned char *) 0x5260
#define TIM1_PSCRL		*(volatile unsigned char *) 0x5261
#define TIM1_ARRH		*(volatile unsigned char *) 0x5262
#define TIM1_ARRL		*(volatile unsigned char *) 0x5263
#define TIM1_RCR		*(volatile unsigned char *) 0x5264
#define TIM1_CCR1H		*(volatile unsigned char *) 0x5265
#define TIM1_CCR1L		*(volatile unsigned char *) 0x5266
#define TIM1_CCR2H		*(volatile unsigned char *) 0x5267
#define TIM1_CCR2L		*(volatile unsigned char *) 0x5268
#define TIM1_CCR3H		*(volatile unsigned char *) 0x5269
#define TIM1_CCR3L		*(volatile unsigned char *) 0x526a
#define TIM1_CCR4H		*(volatile unsigned char *) 0x526b
#define TIM1_CCR4L		*(volatile unsigned char *) 0x526c
#define TIM1_BKR		*(volatile unsigned char *) 0x526d
#define TIM1_DTR		*(volatile unsigned char *) 0x526e
#define TIM1_OISR		*(volatile unsigned char *) 0x526f

#define TIM2_CR1		*(volatile unsigned char *) 0x5300
#define TIM2_IER		*(volatile unsigned char *) 0x5303
#define TIM2_SR1		*(volatile unsigned char *) 0x5304
#define TIM2_SR2		*(volatile unsigned char *) 0x5305
#define TIM2_EGR		*(volatile unsigned char *) 0x5306
#define TIM2_CCMR1		*(volatile unsigned char *) 0x5307
#define TIM2_CCMR2		*(volatile unsigned char *) 0x5308
#define TIM2_CCMR3		*(volatile unsigned char *) 0x5309
#define TIM2_CCER1		*(volatile unsigned char *) 0x530a
#define TIM2_CCER2		*(volatile unsigned char *) 0x530b
#define TIM2_CNTRH		*(volatile unsigned char *) 0x530c
#define TIM2_CNTRL		*(volatile unsigned char *) 0x530d
#define TIM2_PSCR		*(volatile unsigned char *) 0x530e
#define TIM2_ARRH		*(volatile unsigned char *) 0x530f
#define TIM2_ARRL		*(volatile unsigned char *) 0x5310
#define TIM2_CCR1H		*(volatile unsigned char *) 0x5311
#define TIM2_CCR1L		*(volatile unsigned char *) 0x5312
#define TIM2_CCR2H		*(volatile unsigned char *) 0x5313
#define TIM2_CCR2L		*(volatile unsigned char *) 0x5314
#define TIM2_CCR3H		*(volatile unsigned char *) 0x5315
#define TIM2_CCR3L		*(volatile unsigned char *) 0x5316

#define TIM4_CR1		*(volatile unsigned char *) 0x5340
#define TIM4_IER		*(volatile unsigned char *) 0x5343
#define TIM4_SR			*(volatile unsigned char *) 0x5344
#define TIM4_EGR		*(volatile unsigned char *) 0x5345
#define TIM4_CNTR		*(volatile unsigned char *) 0x5346
#define TIM4_PSCR		*(volatile unsigned char *) 0x5347
#define TIM4_ARR		*(volatile unsigned char *) 0x5348

// EXTI registers
#define EXTI_CR1		*(volatile unsigned char *) 0x50a0
#define EXTI_CR2		*(volatile unsigned char *) 0x50a1

// UART registers
#define UART1_SR		*(volatile unsigned char *) 0x5230
#define UART1_DR		*(volatile unsigned char *) 0x5231
#define UART1_BRR1		*(volatile unsigned char *) 0x5232
#define UART1_BRR2		*(volatile unsigned char *) 0x5233
#define UART1_CR1		*(volatile unsigned char *) 0x5234
#define UART1_CR2		*(volatile unsigned char *) 0x5235
#define UART1_CR3		*(volatile unsigned char *) 0x5236
#define UART1_CR4		*(volatile unsigned char *) 0x5237
#define UART1_CR5		*(volatile unsigned char *) 0x5238
#define UART1_GTR		*(volatile unsigned char *) 0x5239
#define UART1_PSCR		*(volatile unsigned char *) 0x523a

// ADC registers
#define ADC_CSR			*(volatile unsigned char *) 0x5400
#define ADC_CR1			*(volatile unsigned char *) 0x5401
#define ADC_CR2			*(volatile unsigned char *) 0x5402
#define ADC_CR3			*(volatile unsigned char *) 0x5403
#define ADC_DRH			*(volatile unsigned char *) 0x5404
#define ADC_DRL			*(volatile unsigned char *) 0x5405
#define ADC_TDRH		*(volatile unsigned char *) 0x5406
#define ADC_TDRL		*(volatile unsigned char *) 0x5407
#define ADC_HTRH		*(volatile unsigned char *) 0x5408
#define ADC_HTRL		*(volatile unsigned char *) 0x5409
#define ADC_LTRH		*(volatile unsigned char *) 0x540a
#define ADC_LTRL		*(volatile unsigned char *) 0x540b
#define ADC_AWSRH		*(volatile unsigned char *) 0x540c
#define ADC_AWSRL		*(volatile unsigned char *) 0x540d
#define ADC_AWCRH		*(volatile unsigned char *) 0x540e
#define ADC_AWCRL		*(volatile unsigned char *) 0x540f

// I2C registers
#define I2C_CR1			*(volatile unsigned char *) 0x5210
#define I2C_CR2			*(volatile unsigned char *) 0x5211
#define I2C_FREQR		*(volatile unsigned char *) 0x5212
#define I2C_OARL		*(volatile unsigned char *) 0x5213
#define I2C_OARH		*(volatile unsigned char *) 0x5214
#define I2C_DR			*(volatile unsigned char *) 0x5216
#define I2C_SR1			*(volatile unsigned char *) 0x5217
#define I2C_SR2			*(volatile unsigned char *) 0x5218
#define I2C_SR3			*(volatile unsigned char *) 0x5219
#define I2C_ITR			*(volatile unsigned char *) 0x521a
#define I2C_CCRL		*(volatile unsigned char *) 0x521b
#define I2C_CCRH		*(volatile unsigned char *) 0x521c
#define I2C_TRISER		*(volatile unsigned char *) 0x521d
#define I2C_PECR		*(volatile unsigned char *) 0x521e

// CLK_ICKR bits
#define CLK_ICKR_HSIEN		0
#define CLK_ICKR_HSIRDY		1
#define CLK_ICKR_FHW		2
#define CLK_ICKR_LSIEN		3
#define CLK_ICKR_LSIRDY		4
#define CLK_ICKR_REGAH		5

// CLK_SWCR bits
#define CLK_SWCR_SWBSY		0
#define CLK_SWCR_SWEN		1
#define CLK_SWCR_SWIEN		2
#define CLK_SWCR_SWIF		3

// CLK_PCKENR1 bits
#define CLK_PCKENR1_10		0
#define CLK_PCKENR1_11		1
#define CLK_PCKENR1_12		2
#define CLK_PCKENR1_13		3
#define CLK_PCKENR1_14		4
#define CLK_PCKENR1_15		5
#define CLK_PCKENR1_16		6
#define CLK_PCKENR1_17		7

// CLK_PCKENR2 bits
#define CLK_PCKENR2_20		0
#define CLK_PCKENR2_21		1
#define CLK_PCKENR2_22		2
#define CLK_PCKENR2_23		3
#define CLK_PCKENR2_24		4
#define CLK_PCKENR2_25		5
#define CLK_PCKENR2_26		6
#define CLK_PCKENR2_27		7

// CLK_CKDIVR
#define CLK_CKDIVR_CPUDIV	0
#define CLK_CKDIVR_HSIDIV	3

// TIMX_CR1 bits
#define TIMX_CR1_CEN		0
#define TIMX_CR1_UDIS		1
#define TIMX_CR1_URS		2
#define TIMX_CR1_OPM		3
#define TIMX_CR1_ARPE		7

// TIMX_CR2 bits
#define TIMX_CR2_MMS		4

// TIMX_EGR
#define TIMX_EGR_UG		0
#define TIMX_EGR_TG		6

// TIMX_IER
#define TIMX_IER_UIE		0
#define TIMX_IER_TIE		6

// TIMX_SR
#define TIMX_SR_UIF		0
#define TIMX_SR_TIF		6

// TIMX_CCMR1
#define TIMX_CCMR1_CC1S		0
#define TIMX_CCMR1_OC1PE	3
#define TIMX_CCMR1_OC1M		4

// TIMX_CCER1
#define TIMX_CCER1_CC1E		0
#define TIMX_CCER1_CC1P		1
#define TIMX_CCER1_CC2E		4
#define TIMX_CCER1_CC2P		5

// EXTI_CR1
#define EXTI_CR1_PAIS		0
#define EXTI_CR1_PBIS		2
#define EXTI_CR1_PCIS		4
#define EXTI_CR1_PDIS		6

// EXTI_CR2
#define EXTI_CR2_PEIS		0
#define EXTI_CR2_TLIS		2

// UART_CR1 bits
#define UART_CR1_R8		7
#define UART_CR1_T8		6
#define UART_CR1_UARTD		5
#define UART_CR1_M		4
#define UART_CR1_WAKE		3
#define UART_CR1_PCEN		2
#define UART_CR1_PS		1
#define UART_CR1_PIEN		0

// UART_CR2 bits
#define UART_CR2_TIEN		7
#define UART_CR2_TCIEN		6
#define UART_CR2_RIEN		5
#define UART_CR2_ILIEN		4
#define UART_CR2_TEN		3
#define UART_CR2_REN		2
#define UART_CR2_RWU		1
#define UART_CR2_SBK		0

// UART_CR3 bits
#define UART_CR3_LINEN		6
#define UART_CR3_STOP2		5
#define UART_CR3_STOP1		4
#define UART_CR3_CLKEN		3
#define UART_CR3_CPOL		2
#define UART_CR3_CPHA		1
#define UART_CR3_LBCL		0

// UART_SR bits
#define UART_SR_TXE		7
#define UART_SR_TC		6
#define UART_SR_RXNE		5
#define UART_SR_IDLE		4
#define UART_SR_OR		3
#define UART_SR_NF		2
#define UART_SR_FE		1
#define UART_SR_PE		0

// ADC_CSR bits
#define ADC_CSR_CH		0
#define ADC_CSR_AWDIE		4
#define ADC_CSR_EOCIE		5
#define ADC_CSR_AWD		6
#define ADC_CSR_EOC		7

// ADC_CR1 bits
#define ADC_CR1_ADON		0
#define ADC_CR1_CONT		1
#define ADC_CR1_SPSEL		4

// ADC_CR2 bits
#define ADC_CR2_SCAN		1
#define ADC_CR2_ALIGN		3
#define ADC_CR2_EXTSEL		4
#define ADC_CR2_EXTTRIG		6

// I2C_CR1 bits
#define I2C_CR1_PE		0
#define I2C_CR1_ENGC		6
#define I2C_CR1_NOSTRETCH	7

// I2C_CR2 bits
#define I2C_CR2_START		0
#define I2C_CR2_STOP		1
#define I2C_CR2_ACK		2
#define I2C_CR2_POS		3
#define I2C_CR2_SWRST		7

// I2C_FREQR bits
#define I2C_FREQR_FREQ		0

// I2C_OARL bits
#define I2C_OARL_ADD0		0
#define I2C_OARL_ADD		1

// I2C_OARH bits
#define I2C_OARH_ADD		1
#define I2C_OARH_ADDCONF	6
#define I2C_OARH_ADDMODE	7

// I2C_SR1 bits
#define I2C_SR1_SB		0
#define I2C_SR1_ADDR		1
#define I2C_SR1_BTF		2
#define I2C_SR1_ADD10		3
#define I2C_SR1_STOPF		4
#define I2C_SR1_RXNE		6
#define I2C_SR1_TXE		7

// I2C_SR2 bits
#define I2C_SR2_BERR		0
#define I2C_SR2_ARLO		1
#define I2C_SR2_AF		2
#define I2C_SR2_OVR		3
#define I2C_SR2_WUFH		5

// I2C_SR3 bits
#define I2C_SR3_MSL		0
#define I2C_SR3_BUSY		1
#define I2C_SR3_TRA		2
#define I2C_SR3_GENCALL		4
#define I2C_SR3_DUALF		7

// I2C_ITR bits
#define I2C_ITR_ITERREN		0
#define I2C_ITR_ITEVTEN		1
#define I2C_ITR_ITBUFEN		2

// I2C_CCRH bits
#define I2C_CCRH_CCR		0
#define I2C_CCRH_DUTY		6
#define I2C_CCRH_FS		7

// I2C_TRISER bits
#define I2C_TRISER_TRISE	0

#define disable_interrupt()	__asm__("sim")
#define enable_interrupt()	__asm__("rim")

#endif
