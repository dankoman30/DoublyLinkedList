#pragma once

using namespace std;

class DLL {
private:
	struct Node {
		int nodeValue;
		struct Node* nextNodeAddress;
		struct Node* prevNodeAddress;
	};
	struct Node* head; // pointer to head node
	struct Node* GetNewNode(int x); // function to get new node (to be used in InsertBeforeHead and InsertAtTail functions
	int getMinimumKey(); // returns minimum key in the list
	int getMaximumKey(); // returns maximum key in the list
	void deleteThisNode(int index);
	int getNumberFromUser(string message); // function to get input from user

public:
	DLL();
	void InsertBeforeHead(int x); // insert new node before head
	void AppendAfterTail(int x); // insert new node after tail
	void PrintListForward();
	void PrintListReverse();
	void populateList1to10();
	void nullifyHead();
	Node* Find(int valueToFind);
	void getMinMax();
	void deleteNode();
};