#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "DLL.h"

using namespace std;

DLL::DLL() {
	head = NULL;
}

struct DLL::Node* DLL::GetNewNode(int x) { // function to get new node (to be used in InsertBeforeHead and InsertAtTail functions
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // reserve some memory for this new node in the heap using malloc
	newNode->nodeValue = x; // same as saying (*newNode).nodeValue = x;
	newNode->prevNodeAddress = NULL;
	newNode->nextNodeAddress = NULL;
	return newNode;
}




int DLL::getMinimumKey() { // returns minimum key in the list
	struct Node* temp = head;
	int minKey = temp->nodeValue; // initialize to value of head node
	while (temp != NULL) { // step through list until temp is null
		if (temp->nodeValue < minKey) { // if this node's value is less than standing minimum
			minKey = temp->nodeValue; // then set it as the new standing minimum
		}
		temp = temp->nextNodeAddress; // set temp to next node
	}
	return minKey;
}

int DLL::getMaximumKey() { // returns maximum key in the list
	struct Node* temp = head;
	int maxKey = temp->nodeValue; // initialize to the value of the head node
	while (temp != NULL) { // step through list until temp is null
		if (temp->nodeValue > maxKey) { // if this node's value is greater than standing maximum
			maxKey = temp->nodeValue; // then set it as the new standing maximum
		}
		temp = temp->nextNodeAddress; // set temp to next node
	}
	return maxKey;
}

void DLL::deleteThisNode(int index) {
	struct Node* temp = head;
	int nodeIndex = 1; // initialze index to 1
	while (temp != NULL) { // step through list until temp is null
		if (index == nodeIndex) { // if we've traversed to the node we'd like to delete
			if (temp->prevNodeAddress == NULL && temp->nextNodeAddress == NULL) { // this is the only node in the list
				cout << endl << endl << "WARNING - YOU'RE DELETING THE ONLY NODE IN THE LIST!" << endl << endl;
				head = NULL; // wipe out the list
			}
			else if (temp->prevNodeAddress == NULL) { // head node
				temp->nextNodeAddress->prevNodeAddress = NULL; // assign NULL to the prev field of temp's next node (this is the new head node)
				head = temp->nextNodeAddress; // this is the new head node
			}
			else if (temp->nextNodeAddress == NULL) { // tail node
				temp->prevNodeAddress->nextNodeAddress = NULL; // assign NULL to the next field of temp's prev node (this is the new tail node)
			}
			else { // intermediate node (in between head and tail).  temp needs to step out of the middle
				temp->prevNodeAddress->nextNodeAddress = temp->nextNodeAddress; // point prev node's next address to temp's next address
				temp->nextNodeAddress->prevNodeAddress = temp->prevNodeAddress; // point next node's prev address to temp's prev address
			}
			cout << "Node of index #" << index << " has been deleted!  Here's the updated list:" << endl;
			PrintListForward(); // print the list again so the user can verify deletion
			return; // we can hereby exit the function, as it has performed its, uh, function
		}
		nodeIndex++; // increment node serial by 1 on each loop iteration
		temp = temp->nextNodeAddress; // set temp to next node
	}
	// if we've gotten to this point, the index was not found in the list.  we should warn the user
	cout << endl << "WARNING!!! Node of index " << index << " does not exist in the list, so nothing was deleted.";
	cout << endl;
}

int DLL::getNumberFromUser(string message) { // function to get input from user
	cout << endl << endl << message + ": ";
	int entry;
	cin >> entry;
	while (!cin) { // keep repeating until we have a valid entry
		cout << endl << "INVALID ENTRY! PLEASE ENTER AN INTEGER!! Try again." << endl;
		cin.clear(); // clear the input stream
		cin.ignore(256, '\n');
		cout << endl << endl << message + ": "; // repeat message
		cin >> entry;
	}
	cout << endl;
	return entry;
}

void DLL::InsertBeforeHead(int x) { // insert new node before head
	struct Node* newNode = GetNewNode(x);
	if (head == NULL) { // (check if we're trying to add to an empty list)
		head = newNode; // if so, this node we are trying to insert shall be the head node
		return; // exit the function, as this is the only node in the list
	}
	head->prevNodeAddress = newNode; // overwriting head's null pointer in prev field to the node we're inserting in front of it
	newNode->nextNodeAddress = head; // pointing newNode's next field to the address of old/current head node
	head = newNode; // setting the new head address to that of the new node we just created
}

void DLL::AppendAfterTail(int x) { // insert new node after tail
	struct Node* newNode = GetNewNode(x);
	if (head == NULL) { // (check if we're trying to add to an empty list)
		head = newNode; // if so, this node we are trying to insert shall be the head node
		return; // exit the function, as this is the only node in the list
	}

	struct Node* temp = head; // temporary pointer to head node
	while (temp->nextNodeAddress != NULL) { // steps through list until final node is reached
		temp = temp->nextNodeAddress;		 // and sets temp to the last/final node in the list
	}

	// at this point, temp should be the final node in the list.  now we can append the new node
	temp->nextNodeAddress = newNode; // point the last node's next field to the new node's address
	newNode->prevNodeAddress = temp; // point the new node's prev field to the last node's address

}

void DLL::PrintListForward() {
	struct Node* temp = head;
	printf("Forward:\n");
	int nodeIndex = 1;
	while (temp != NULL) { // step through list until temp is null
		cout << "Node #" << nodeIndex << ": " << temp->nodeValue << endl;
		nodeIndex++; // increment node serial by 1 on each loop iteration
		temp = temp->nextNodeAddress; // set temp to next node
	}
	cout << endl;
}

void DLL::PrintListReverse() {
	struct Node* temp = head;
	if (temp == NULL) return; // exit if empty list

	int nodeIndex = 1; // initialize at 1 (at this point we only know about 1 node)
	while (temp->nextNodeAddress != NULL) { // steps through list until final node is reached
		temp = temp->nextNodeAddress;		 // and sets temp to the last/final node in the list
		nodeIndex++; // increment node serial by 1 for each new node found
	}

	// traverse backward using prev pointer
	printf("Reverse:\n");
	while (temp != NULL) { // step through list until temp is null
		cout << "Node #" << nodeIndex << ": " << temp->nodeValue << endl;
		nodeIndex--; // decrement node serial by 1 on each loop iteration
		temp = temp->prevNodeAddress; // set temp to prev node
	}
	cout << endl;
}

void DLL::populateList1to10() {
	head = NULL; // reset head to null to start new empty list
	for (int i = 1; i < 11; i++) { // repeat for 1 through 10 and then stop
		AppendAfterTail(i);
	}
}

void DLL::nullifyHead() {
	head = NULL; // reset list to empty by destroying the head node
}

DLL::Node* DLL::Find(int valueToFind) { // returns a pointer to the first node in the list whose key matches specified value
	struct Node* temp = head;
	while (temp != NULL) { // step through list until temp is null
		if (valueToFind == temp->nodeValue) { // match found! return it
			return temp;
		}
		temp = temp->nextNodeAddress; // set temp to next node
	}
	return NULL; // if we get to this point, the specified key was not found, so we can return NULL
}

void DLL::getMinMax() { // prints minimum and maximum keys in the list
	if (head == NULL) { // check for empty list before performing operations on it
		cout << endl << "LIST IS EMPTY!" << endl;
		return; // exit the function because the list is empty, so there are no values to check
	}
	cout << endl << endl << "MINIMUM value in the list is " << getMinimumKey();
	cout << endl << endl << "MAXIMUM value in the list is " << getMaximumKey();
	cout << endl << endl;
}

void DLL::deleteNode() {
	if (head == NULL) { // check for empty list before performing operations on it
		cout << endl << "LIST IS EMPTY!" << endl;
		return; // exit the function because the list is empty, so there is nothing to delete
	}
	// first print node list
	PrintListForward();
	// then, let user choose index to delete
	deleteThisNode(getNumberFromUser("ENTER THE INDEX OF THE NODE YOU'D LIKE TO DELETE"));
}