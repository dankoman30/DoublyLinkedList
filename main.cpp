#include <iostream>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

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

vector<int> generateVector(int length) {
	vector<int> values; // declare vector

	if (length < 1) { // check for 0 or negative cases
		cout << endl << "Cannot add " << length << " nodes to the list. Number of nodes must be greater than 0.\n";
	}
	else {
		// add items to the vector
		cout << endl << "Creating a vector containing values 1 to " << length;
		for (int i = 0; i < length; i++) {
			values.push_back(i + 1); // add numbers 1 through nodes to the vector
		}

		// shuffle the vector
		cout << " and shuffling it in random order." << endl;
		auto rng = std::default_random_engine{};
		std::shuffle(std::begin(values), std::end(values), rng);
	}

	return values;
}

int main() {
	DLL<int> list; // instantiate doubly linked list object (head is set to null during construction)

    for (;;) { // main loop
        cout << "\nWhat would you like to do?" << endl <<
			"1. Create new linked list with specified number of integers" << endl <<
			"2. Reset entire list to empty" << endl <<
			"3. Print list FORWARD" << endl <<
			"4. Print list in REVERSE" << endl <<
			"5. Insert new node before head" << endl <<
			"6. Append new node to end of list" << endl <<
			"7. Get memory address of node with specified value (FIND)" << endl <<
			"8. Get minimum and maximum values in the list" << endl <<
			"9. Delete a node of specified index" << endl <<
			"10. Print Insertion-Sorted List" << endl <<
			"0. EXIT\n\n";
		int choice = getNumberFromUser("ENTER A CHOICE");
        switch (choice) {
        case 1: // create new with n items
			list.populateListFromVector(generateVector(getNumberFromUser("ENTER DESIRED NUMBER OF NODES TO ADD TO THE LIST"))); // add nodes to list
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
		case 10:
			list.PrintInsertionSortedList();
			continue;
        case 0: // exit
            cout << "\n\nBYE!!!\n\n";
            break; // exit loop
        }
        break; // exit program
    }
}