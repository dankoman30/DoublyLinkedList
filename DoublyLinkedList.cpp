#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Node {
	int nodeValue;
	struct Node* nextNodeAddress;
	struct Node* prevNodeAddress;
};

struct Node* head; // (global) pointer to head node

struct Node* GetNewNode(int x) { // function to get new node (to be used in InsertBeforeHead and InsertAtTail functions
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // reserve some memory for this new node in the heap using malloc
	newNode->nodeValue = x; // same as saying (*newNode).nodeValue = x;
	newNode->prevNodeAddress = NULL;
	newNode->nextNodeAddress = NULL;
	return newNode;
}
void InsertBeforeHead(int x) { // insert new node before head
	struct Node* newNode = GetNewNode(x);
	if (head == NULL) { // (check if we're trying to add to an empty list)
		head = newNode; // if so, this node we are trying to insert shall be the head node
		return; // exit the function, as this is the only node in the list
	}
	head->prevNodeAddress = newNode; // overwriting head's null pointer in prev field to the node we're inserting in front of it
	newNode->nextNodeAddress = head; // pointing newNode's next field to the address of old/current head node
	head = newNode; // setting the new head address to that of the new node we just created
}

void AppendAfterTail(int x) { // insert new node after tail
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

void PrintListForward() {
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

void PrintListReverse() {
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

int getNumberFromUser(string message) { // function to get input from user
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

void populateList1to10() {
	head = NULL; // reset head to null to start new empty list
	for (int i = 1; i < 11; i++) { // repeat for 1 through 10 and then stop
		AppendAfterTail(i);
	}
}

void nullifyHead() {
	head = NULL; // reset list to empty by destroying the head node
}

Node* Find(int valueToFind) { // returns a pointer to the first node in the list whose key matches specified value
	struct Node* temp = head;
	while (temp != NULL) { // step through list until temp is null
		if (valueToFind == temp->nodeValue) { // match found! return it
			return temp;
		}
		temp = temp->nextNodeAddress; // set temp to next node
	}
	return NULL; // if we get to this point, the specified key was not found, so we can return NULL
}

int getMinimumKey() { // returns minimum key in the list
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

int getMaximumKey() { // returns maximum key in the list
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

void getMinMax() { // prints minimum and maximum keys in the list
	if (head == NULL) { // check for empty list before performing operations on it
		cout << endl << "LIST IS EMPTY!" << endl;
		return; // exit the function because the list is empty, so there are no values to check
	}
	cout << endl << endl << "MINIMUM value in the list is " << getMinimumKey();
	cout << endl << endl << "MAXIMUM value in the list is " << getMaximumKey();
	cout << endl << endl;
}

void deleteThisNode(int index) {
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

void deleteNode() {
	if (head == NULL) { // check for empty list before performing operations on it
		cout << endl << "LIST IS EMPTY!" << endl;
		return; // exit the function because the list is empty, so there is nothing to delete
	}
	// first print node list
	PrintListForward();
	// then, let user choose index to delete
	deleteThisNode(getNumberFromUser("ENTER THE INDEX OF THE NODE YOU'D LIKE TO DELETE"));
}

int main() {
	head = NULL; // initialize head to NULL

    for (;;) { // main loop
        cout << "\nWhat would you like to do?\n1. Create new linked list of integers 1 through 10\n2. Reset entire list to empty\n3. Print list FORWARD\n4. Print list in REVERSE\n5. Insert new node before head\n6. Append new node to end of list\n7. Get memory address of node with specified value (FIND)\n8. Get minimum and maximum values in the list\n9. Delete a node of specified index\n0. EXIT\n\n";
		int choice = getNumberFromUser("ENTER A CHOICE");
        switch (choice) {
        case 1: // create new list 1-10
			populateList1to10();
            continue;
        case 2: // reset list to empty (nullify head)
			nullifyHead();
            continue;
        case 3: // print list forward
			PrintListForward();
            continue;
        case 4: // print list reverse
			PrintListReverse();
			continue;
        case 5: // insert new node before head
			InsertBeforeHead(getNumberFromUser("ENTER NEW VALUE TO INSERT AT THE BEGINNING OF THE LIST"));
			continue;
        case 6: // append new node after tail
			AppendAfterTail(getNumberFromUser("ENTER NEW VALUE TO APPEND TO THE END OF THE LIST"));
			continue;
		case 7: // find memory address of specified value
			choice = getNumberFromUser("ENTER A VALUE TO FIND IN THE LIST");
			cout << endl << "Memory address of first list entry matching " << choice << " is " << Find(choice) << endl;
			continue;
		case 8: // get minimum and maximum values (keys)
			getMinMax();
			continue;
		case 9: // delete a node of specified index
			deleteNode();
			continue;
        case 0: // exit
            cout << "\n\nBYE!!!\n\n";
            break; // exit loop
        }
        break; // exit program
    }
}