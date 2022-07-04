#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "DLL.h"

using namespace std;

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

int main() {
	DLL list; // instantiate doubly linked list object (head is set to null during construction

    for (;;) { // main loop
        cout << "\nWhat would you like to do?\n1. Create new linked list of integers 1 through 10\n2. Reset entire list to empty\n3. Print list FORWARD\n4. Print list in REVERSE\n5. Insert new node before head\n6. Append new node to end of list\n7. Get memory address of node with specified value (FIND)\n8. Get minimum and maximum values in the list\n9. Delete a node of specified index\n0. EXIT\n\n";
		int choice = getNumberFromUser("ENTER A CHOICE");
        switch (choice) {
        case 1: // create new list 1-10
			list.populateList1to10();
            continue;
        case 2: // reset list to empty (nullify head)
			list.nullifyHead();
            continue;
        case 3: // print list forward
			list.PrintListForward();
            continue;
        case 4: // print list reverse
			list.PrintListReverse();
			continue;
        case 5: // insert new node before head
			list.InsertBeforeHead(getNumberFromUser("ENTER NEW VALUE TO INSERT AT THE BEGINNING OF THE LIST"));
			continue;
        case 6: // append new node after tail
			list.AppendAfterTail(getNumberFromUser("ENTER NEW VALUE TO APPEND TO THE END OF THE LIST"));
			continue;
		case 7: // find memory address of specified value
			choice = getNumberFromUser("ENTER A VALUE TO FIND IN THE LIST");
			cout << endl << "Memory address of first list entry matching " << choice << " is " << list.Find(choice) << endl;
			continue;
		case 8: // get minimum and maximum values (keys)
			list.getMinMax();
			continue;
		case 9: // delete a node of specified index
			list.deleteNode();
			continue;
        case 0: // exit
            cout << "\n\nBYE!!!\n\n";
            break; // exit loop
        }
        break; // exit program
    }
}