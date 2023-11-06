/*
 * Channel_definition.c
 *
 *  Created on: Aug 6, 2020
 *      Author: Charles-Alexis
 */
#include PLATFORM_HEADER
#include CONFIGURATION_HEADER
#include EMBER_AF_API_STACK
#include EMBER_AF_API_HAL
#include EMBER_AF_API_COMMAND_INTERPRETER2
#ifdef EMBER_AF_API_DEBUG_PRINT
  #include EMBER_AF_API_DEBUG_PRINT
#endif
#include "Channel_definition.h"

uint8_t packetsOrder[94] = {0,1,2,3,4,5,6,7,8,9,10,11,  0,1,2,3,4,5,6,7,  0,1,2,3,4,5,6,7,  0,1,2,3,4,5,6,7,  0,1,2,3,4,5,6,7,                 //First 5 packets
							0,1,2,3,4,5,6,7,8,  0,1,2,3,4,5,6,7, 0,1,2,3,4,5,6,7,  0,1,2,3,4,5,6,7,  0,1,2,3,4,5,6,7,  0,1,2,3,4,5,6,7,  8};

uint16_t oldPackets[12];
uint16_t tempi=0;

#define MaxData 50
uint16_t DataToDAC[12][MaxData+1];

void initiateArray(){/*
	if(ArrayInitiate == false){
		ArrayInitiate=true;
		for(uint8_t j=0;j<12;j++){for(uint8_t k=0;k<MaxData+1;k++){DataToDAC[j][k]=0;}}
	}*/
}

uint8_t calculateFirstAcquisition(uint8_t packetNumber, uint16_t payloadLength){
	uint16_t dataPacketSize = ((payloadLength-1)*8/10); //124
	uint16_t firstPacketIndex = dataPacketSize * packetNumber; //124 * x
	uint32_t i = 0;
	for(; i < 10000; i++){
		if(  ((i*85)+8) >= firstPacketIndex && ( ((i*85)+8) -firstPacketIndex)<=93){
					break;
		}
	}
	uint8_t result = (93-(((i*85)+8)-firstPacketIndex));
	return result;
}

void ByteTo16Uint(uint16_t * Samples, uint8_t * PayloadBytes, uint16_t BytesLength)
	{
	uint8_t index=0;
		  for(int p =0; p<(BytesLength-1);p+=5){
			  Samples[index] = ((uint16_t)(PayloadBytes[p]) + (((uint16_t)PayloadBytes[p+4] & 0b11000000)<<2))<<2;
			  Samples[index+1] = ((uint16_t)(PayloadBytes[p+1]) + (((uint16_t)PayloadBytes[p+4] & 0b00110000)<<4))<<2;
			  Samples[index+2] = ((uint16_t)(PayloadBytes[p+2]) + (((uint16_t)PayloadBytes[p+4] & 0b00001100)<<6))<<2;
			  Samples[index+3] = ((uint16_t)(PayloadBytes[p+3]) + (((uint16_t)PayloadBytes[p+4] & 0b00000011)<<8))<<2;
				index+=4;
		  }
	}

void dispatchPackets(uint16_t * Samples, uint8_t * PayloadBytes, uint16_t BytesLength){
	static bool ArrayInitiate = false;
	if(ArrayInitiate == false){
		ArrayInitiate=true;
		for(uint8_t j=0;j<12;j++){for(uint8_t k=0;k<MaxData+1;k++){DataToDAC[j][k]=0;}}
	}

	ByteTo16Uint(Samples,PayloadBytes,BytesLength); 												//Get Data to Uint16
	uint8_t firstChannel = calculateFirstAcquisition(PayloadBytes[(BytesLength-1)],BytesLength);	//Check what is the first channel of the packet

	uint16_t actualSample;																			//Channel of the sample to save
	uint16_t actualIndex;																			//number of the same sample saved

	if(PayloadBytes[(BytesLength-1)] == 0 || PayloadBytes[(BytesLength-1)] == 84){
	//emberAfCorePrintln("Packets number: %d",PayloadBytes[(BytesLength-1)]);
		}

	for(uint8_t i = 0; i < (BytesLength-1)*8/10; i++)
  	{
		actualSample = packetsOrder[(firstChannel+i)%85];
		actualIndex = DataToDAC[packetsOrder[actualSample]][MaxData];

		DataToDAC[actualSample][actualIndex] = Samples[i];
		DataToDAC[actualSample][MaxData] +=1;

		if(PayloadBytes[(BytesLength-1)] == 0 || PayloadBytes[(BytesLength-1)] == 84){
		//emberAfCorePrint("%d ",DataToDAC[actualSample][actualIndex]);
			}

		if(DataToDAC[actualSample][MaxData]>19){DataToDAC[actualSample][MaxData] = 0;}
  	}
}



void dispatchPacketsDeltaEncoding(uint16_t * Samples, uint8_t * PayloadBytes, uint16_t BytesLength){
	if(PayloadBytes[BytesLength-1]>125){
		uint8_t BytesInCycle = 70;
		uint8_t referenceBytes = 15;
		uint8_t numberOfCycles =  BytesLength/BytesInCycle;
		uint8_t sampleIndex = 0;
		uint8_t sign; uint8_t reconstruction; uint8_t value;
		uint8_t packnumber = PayloadBytes[BytesLength-1]-150;
		for(uint8_t i = 0; i<numberOfCycles ;i++)
			{
				for(uint8_t k =(i*BytesInCycle) ; k<referenceBytes+ (i*BytesInCycle) ; k+=5)
					{

					  Samples[sampleIndex] = ((uint16_t)(PayloadBytes[k]) | (((uint16_t)(PayloadBytes[k+4] & 0b11000000))<<2))<<2;
					  Samples[sampleIndex+1] = ((uint16_t)(PayloadBytes[k+1]) | (((uint16_t)(PayloadBytes[k+4] & 0b00110000))<<4))<<2;
					  Samples[sampleIndex+2] = ((uint16_t)(PayloadBytes[k+2]) | (((uint16_t)(PayloadBytes[k+4] & 0b00001100))<<6))<<2;
					  Samples[sampleIndex+3] = ((uint16_t)(PayloadBytes[k+3]) | (((uint16_t)(PayloadBytes[k+4] & 0b00000011))<<8))<<2;
					  oldPackets[packetsOrder[sampleIndex%85]] = Samples[sampleIndex];
					  oldPackets[packetsOrder[(sampleIndex+1)%85]] = Samples[sampleIndex+1];
					  oldPackets[packetsOrder[(sampleIndex+2)%85]] = Samples[sampleIndex+2];
					  oldPackets[packetsOrder[(sampleIndex+3)%85]] = Samples[sampleIndex+3];
					  if(packnumber==0){emberAfCorePrintln("DAC:%d Payload:%d		%d %d %d %d  from %d %d %d %d %d",sampleIndex,k,
							  	  	  Samples[sampleIndex],Samples[sampleIndex+1],Samples[sampleIndex+2],Samples[sampleIndex+3],
									  PayloadBytes[k],PayloadBytes[k+1],PayloadBytes[k+2],PayloadBytes[k+3],PayloadBytes[k+4]);}
					  //emberAfCorePrintln("OLD PACKETS: %d %d %d %d",oldPackets[packetsOrder[sampleIndex%85]],oldPackets[packetsOrder[(sampleIndex+1)%85]],oldPackets[packetsOrder[(sampleIndex+2)%85]],oldPackets[packetsOrder[(sampleIndex+3)%85]]);
					  sampleIndex+=4;
					}

				for(uint8_t k = (i*BytesInCycle)+15; k<((i+1)*BytesInCycle) ; k+=3)
					{
						if(sampleIndex==52 || sampleIndex==137){
							sign = (PayloadBytes[k] & 0b00100000);
							value =(PayloadBytes[k] & 0b00011111)<<2;
							if(sign!=0){
								Samples[sampleIndex] = oldPackets[packetsOrder[(sampleIndex)%85]]+value;}
							else{Samples[sampleIndex] = oldPackets[packetsOrder[(sampleIndex)%85]]-value;}
							oldPackets[packetsOrder[(sampleIndex)%85]] = Samples[sampleIndex];
							if(packnumber==0){emberAfCorePrintln("DAC:%d Payload:%d   %d %d",sampleIndex,k,Samples[sampleIndex],PayloadBytes[k]);}
							k++;
							sampleIndex++;}

						for(uint8_t j = 0; j<4; j++){
							if(j<3){
							sign = (PayloadBytes[k+j] & 0b00100000);
							value =(PayloadBytes[k+j] & 0b00011111)<<2;
							if(sign!=0){
								Samples[sampleIndex+j] = oldPackets[packetsOrder[(sampleIndex+j)%85]]+value;}
							else{Samples[sampleIndex+j] = oldPackets[packetsOrder[(sampleIndex+j)%85]]-value;}
							oldPackets[packetsOrder[(sampleIndex+j)%85]] = Samples[sampleIndex+j];}
							else{
								reconstruction = (PayloadBytes[k] & 0b11000000)>>2 | ((PayloadBytes[k+1] & 0b11000000)>>4) | ((PayloadBytes[k+2] & 0b11000000)>>6);
								sign = (reconstruction & 0b00100000);
								value =(reconstruction & 0b00011111)<<2;
								if(sign!=0){Samples[sampleIndex+j] = oldPackets[packetsOrder[(sampleIndex+j)%85]]+value;}
								else{Samples[sampleIndex+j] = oldPackets[packetsOrder[(sampleIndex+j)%85]]-value;}
								oldPackets[packetsOrder[(sampleIndex+j)%85]] = Samples[sampleIndex+j];
							}
						}
						if(packnumber==0){emberAfCorePrintln("DAC:%d Payload:%d		%d %d %d %d from %d %d %d",sampleIndex,k,
													  	  	  Samples[sampleIndex],Samples[sampleIndex+1],Samples[sampleIndex+2],Samples[sampleIndex+3],
															  PayloadBytes[k],PayloadBytes[k+1],PayloadBytes[k+2]);}

						sampleIndex+=4;
						}
			}
		tempi+=1;
		if(tempi==1000){tempi = 0;}
	}
}








