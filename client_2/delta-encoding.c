/*
 * delta-encoding.c
 *
 *  Created on: Aug 13, 2020
 *      Author: Charles-Alexis
 */

#include "delta-encoding.h"

extern uint8_t packIndex;
uint16_t tempi=0;

uint8_t packetsOrder[85] = {0,1,2,3,4,5,6,7,8,9,10,11,  0,1,2,3,4,5,6,7,  0,1,2,3,4,5,6,7,  0,1,2,3,4,5,6,7,  0,1,2,3,4,5,6,7,                 //First 5 packets
							0,1,2,3,4,5,6,7,8,  0,1,2,3,4,5,6,7, 0,1,2,3,4,5,6,7,  0,1,2,3,4,5,6,7,  0,1,2,3,4,5,6,7}; //Last 5 packets +

uint16_t oldValues[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

void buildPayloadEncoding7(uint8_t * DeltaPackets, uint16_t * ADCData){
	uint8_t SubPacketIndex = 0;
	uint16_t ADCInd=0;
	//Reference Data
	for(uint8_t SubPacketIndex = 0; SubPacketIndex < 79; SubPacketIndex+=79){
		for(uint32_t p = SubPacketIndex; p<SubPacketIndex+15; p+=5){
			DeltaPackets[p] = (uint8_t)((ADCData[ADCInd])>>2);
			DeltaPackets[p+1] = (uint8_t)((ADCData[ADCInd+1])>>2);
			DeltaPackets[p+2] = (uint8_t)((ADCData[ADCInd+2])>>2);
			DeltaPackets[p+3] = (uint8_t)((ADCData[ADCInd+3])>>2);
			DeltaPackets[p+4] = ((ADCData[ADCInd]>>10)<<6)+((ADCData[ADCInd+1]>>10)<<4)+((ADCData[ADCInd+2]>>10)<<2)+((ADCData[ADCInd+3]>>10));
			oldValues[ADCInd%85] = ADCData[ADCInd]; oldValues[ADCInd%85+1] = ADCData[ADCInd+1];oldValues[ADCInd%85+2] = ADCData[ADCInd+2]; oldValues[ADCInd%85+3] = ADCData[ADCInd+3];

			/*emberAfCorePrintln("P: %d ADCIND: %d		%d %d %d %d to %d %d %d %d %d",p,ADCInd,
					ADCData[ADCInd],ADCData[ADCInd+1],ADCData[ADCInd+2],ADCData[ADCInd+3],
					DeltaPackets[p], DeltaPackets[p+1], DeltaPackets[p+2], DeltaPackets[p+3], DeltaPackets[p+4]);*/
			ADCInd+=4;
		}
	//Delta Data
	for(uint32_t p = SubPacketIndex+15; p<SubPacketIndex+79; p+=7)
		{
			int16_t delta;
			uint8_t sign;
			for(uint8_t i = 0; i<8; i++)
				{
					delta = oldValues[i] - (ADCData[ADCInd+i]); //Compare with the old  value
					sign = (delta >> 15) << 6;        //Get the Sign
					if(sign!=0){delta = (~delta)+1;}
					delta = (((delta)<<10)>>10) | sign;	  // 0b0SXX XXXX (X are the bits that are use)
					if(i==7){
						DeltaPackets[p] = DeltaPackets[p] | (((uint8_t)(delta)>>6)<<7);       //0b0X00 0000
						DeltaPackets[p+1] = DeltaPackets[p+1] | (((uint8_t)(delta)>>5)<<7);   //0b00X0 0000
						DeltaPackets[p+2] = DeltaPackets[p+2] | (((uint8_t)(delta)>>4)<<7);   //0b000X 0000
						DeltaPackets[p+3] = DeltaPackets[p+3] | (((uint8_t)(delta)>>3)<<7);   //0b0000 X000
						DeltaPackets[p+4] = DeltaPackets[p+4] | (((uint8_t)(delta)>>2)<<7);   //0b0000 0X00
						DeltaPackets[p+5] = DeltaPackets[p+5] | (((uint8_t)(delta)>>1)<<7);   //0b0000 00X0
						DeltaPackets[p+6] = DeltaPackets[p+6] | (((uint8_t)(delta)>>0)<<7);   //0b0000 000X
					}
					else{DeltaPackets[p+i] = delta;}          //Save to Packets
					oldValues[i] = ADCData[ADCInd+i];		  //Save to old value
				}

			/*emberAfCorePrintln("P: %d ADCIND: %d		%d %d %d %d %d %d %d %d to %d %d %d %d %d %d %d",p,ADCInd,
										ADCData[ADCInd],ADCData[ADCInd+1],ADCData[ADCInd+2],ADCData[ADCInd+3],ADCData[ADCInd+4],ADCData[ADCInd+5],ADCData[ADCInd+6],ADCData[ADCInd+7],
										DeltaPackets[p], DeltaPackets[p+1], DeltaPackets[p+2], DeltaPackets[p+3], DeltaPackets[p+4], DeltaPackets[p+5], DeltaPackets[p+6]);*/
			ADCInd+=8;
			if((ADCInd==52) | (ADCInd==137)){
				delta = ADCData[ADCInd] - oldValues[8];	  //Get
				sign = (delta >> 15) << 6;        //Get the Sign
				delta = ((((~delta)+1)<<2)>>2) | sign;
				DeltaPackets[p] = delta;
				//emberAfCorePrintln("P: %d ADCIND: %d		%d to %d",p,ADCInd,ADCData[ADCInd],DeltaPackets[p]);
				p++;
				ADCInd++;} //only 7 bits are used for the ECG #2
		}
		}
	DeltaPackets[79]=100+packIndex;
	packIndex+=1;
	if(packIndex==10){packIndex = 0;}
}

void buildPayloadEncoding6(uint8_t * DeltaPackets, uint16_t * ADCData){
	uint8_t SubPacketIndex = 0;
	uint16_t ADCInd=0;
	//Reference Data
	for(uint8_t SubPacketIndex = 0; SubPacketIndex < 140; SubPacketIndex+=70){
		for(uint32_t p = SubPacketIndex; p<SubPacketIndex+15; p+=5){
			DeltaPackets[p] = (uint8_t)((ADCData[ADCInd]));
			DeltaPackets[p+1] = (uint8_t)((ADCData[ADCInd+1]));
			DeltaPackets[p+2] = (uint8_t)((ADCData[ADCInd+2]));
			DeltaPackets[p+3] = (uint8_t)((ADCData[ADCInd+3]));
			DeltaPackets[p+4] = ((ADCData[ADCInd]>>8)<<6)|((ADCData[ADCInd+1]>>8)<<4)|((ADCData[ADCInd+2]>>8)<<2)|((ADCData[ADCInd+3]>>8));
			oldValues[ADCInd%85] = ADCData[ADCInd]; oldValues[ADCInd%85+1] = ADCData[ADCInd+1];oldValues[ADCInd%85+2] = ADCData[ADCInd+2]; oldValues[ADCInd%85+3] = ADCData[ADCInd+3];
			/*if(packIndex==0){emberAfCorePrintln("P: %d ADCIND: %d		%d %d %d %d to %d %d %d %d %d",p,ADCInd,
					ADCData[ADCInd]<<2,ADCData[ADCInd+1]<<2,ADCData[ADCInd+2]<<2,ADCData[ADCInd+3]<<2,
					DeltaPackets[p], DeltaPackets[p+1], DeltaPackets[p+2], DeltaPackets[p+3], DeltaPackets[p+4]);}*/
			ADCInd+=4;
		}

	//Delta Data
	for(uint32_t p = SubPacketIndex+15; p<SubPacketIndex+70; p+=6)
		{
			int16_t delta;
			uint8_t sign;
			if((ADCInd==52) | (ADCInd==137)){
							delta =oldValues[8]- ADCData[ADCInd];	  //Get
							sign = (delta & 0b100000);        //Get the Sign
							if(sign!=0){delta = (~delta)+1;}
							delta = (delta & 0b00011111) | sign;	  // 0b00SX XXXX (X are the bits that are use)
							DeltaPackets[p] = delta;
							//if(packIndex==0){emberAfCorePrintln("P: %d ADCIND: %d		%d to %d",p,ADCInd,ADCData[ADCInd]<<2,DeltaPackets[p]);}
							p++;
							ADCInd++;} //only 7 bits are used for the ECG #2

			for(uint8_t i = 0; i<8; i++)
				{
					delta = oldValues[i] - (ADCData[ADCInd+i]); //Compare with the old  value
					sign = (delta & 0b100000);        //Get the Sign
					if(sign!=0){delta = (~delta)+1;}
					delta = (delta & 0b00011111) | sign;	  // 0b00SX XXXX (X are the bits that are use)
					if(i==3){
						DeltaPackets[p+i-3] = DeltaPackets[p+i-3] | ((uint8_t)(delta & 0b110000)<<2);       //0b00XX 0000
						DeltaPackets[p+i-2] = DeltaPackets[p+i-2] | ((uint8_t)(delta & 0b1100)<<4);   //0b0000 XX00
						DeltaPackets[p+i-1] = DeltaPackets[p+i-1] | ((uint8_t)(delta & 0b11)<<6);   //0b0000 00XX
					}
					else if(i==7){
						DeltaPackets[p+i-4] = DeltaPackets[p+i-4] | ((uint8_t)(delta & 0b110000)<<2);       //0b00XX 0000
						DeltaPackets[p+i-3] = DeltaPackets[p+i-3] | ((uint8_t)(delta & 0b1100)<<4);   //0b0000 XX00
						DeltaPackets[p+i-2] = DeltaPackets[p+i-2] | ((uint8_t)(delta & 0b11)<<6);   //0b0000 00XX
					}
					else{
						if(i<3){
						DeltaPackets[p+i] = delta;}
						else{DeltaPackets[p+i-1] = delta;}
					}          //Save to Packets
					oldValues[i] = ADCData[ADCInd+i];		  //Save to old value
				}


			/*if(packIndex==0){emberAfCorePrintln("P: %d ADCIND: %d		%d %d %d %d %d %d %d %d to %d %d %d %d %d %d",p,ADCInd,
										ADCData[ADCInd]<<2,ADCData[ADCInd+1]<<2,ADCData[ADCInd+2]<<2,ADCData[ADCInd+3]<<2,ADCData[ADCInd+4]<<2,ADCData[ADCInd+5]<<2,ADCData[ADCInd+6]<<2,ADCData[ADCInd+7]<<2,
										DeltaPackets[p], DeltaPackets[p+1], DeltaPackets[p+2],DeltaPackets[p+3], DeltaPackets[p+4], DeltaPackets[p+5]);}*/
			ADCInd+=8;

		}

	}
	DeltaPackets[140]=150+packIndex;
	packIndex+=1;
	tempi+=1;
	if(tempi==1000){tempi = 0;}
	if(packIndex==50){packIndex = 1;}
}
