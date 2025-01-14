#include "MFRC522.h"
#include "GPIO.h"
#include "SPI.h"

/*
* Function: TM_MFRC522_Init
* Description: This function initializes module RFID MFRC522
* Input: 
*		None
* Output: 
*		Returns none
*/
void TM_MFRC522_Init(void) {
	MFRC522_InitPins();
	SPI_Config();

	TM_MFRC522_Reset();

	TM_MFRC522_WriteRegister(MFRC522_REG_T_MODE, 0x8D);
	TM_MFRC522_WriteRegister(MFRC522_REG_T_PRESCALER, 0x3E);
	TM_MFRC522_WriteRegister(MFRC522_REG_T_RELOAD_L, 30);           
	TM_MFRC522_WriteRegister(MFRC522_REG_T_RELOAD_H, 0);

	/* 48dB gain */
	TM_MFRC522_WriteRegister(MFRC522_REG_RF_CFG, 0x70);
	
	TM_MFRC522_WriteRegister(MFRC522_REG_TX_AUTO, 0x40);
	TM_MFRC522_WriteRegister(MFRC522_REG_MODE, 0x3D);

	TM_MFRC522_AntennaOn();		//Open the antenna
}

/*
* Function: TM_MFRC522_Check
* Description: This function checks for RFID card existance
* Input: 
*		id - pointer to 5 bytes long memory to store valid card id in
*		ID is valid only if card is detected, so when function returns MI_OK
* Output: 
*		Returns MI_OK if card is detected
*/
TM_MFRC522_Status_t TM_MFRC522_Check(uint8_t* id) {
	TM_MFRC522_Status_t status;
	//Find cards, return card type
	status = TM_MFRC522_Request(PICC_REQIDL, id);	
	if (status == MI_OK) {
		//Card detected
		//Anti-collision, return card serial number 4 bytes
		status = TM_MFRC522_Anticoll(id);	
	}
	TM_MFRC522_Halt();			//Command card into hibernation 

	return status;
}

/*
* Function: TM_MFRC522_Compare
* Description: This function compares 2 RFID ID
* Input: 
*		CardID - pointer to 5 bytes detected card ID
*		CompareID - pointer to 5 bytes your ID
* Output: 
*		Returns MI_OK if IDs are the same, or MI_ERR if not
*/
TM_MFRC522_Status_t TM_MFRC522_Compare(uint8_t* CardID, uint8_t* CompareID) {
	uint8_t i;
	for (i = 0; i < 5; i++) {
		if (CardID[i] != CompareID[i]) {
			return MI_ERR;
		}
	}
	return MI_OK;
}

/*
* Function: TM_MFRC522_WriteRegister
* Description: This function writes data to MFRC522's register
* Input: 
*		addr - address of register to write data
*		val - value that write to register 
* Output:
*		Returns none
*/
void TM_MFRC522_WriteRegister(uint8_t addr, uint8_t val) {
	//CS low
	MFRC522_CS_LOW;
	//Send address
	MFRC522_SPI_Send((addr << 1) & 0x7E);
	//Send data	
	MFRC522_SPI_Send(val);
	//CS high
	MFRC522_CS_HIGH;
}

/*
* Function: TM_MFRC522_ReadRegister
* Description: This function reads data from MFRC522's register
* Input: 
*		addr - address of register to read data 
* Output: 
*		Returns value read from register
*/
uint8_t TM_MFRC522_ReadRegister(uint8_t addr) {
	uint8_t val;
	//CS low
	MFRC522_CS_LOW;

	MFRC522_SPI_Send(((addr << 1) & 0x7E) | 0x80);	
	val = MFRC522_SPI_Send(MFRC522_DUMMY);
	//CS high
	MFRC522_CS_HIGH;

	return val;	
}

/*
* Function: TM_MFRC522_SetBitMask
* Description: This function sets some specific bits in MFRC522's register
* Input: 
*		reg - register want to set bits
*		mask - mask to set bits
* Output:
*		Returns none
*/
void TM_MFRC522_SetBitMask(uint8_t reg, uint8_t mask) {
	TM_MFRC522_WriteRegister(reg, TM_MFRC522_ReadRegister(reg) | mask);
}

/*
* Function: TM_MFRC522_ClearBitMask
* Description: This function clears some specific bits in MFRC522's register
* Input: 
*		reg - register want to clear bits
*		mask - mask to clear bits
* Output:
*		Returns none
*/
void TM_MFRC522_ClearBitMask(uint8_t reg, uint8_t mask){
	TM_MFRC522_WriteRegister(reg, TM_MFRC522_ReadRegister(reg) & (~mask));
} 

/*
* Function: TM_MFRC522_AntennaOn
* Description: This function turns on the antenna of the MFRC522
* Input: 
*		None
* Output:
*		Returns none
*/
void TM_MFRC522_AntennaOn(void) {
	uint8_t temp;

	temp = TM_MFRC522_ReadRegister(MFRC522_REG_TX_CONTROL);
	if (!(temp & 0x03)) {
		TM_MFRC522_SetBitMask(MFRC522_REG_TX_CONTROL, 0x03);
	}
}

/*
* Function: TM_MFRC522_AntennaOff
* Description: This function turns off the antenna of the MFRC522
* Input: 
*		None
* Output:
*		Returns none
*/
void TM_MFRC522_AntennaOff(void) {
	TM_MFRC522_ClearBitMask(MFRC522_REG_TX_CONTROL, 0x03);
}

/*
* Function: TM_MFRC522_Reset
* Description: This function resets MFRC522, return to its original state
* Input: 
*		None
* Output:
*		Returns none
*/
void TM_MFRC522_Reset(void) {
	TM_MFRC522_WriteRegister(MFRC522_REG_COMMAND, PCD_RESETPHASE);
}

/*
* Function: TM_MFRC522_Request
* Description: This function sends a request to find nearby cards
* Input: 
*		reqMode - mode request
*		TagType - pointer to save the detected tag type
* Output:
*		Returns MI_OK if card is detected
*/
TM_MFRC522_Status_t TM_MFRC522_Request(uint8_t reqMode, uint8_t* TagType) {
	TM_MFRC522_Status_t status;  
	uint16_t backBits;			//The received data bits

	TM_MFRC522_WriteRegister(MFRC522_REG_BIT_FRAMING, 0x07);		//TxLastBists = BitFramingReg[2..0]	???

	TagType[0] = reqMode;
	status = TM_MFRC522_ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);

	if ((status != MI_OK) || (backBits != 0x10)) {    
		status = MI_ERR;
	}

	return status;
}

/*
* Function: TM_MFRC522_ToCard
* Description: This function sends commands to the card and receives responses from the card
* Input: 
*		command - command to send to the card
*		sendData - data to send
*		sendLen - length of data to send
*		sendData - response data from the card
*		sendLen - length of response data
* Output:
*		Returns status, MI_OK if card is detected
*/
TM_MFRC522_Status_t TM_MFRC522_ToCard(uint8_t command, uint8_t* sendData, uint8_t sendLen, uint8_t* backData, uint16_t* backLen) {
	TM_MFRC522_Status_t status = MI_ERR;
	uint8_t irqEn = 0x00;
	uint8_t waitIRq = 0x00;
	uint8_t lastBits;
	uint8_t n;
	uint16_t i;

	switch (command) {
		case PCD_AUTHENT: {
			irqEn = 0x12;
			waitIRq = 0x10;
			break;
		}
		case PCD_TRANSCEIVE: {
			irqEn = 0x77;
			waitIRq = 0x30;
			break;
		}
		default:
			break;
	}

	TM_MFRC522_WriteRegister(MFRC522_REG_COMM_IE_N, irqEn | 0x80);
	TM_MFRC522_ClearBitMask(MFRC522_REG_COMM_IRQ, 0x80);
	TM_MFRC522_SetBitMask(MFRC522_REG_FIFO_LEVEL, 0x80);

	TM_MFRC522_WriteRegister(MFRC522_REG_COMMAND, PCD_IDLE);

	//Writing data to the FIFO
	for (i = 0; i < sendLen; i++) {   
		TM_MFRC522_WriteRegister(MFRC522_REG_FIFO_DATA, sendData[i]);    
	}

	//Execute the command
	TM_MFRC522_WriteRegister(MFRC522_REG_COMMAND, command);
	if (command == PCD_TRANSCEIVE) {    
		TM_MFRC522_SetBitMask(MFRC522_REG_BIT_FRAMING, 0x80);		//StartSend=1,transmission of data starts  
	}   

	//Waiting to receive data to complete
	i = 2000;	//i according to the clock frequency adjustment, the operator M1 card maximum waiting time 25ms???
	do {
		//CommIrqReg[7..0]
		//Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
		n = TM_MFRC522_ReadRegister(MFRC522_REG_COMM_IRQ);
		i--;
	} while ((i!=0) && !(n&0x01) && !(n&waitIRq));

	TM_MFRC522_ClearBitMask(MFRC522_REG_BIT_FRAMING, 0x80);			//StartSend=0

	if (i != 0)  {
		if (!(TM_MFRC522_ReadRegister(MFRC522_REG_ERROR) & 0x1B)) {
			status = MI_OK;
			if (n & irqEn & 0x01) {   
				status = MI_NOTAGERR;			
			}

			if (command == PCD_TRANSCEIVE) {
				n = TM_MFRC522_ReadRegister(MFRC522_REG_FIFO_LEVEL);
				lastBits = TM_MFRC522_ReadRegister(MFRC522_REG_CONTROL) & 0x07;
				if (lastBits) {   
					*backLen = (n - 1) * 8 + lastBits;   
				} else {   
					*backLen = n * 8;   
				}

				if (n == 0) {   
					n = 1;    
				}
				if (n > MFRC522_MAX_LEN) {   
					n = MFRC522_MAX_LEN;   
				}

				//Reading the received data in FIFO
				for (i = 0; i < n; i++) {   
					backData[i] = TM_MFRC522_ReadRegister(MFRC522_REG_FIFO_DATA);    
				}
			}
		} else {   
			status = MI_ERR;  
		}
	}

	return status;
}

/*
* Function: TM_MFRC522_Anticoll
* Description: This function prevents collisions if there are multiple tags close together
* Input: 
*		serNum - pointer to store the serial number of the detected card
* Output:
*		Returns status, MI_OK if card is detected
*/
TM_MFRC522_Status_t TM_MFRC522_Anticoll(uint8_t* serNum) {
	TM_MFRC522_Status_t status;
	uint8_t i;
	uint8_t serNumCheck = 0;
	uint16_t unLen;

	TM_MFRC522_WriteRegister(MFRC522_REG_BIT_FRAMING, 0x00);		//TxLastBists = BitFramingReg[2..0]

	serNum[0] = PICC_ANTICOLL;
	serNum[1] = 0x20;
	status = TM_MFRC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

	if (status == MI_OK) {
		//Check card serial number
		for (i = 0; i < 4; i++) {   
			serNumCheck ^= serNum[i];
		}
		if (serNumCheck != serNum[i]) {   
			status = MI_ERR;    
		}
	}
	return status;
} 

/*
* Function: TM_MFRC522_CalculateCRC
* Description: This function calculates the CRC value for the data sent to the card
* Input: 
*		pIndata - input data
*		len - length of input data
*		pOutData - pointer to store CRC result
* Output:
*		Returns none
*/
void TM_MFRC522_CalculateCRC(uint8_t*  pIndata, uint8_t len, uint8_t* pOutData) {
	uint8_t i, n;

	TM_MFRC522_ClearBitMask(MFRC522_REG_DIV_IRQ, 0x04);			//CRCIrq = 0
	TM_MFRC522_SetBitMask(MFRC522_REG_FIFO_LEVEL, 0x80);			//Clear the FIFO pointer
	//Write_MFRC522(CommandReg, PCD_IDLE);

	//Writing data to the FIFO	
	for (i = 0; i < len; i++) {   
		TM_MFRC522_WriteRegister(MFRC522_REG_FIFO_DATA, *(pIndata+i));   
	}
	TM_MFRC522_WriteRegister(MFRC522_REG_COMMAND, PCD_CALCCRC);

	//Wait CRC calculation is complete
	i = 0xFF;
	do {
		n = TM_MFRC522_ReadRegister(MFRC522_REG_DIV_IRQ);
		i--;
	} while ((i!=0) && !(n&0x04));			//CRCIrq = 1

	//Read CRC calculation result
	pOutData[0] = TM_MFRC522_ReadRegister(MFRC522_REG_CRC_RESULT_L);
	pOutData[1] = TM_MFRC522_ReadRegister(MFRC522_REG_CRC_RESULT_M);
}

/*
* Function: TM_MFRC522_SelectTag
* Description: This function selects a specific RFID card
* Input: 
*		serNum - serial number of selected card
* Output:
*		Returns response data size from card
*/
uint8_t TM_MFRC522_SelectTag(uint8_t* serNum) {
	uint8_t i;
	TM_MFRC522_Status_t status;
	uint8_t size;
	uint16_t recvBits;
	uint8_t buffer[9]; 

	buffer[0] = PICC_SElECTTAG;
	buffer[1] = 0x70;
	for (i = 0; i < 5; i++) {
		buffer[i+2] = *(serNum+i);
	}
	TM_MFRC522_CalculateCRC(buffer, 7, &buffer[7]);		//??
	status = TM_MFRC522_ToCard(PCD_TRANSCEIVE, buffer, 9, buffer, &recvBits);

	if ((status == MI_OK) && (recvBits == 0x18)) {   
		size = buffer[0]; 
	} else {   
		size = 0;    
	}

	return size;
}

/*
* Function: TM_MFRC522_Auth
* Description: This function authenticates with the card before reading or writing data
* Input: 
*		authMode - authentication mode
*		BlockAddr - block data address
*		Sectorkey - key for the block data
*		serNum - serial number of the card
* Output:
*		Returns status, MI_OK if card is detected
*/
TM_MFRC522_Status_t TM_MFRC522_Auth(uint8_t authMode, uint8_t BlockAddr, uint8_t* Sectorkey, uint8_t* serNum) {
	TM_MFRC522_Status_t status;
	uint16_t recvBits;
	uint8_t i;
	uint8_t buff[12]; 

	//Verify the command block address + sector + password + card serial number
	buff[0] = authMode;
	buff[1] = BlockAddr;
	for (i = 0; i < 6; i++) {    
		buff[i+2] = *(Sectorkey+i);   
	}
	for (i=0; i<4; i++) {    
		buff[i+8] = *(serNum+i);   
	}
	status = TM_MFRC522_ToCard(PCD_AUTHENT, buff, 12, buff, &recvBits);

	if ((status != MI_OK) || (!(TM_MFRC522_ReadRegister(MFRC522_REG_STATUS2) & 0x08))) {   
		status = MI_ERR;   
	}

	return status;
}

/*
* Function: TM_MFRC522_Read
* Description: This function reads data from block address
* Input: 
*		blockAddr - address of the block of data to be read
*		recvData - pointer to store the data read from the card 
* Output:
*		Returns status, MI_OK if card is detected
*/
TM_MFRC522_Status_t TM_MFRC522_Read(uint8_t blockAddr, uint8_t* recvData) {
	TM_MFRC522_Status_t status;
	uint16_t unLen;

	recvData[0] = PICC_READ;
	recvData[1] = blockAddr;
	TM_MFRC522_CalculateCRC(recvData,2, &recvData[2]);
	status = TM_MFRC522_ToCard(PCD_TRANSCEIVE, recvData, 4, recvData, &unLen);

	if ((status != MI_OK) || (unLen != 0x90)) {
		status = MI_ERR;
	}

	return status;
}

/*
* Function: TM_MFRC522_Write
* Description: This function writes data to block address
* Input: 
*		blockAddr - address of the block of data to write
*		writeData - pointer to write the data to the card 
* Output:
*		Returns status, MI_OK if card is detected
*/
TM_MFRC522_Status_t TM_MFRC522_Write(uint8_t blockAddr, uint8_t* writeData) {
	TM_MFRC522_Status_t status;
	uint16_t recvBits;
	uint8_t i;
	uint8_t buff[18]; 

	buff[0] = PICC_WRITE;
	buff[1] = blockAddr;
	TM_MFRC522_CalculateCRC(buff, 2, &buff[2]);
	status = TM_MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);

	if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A)) {   
		status = MI_ERR;   
	}

	if (status == MI_OK) {
		//Data to the FIFO write 16Byte
		for (i = 0; i < 16; i++) {    
			buff[i] = *(writeData+i);   
		}
		TM_MFRC522_CalculateCRC(buff, 16, &buff[16]);
		status = TM_MFRC522_ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);

		if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A)) {   
			status = MI_ERR;   
		}
	}

	return status;
}

/*
* Function: TM_MFRC522_Halt
* Description: This function puts an RFID tag into a “halt” or “sleep” states
* Input: 
*		None 
* Output:
*		Returns none
*/
void TM_MFRC522_Halt(void) {
	uint16_t unLen;
	uint8_t buff[4]; 

	buff[0] = PICC_HALT;
	buff[1] = 0;
	TM_MFRC522_CalculateCRC(buff, 2, &buff[2]);

	TM_MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &unLen);
}
