/*
 * NRF24L01_registers.h
 *
 *  Created on: Jun 21, 2025
 *      Author: leand
 */

#ifndef NRF24_NRF24L01_REGISTERS_H_
#define NRF24_NRF24L01_REGISTERS_H_

/* Memory map*/
#define NRF24L01_CONFIG				(0x00)
#define NRF24L01_EN_AA				(0x01)
#define NRF24L01_EN_RXADDR			(0x02)
#define NRF24L01_SETUP_AW			(0x03)
#define NRF24L01_SETUP_RETR			(0x04)
#define NRF24L01_RF_CH				(0x05)
#define NRF24L01_RF_SETUP			(0x06)
#define NRF24L01_STATUS				(0x07)
#define NRF24L01_OBSERVE_TX			(0x08)
#define NRF24L01_RPD				(0x09)
#define NRF24L01_RX_ADDR_P0			(0x0A)
#define NRF24L01_RX_ADDR_P1			(0x0B)
#define NRF24L01_RX_ADDR_P2			(0x0C)
#define NRF24L01_RX_ADDR_P3			(0x0D)
#define NRF24L01_RX_ADDR_P4			(0x0E)
#define NRF24L01_RX_ADDR_P5			(0x0F)
#define NRF24L01_TX_ADDR			(0x10)
#define NRF24L01_RX_PW_P0			(0x11)
#define NRF24L01_RX_PW_P1			(0x12)
#define NRF24L01_RX_PW_P2			(0x13)
#define NRF24L01_RX_PW_P3			(0x14)
#define NRF24L01_RX_PW_P4			(0x15)
#define NRF24L01_RX_PW_P5			(0x16)
#define NRF24L01_FIFO_STATUS		(0x17)
#define NRF24L01_DYNPD				(0x1C)
#define NRF24L01_FEATURE			(0x1D)

/* Instruction Mnemonics*/
#define R_REGISTER					(0x00)
#define W_REGISTER					(0x20)
#define RW_REGISTER_MASK			(0x1F)
#define R_RX_PAYLOAD				(0x61)
#define W_TX_PAYLOAD				(0xA0)
#define FLUSH_TX					(0xE1)
#define FLUSH_RX					(0xE2)
#define REUSE_TX_PL					(0xE3)
#define R_RX_PL_WID					(0x60)
#define W_ACK_PAYLOAD				(0xA8)
#define W_TX_PAYLOAD_NO_ACK			(0xB0)
#define NOP							(0xFF)

#endif /* NRF24_NRF24L01_REGISTERS_H_ */
