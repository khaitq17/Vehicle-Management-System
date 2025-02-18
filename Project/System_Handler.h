/***************************************************************************
 * @file    System_Handler.h
 * @brief   Declare functions to handle main system
 * @details This file includes necessary functions to handle main system,  
 *					such as file operations, linked list.
 * @version 1.0
 * @date    2024-10-22
 * @author  Tran Quang Khai
 ***************************************************************************/
#ifndef __SYSTEM_HANDLER_H
#define __SYSTEM_HANDLER_H

#include "MFRC522.h"
#include "ff.h"
#include "fatfs.h"
#include "fatfs_sd.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**************************************************************************
 * Define number of UIDs used in the the system
 **************************************************************************/
#define MAX_UIDS 4

/**************************************************************************
 * @struct Node define 1 node of linked list
 * uid[5]	 UID of a RFID tag
 * next		 Pointer to the next node of linked list
 **************************************************************************/
typedef struct Node {
	uint8_t uid[5];		// UID of a RFID tag
	struct Node* next;	// Pointer to the next node of linked list
} Node;

/**************************************************************************
 * @brief   Convert list to array
 * @param   head			Pointer to first node of linked list
 * @param   uids			Array that stores UID 		
 * @param 	maxSize			Number of nodes in the list
 * @return  int				Return number of UIDs in the list
 **************************************************************************/
int convertListToArray(Node* head, uint8_t uids[][5], int maxSize);

/**************************************************************************
 * @brief   Compare 2 UIDs
 * @param   a		Pointer to the first UID
 * @param   b		Pointer to the second UID		
 * @return  int		Return a negative value if the first UID is less than the second UID
 *						   0 if the two UIDs are equal
 *						   a positive value if the first UID is greater than the second UID
 **************************************************************************/
int compareUIDs(const void* a, const void* b);

/**************************************************************************
 * @brief   Sort UIDs
 * @param   uids		Array that want to sort
 * @param   count		Number of UIDs in the array			
 * @return  void
 **************************************************************************/
void sortUIDs(uint8_t uids[][5], int count); 

/**************************************************************************
 * @brief   Search UID
 * @param   uids				Array that want to search UID
 * @param   count				Number of UIDs in the array	
 * @param	targetUID			UID to search
 * @return  bool				Return true if found UID
 *														 false if not found UID
 **************************************************************************/
bool binarySearchUID(uint8_t uids[][5], int count, uint8_t* targetUID); 

/**************************************************************************
 * @brief   Add UID to linked list
 * @param   head		Pointer to first node of linked list
 * @param   newID		New ID to add to linked list
 * @return  void
 **************************************************************************/
void addNode(Node** head, uint8_t* newUID); 

#endif	/* __SYSTEM_HANDLER_H */