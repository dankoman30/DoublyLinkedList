#pragma once

#include <chrono>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

template<typename type>
class DLL {
private:
	struct Node {
		type nodeValue;
		struct Node* nextNodeAddress;
		struct Node* prevNodeAddress;
	};

	struct Node* head; // pointer to head node

	class performanceAnalyzer { // performance analyzer class to construct an object to track function execution times
	private:
		std::chrono::steady_clock::time_point startTime, endTime; // PERFORMANCE ANALYSIS
		duration<double, std::milli> runtimeMillis;

		auto getTime() {
			return high_resolution_clock::now();
		}
	public:
		void start() {
			startTime = getTime();
		}
		void end() {
			endTime = getTime();
			runtimeMillis = endTime - startTime;
			cout << "\n*************************************************************\n";
			cout << "\nPERFORMANCE ANALYSIS: THAT OPERATION TOOK " << runtimeMillis.count() << " ms.\n";
			cout << "\n*************************************************************\n\n";
		}
	};

	performanceAnalyzer pa; // instantiate performance analyzer

	int getLength() { // method to retrieve the size of the list
		struct Node* temp = head;
		int length = 0; // initialize list length to 0 (because we don't yet know if head is null, indicating 0 length)
		while (temp != NULL) { // step through list until temp is null
			length++; // increment length by 1 on each loop iteration
			temp = temp->nextNodeAddress; // set temp to next node
		}
		return length;
	}

	struct Node* GetNewNode(type x) { // function to get new node (to be used in InsertBeforeHead and InsertAtTail functions
		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // reserve some memory for this new node in the heap using malloc
		newNode->nodeValue = x; // same as saying (*newNode).nodeValue = x;
		newNode->prevNodeAddress = NULL;
		newNode->nextNodeAddress = NULL;
		return newNode;
	}

	type getMinimumKey() { // returns minimum key in the list
		struct Node* temp = head;
		type minKey = temp->nodeValue; // initialize to value of head node
		while (temp != NULL) { // step through list until temp is null
			if (temp->nodeValue < minKey) { // if this node's value is less than standing minimum
				minKey = temp->nodeValue; // then set it as the new standing minimum
			}
			temp = temp->nextNodeAddress; // set temp to next node
		}
		return minKey;
	}

	type getMaximumKey() { // returns maximum key in the list
		struct Node* temp = head;
		type maxKey = temp->nodeValue; // initialize to the value of the head node
		while (temp != NULL) { // step through list until temp is null
			if (temp->nodeValue > maxKey) { // if this node's value is greater than standing maximum
				maxKey = temp->nodeValue; // then set it as the new standing maximum
			}
			temp = temp->nextNodeAddress; // set temp to next node
		}
		return maxKey;
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

	void privateDeleteList(Node** rHead) // method to delete the entire list
	{
		Node* current = *rHead;
		Node* next = NULL;

		while (current != NULL) // iterate through the list, freeing each node from memory
		{
			next = current->nextNodeAddress;
			free(current);
			current = next;
		}

		*rHead = NULL; // dereference the head
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

	void sortedInsert(struct Node** head, struct Node* newNode) {
		struct Node* currentNode;

		if (*head == NULL) {
			*head = newNode; // if it's an empty list, the new node will be the head
		}
		else if ((*head)->nodeValue >= newNode->nodeValue) { // in this case, the new node will be inserted at the beginning
			newNode->nextNodeAddress = *head; // set new node's next address to the current head
			newNode->nextNodeAddress->prevNodeAddress = newNode; // set the new node's next node's previous address to the new node
			*head = newNode; // set head address to the new node's
		}
		else {
			currentNode = *head; // set current node to head

			while (currentNode->nextNodeAddress != NULL && currentNode->nextNodeAddress->nodeValue < newNode->nodeValue) { // traverse through the list while next isn't null and next's data is less than new node's data
				currentNode = currentNode->nextNodeAddress; // set current node to next node's address
			}

			newNode->nextNodeAddress = currentNode->nextNodeAddress; // set new node's next address to be equal to the current node's next address
			if (currentNode->nextNodeAddress != NULL) { // check to make sure this isn't being inserted at the end of the list
				newNode->nextNodeAddress->prevNodeAddress = newNode; // if it's not at the end of the list, next node's previous address should be set to the new node's address
			}

			currentNode->nextNodeAddress = newNode; // set the current node's next to the new node's address
			newNode->prevNodeAddress = currentNode; // and finally, set the new node's previous address to the current node
		}
	}

	void PrivatePrintBubbleSortedList(struct Node** head) { // accepts head node pointer
		struct Node* currentNode;

		if (*head == NULL) {
			cout << endl << "EMPTY LIST!" << endl;
			return;
		}

		// create a copy of the list prior to sorting
		DLL sorted;
		currentNode = *head;
		while (currentNode != NULL) {
			sorted.AppendAfterTail(currentNode->nodeValue); // add values one at a time to the new list
			currentNode = currentNode->nextNodeAddress;
		}

		int length = sorted.getLength(); // get list length first
		struct Node** sortedHead;
		int outer, inner;
		bool wasSwapped;

		pa.start(); // start performance analyzer

		for (outer = 0; outer <= length; outer++) { // loop for the number of iterations equal to the list length
			sortedHead = &(sorted.head); // get sorted's head and define sortedHead with it
			wasSwapped = false; // initialize this bool to false

			for (inner = 0; inner < length - outer - 1; inner++) { // loop until inner counter reaches value of list length, minus outer counter, minus 1
				struct Node* first = *sortedHead; // first should be the head
				struct Node* second = first->nextNodeAddress; // second is first's next

				if (first->nodeValue > second->nodeValue) { // compare node values here
					struct Node* temp = second->nextNodeAddress; // create a placeholder
					second->nextNodeAddress = first; // second node's next address points to first
					first->nextNodeAddress = temp; // first node's next addresss points to the temp node (second node's original next address)
					*sortedHead = second; // set new head
					wasSwapped = true; // flag bool to true, indicating a swap has taken place
				}
				sortedHead = &(*sortedHead)->nextNodeAddress; // step to the next address
			}

			if (!wasSwapped) // if there was no swap up to this point, exit the loop
				break;
		}

		pa.end(); // stop performance analyzer

		bool print;

		// after we've populated the new sorted list, if it's over 100 entries in length, give the user the option to print it to the console
		if (length > 100) {
			cout << "\nThe list contains " << length << " entries... Want to print it?\n1. yes\n2. no\n\n";
			print = getNumberFromUser("YOUR CHOICE") == 1 ? true : false;
		}
		else {
			print = true; // if the list length is not greater than 100, print it by default
		}
		if (print) sorted.PrintListForward();
	}

public:
	DLL() {
		head = NULL;
	};

	void InsertBeforeHead(type x) { // insert new node before head
		struct Node* newNode = GetNewNode(x);
		if (head == NULL) { // (check if we're trying to add to an empty list)
			head = newNode; // if so, this node we are trying to insert shall be the head node
			return; // exit the function, as this is the only node in the list
		}
		head->prevNodeAddress = newNode; // overwriting head's null pointer in prev field to the node we're inserting in front of it
		newNode->nextNodeAddress = head; // pointing newNode's next field to the address of old/current head node
		head = newNode; // setting the new head address to that of the new node we just created
	}

	void AppendAfterTail(type x) { // insert new node after tail
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

	void PrintInsertionSortedList() {
		DLL sorted; // instantiate new DLL object
		struct Node* temp = head;

		pa.start(); // start performance analyzer

		while (temp != NULL) {
			sortedInsert(&(sorted.head), GetNewNode(temp->nodeValue)); // dereference sorted's head node and pass it to sortedInsert, along with a new node created from temp node's value
			temp = temp->nextNodeAddress; // jump to next node
		}

		pa.end(); // stop performance analyzer

		int length = sorted.getLength();
		bool print;

		// after we've populated the new sorted list, if it's over 100 entries in length, give the user the option to print it to the console
		if (length > 100) {
			cout << "\nThe list contains " << length << " entries... Want to print it?\n1. yes\n2. no\n\n";
			print = getNumberFromUser("YOUR CHOICE") == 1 ? true : false;
		}
		else {
			print = true; // if the list length is not greater than 100, print it by default
		}
		if (print) sorted.PrintListForward();
	}

	void PrintBubbleSortedList() {
		PrivatePrintBubbleSortedList(&head);
	}

	void deleteList() {
		if (head != NULL) privateDeleteList(&head);
	}

	Node* Find(type valueToFind) { // returns a pointer to the first node in the list whose key matches specified value
		struct Node* temp = head;
		while (temp != NULL) { // step through list until temp is null
			if (valueToFind == temp->nodeValue) { // match found! return it
				return temp;
			}
			temp = temp->nextNodeAddress; // set temp to next node
		}
		return NULL; // if we get to this point, the specified key was not found, so we can return NULL
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

	void populateListFromVector(vector<type> values) {
		head = NULL; // reset head to null to start new empty list
		int length = values.size();
		cout << endl << "Adding " << length << " nodes from vector to the list.\n";

		// if vector has over 100 values, give the user the option of whether or not to print individual lines to the console on each addition
		bool print;
		if (length > 100) {
			cout << "\nThe input vector contains " << length << " values... Want to print each added value to the console?\n1. yes\n2. no\n\n";
			print = getNumberFromUser("YOUR CHOICE") == 1 ? true : false;
		}
		else {
			print = true; // if the input vector does not contain more than 100 values, print each line by default
		}

		for (int i = 0; i < values.size(); i++) {
			int value = values[i];
			if (print) cout << "\nAdding a node with value " << value << " to the list.\n";
			AppendAfterTail(value); //  on each loop iteration to add to the list
		}
	}
};