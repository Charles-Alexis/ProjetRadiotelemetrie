/*
 * delta-encoding.h
 *
 *  Created on: Aug 13, 2020
 *      Author: Charles-Alexis
 */

#ifndef DELTA_ENCODING_H_
#define DELTA_ENCODING_H_

#include PLATFORM_HEADER
#include CONFIGURATION_HEADER
#include EMBER_AF_API_STACK
#include EMBER_AF_API_HAL
#include EMBER_AF_API_COMMAND_INTERPRETER2
#ifdef EMBER_AF_API_DEBUG_PRINT
  #include EMBER_AF_API_DEBUG_PRINT
#endif

void buildPayloadEncoding7(uint8_t * DeltaPackets, uint16_t * ADCData);
void buildPayloadEncoding6(uint8_t * DeltaPackets, uint16_t * ADCData);
void buildPayloadEncoding5(uint8_t * DeltaPackets, uint16_t * ADCData);

#endif /* DELTA_ENCODING_H_ */
