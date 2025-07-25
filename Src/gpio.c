/*
 * gpio.c
 *
 *  Created on: Jun 2, 2025
 *      Author: leand
 */

#include "GPIO_utils.h"
#include "HW_types.h"
#include "RCC_utils.h"


#define PA3					(1<<3)

#define PC13				(1<<13)

#define PA2_CNF_MODE		((GPIOx_CRLH_CNF_OUTPUT_GP_PUSH_PULL | GPIOx_CRLH_MODE_50MHz)<<8)
#define PA3_CNF_MODE		((GPIOx_CRLH_CNF_OUTPUT_GP_PUSH_PULL | GPIOx_CRLH_MODE_50MHz)<<12)

#define PA4_CNF_MODE		((GPIOx_CRLH_CNF_OUTPUT_GP_PUSH_PULL | GPIOx_CRLH_MODE_50MHz)<<16)
#define PA5_CNF_MODE		((GPIOx_CRLH_CNF_OUTPUT_AF_PUSH_PULL | GPIOx_CRLH_MODE_50MHz)<<20)
#define PA6_CNF_MODE		((GPIOx_CRLH_CNF_INPUT_PULL_UP_DOWN | GPIOx_CRLH_MODE_INPUT)<<24)
//#define PA6_CNF_MODE		((GPIOx_CRLH_CNF_INPUT_FLOATING | GPIOx_CRLH_MODE_INPUT)<<24)
#define PA7_CNF_MODE		((GPIOx_CRLH_CNF_OUTPUT_AF_PUSH_PULL | GPIOx_CRLH_MODE_50MHz)<<28)

#define SPI1_NSS			PA4_CNF_MODE
#define SPI1_CLK			PA5_CNF_MODE
#define SPI1_MISO			PA6_CNF_MODE
#define SPI1_MOSI			PA7_CNF_MODE

void __attribute__((weak)) gpio_init_config(){
	ENABLE_CLOCK_APB2(RCC_APB2ENR_IOCEEN_CLOCK_ENABLE);	//Enable GPIOC Clock
	HW_REG(GPIO_C+GPIOx_BSRR) = PC13;	//Reset C13

	//  Analog mode all
	//HW_REG(GPIO_C+GPIOx_CRH) &= ~(0xFFFF);
	//HW_REG(GPIO_C+GPIOx_CRL) &= ~(0xFFFF);

	HW_REG(GPIO_C+GPIOx_CRH) &= ~(0xF<<20);	//Set C13 as Output
	HW_REG(GPIO_C+GPIOx_CRH) |= (0x2<<20);	//Set C13 max speed 2MHz
	//HW_REG(RCCA+RCC_CFGR) |= (0x7<<11);	//PPRE2 divided by 16
	//HW_REG(RCCA+RCC_APB2ENR) &= ~(1<<4);

	// Exemplo para restaurar pinos PC14/15 ao estado adequado (modo analógico)
	//HW_REG(GPIO_C+GPIOx_CRH) &= ~((0xF << ((14 - 8) * 4)) | (0xF << ((15 - 8) * 4)));
	//HW_REG(GPIO_C+GPIOx_CRH) |= ((0x0 << ((14 - 8) * 4)) | (0x0 << ((15 - 8) * 4))); // Analog input

	// SPI configuration
	ENABLE_CLOCK_APB2(RCC_APB2ENR_IOAEEN_CLOCK_ENABLE);	// Enable GPIOA Clock
	HW_REG(GPIO_A+GPIOx_CRL) &= ~(0xFFFFF000);			// Clear CNF and MODE A7-A2
	HW_REG(GPIO_A+GPIOx_ODR) &= ~PA3;			// Reset A3

	HW_REG(GPIO_A+GPIOx_CRL) |= PA3_CNF_MODE;	// CE

	HW_REG(GPIO_A+GPIOx_CRL) |= SPI1_CLK;	// CLK Master Alternate function push-pull
	HW_REG(GPIO_A+GPIOx_CRL) |= SPI1_MOSI;	// MOSI Full duplex / master Alternate function push-pull
	HW_REG(GPIO_A+GPIOx_CRL) |= SPI1_MISO;	// MISO Full duplex / master Input floating / Input pull-up
	HW_REG(GPIO_A+GPIOx_CRL) |= SPI1_NSS;	// NSS Software
	// afio_init_config();
}

char __attribute__((weak)) lock_key_write_sequence(const short int port_bits){
	int save_register = 0;

	HW_REG(GPIO_C+GPIOx_LCKR) &= ~(0x0001FFFF);	//Reset  Value 0x0000 0000
	save_register = HW_REG(GPIO_C+GPIOx_LCKR) |= (port_bits & LCKR_MASK);	//Lock only port on value
	// Lock sequence
	HW_REG(GPIO_C+GPIOx_LCKR) = save_register | (LCKK);	//Write 1
	HW_REG(GPIO_C+GPIOx_LCKR) = save_register & ~(LCKK);	//Write 0
	HW_REG(GPIO_C+GPIOx_LCKR) = save_register | (LCKK);	//Write 1
	HW_REG(GPIO_C+GPIOx_LCKR);			//Read 0

	return (char)(HW_REG(GPIO_C+GPIOx_LCKR) >> 16);	//Read 1 optional
	/*
	char lock_key = 0;
	HW_REG(GPIO_C+GPIOx_LCKR) = ~(0x1FFFF);	//Reset  Value 0x0000 0000
	HW_REG(GPIO_C+GPIOx_LCKR) |= (0xFFFF);		//Lock all
	// Lock sequence
	HW_REG(GPIO_C+GPIOx_LCKR) = (0x1FFFF);	//Write 1
	HW_REG(GPIO_C+GPIOx_LCKR) = ~(0x10000);	//Write 0
	HW_REG(GPIO_C+GPIOx_LCKR) = (0x1FFFF);	//Write 1
	HW_REG(GPIO_C+GPIOx_LCKR);			//Read 0
	lock_key = HW_REG(GPIO_C+GPIOx_LCKR) >> 16;	//Read 1 optional
	*/
}

//UNDEF
#undef PA2
#undef PA3
#undef PC13
#undef PA2_CNF_MODE
#undef PA3_CNF_MODE
#undef PA4_CNF_MODE
#undef PA5_CNF_MODE
#undef PA6_CNF_MODE
#undef PA7_CNF_MODE
#undef SPI1_NSS
#undef SPI1_CLK
#undef SPI1_MISO
#undef SPI1_MOSI
