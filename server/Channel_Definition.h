/*
 * Channel_Definition.h
 *
 *  Created on: Jul 2, 2020
 *      Author: Charles-Alexis
 */

#ifndef CHANNEL_DEFINITION_H_
#define CHANNEL_DEFINITION_H_

uint8_t calculateFirstAcquisition(uint8_t packetNumber, uint16_t payloadLeangth);
void ByteTo16Uint(uint16_t * Samples, uint8_t * PayloadBytes, uint16_t BytesLength);
void dispatchPackets(uint16_t * Samples, uint8_t * PayloadBytes, uint16_t BytesLength);
void dispatchPacketsDeltaEncoding(uint16_t * Samples, uint8_t * PayloadBytes, uint16_t BytesLength);

#endif /* CHANNEL_DEFINITION_H_ */
