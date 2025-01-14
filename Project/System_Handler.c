/***************************************************************************
 * @file    System_Handler.c
 * @brief   Define functions to handle main system
 * @details This file defines functions to handle main system, such as file 
 *					operations, linked list.
 * @version 1.0
 * @date    2024-10-22
 * @author  Tran Quang Khai
 ***************************************************************************/
#include "System_Handler.h"

/**************************************************************************
 * @brief   Convert list to array
 * @details This function converts all nodes in the list and save to an array.
 * @param   head			Pointer to first node of linked list
 * @param   uids			Array that stores UID 		
 * @param 	maxSize		Number of nodes in the list
 * @return  int				Return number of UIDs in the list
 **************************************************************************/
int convertListToArray(Node* head, uint8_t uids[][5], int maxSize)
{
	int count = 0;
	Node* current = head;
	
	while (current != NULL && count < maxSize) {
		memcpy(uids[count], current->uid, 5);
		count++;
		current = current->next;
	}
	
	return count;
}

/**************************************************************************
 * @brief   Compare 2 UIDs
 * @details This function compares 2 UIDs.
 * @param   a			Pointer to the first UID
 * @param   b			Pointer to the second UID		
 * @return  int		Return a negative value if the first UID is less than the second UID
 *										 	 0 if the two UIDs are equal
 *										 	 a positive value if the first UID is greater than the second UID
 **************************************************************************/
int compareUIDs(const void* a, const void* b) 
{
	return memcmp(a, b, 5); 
}

/**************************************************************************
 * @brief   Sort UIDs
 * @details This function sorts the UIDs in the array in ascending order.
 * @param   uids		Array that want to sort
 * @param   count		Number of UIDs in the array			
 * @return  void
 **************************************************************************/
void sortUIDs(uint8_t uids[][5], int count) 
{
	qsort(uids, count, 5 * sizeof(uint8_t), compareUIDs);
}

/**************************************************************************
 * @brief   Search UID
 * @details This function search UID in the array by using binary search.
 * @param   uids				Array that want to search UID
 * @param   count				Number of UIDs in the array	
 * @param		targetUID		UID to search
 * @return  bool				Return true if found UID
 *														 false if not found UID
 **************************************************************************/
bool binarySearchUID(uint8_t uids[][5], int count, uint8_t* targetUID) 
{
	int low = 0, high = count - 1;

	while (low <= high) {
		int mid = (low + high) / 2;
		int cmp = memcmp(uids[mid], targetUID, 5);

		if (cmp == 0) {
			return true; 
		} else if (cmp < 0) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
  return false; 
}

/**************************************************************************
 * @brief   Add UID to linked list
 * @details This function adds a node contain RFID tag UID to linked list.
 * @param   head		Pointer to first node of linked list
 * @param   newID		New ID to add to linked list
 * @return  void
 **************************************************************************/
void addNode(Node** head, uint8_t* newUID)
{
	Node *newNode = (Node*)malloc(sizeof(Node));
	
	if (newNode == NULL) {
		printf("Memory allocation failed!\n");
    return;
	}
	
	memcpy(newNode->uid, newUID, 5);
	newNode->next = NULL;
	
	if (*head == NULL) {
		*head = newNode;
	} else {
		Node* temp = *head; 
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
}