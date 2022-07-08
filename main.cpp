#include <fstream>
#include <iostream>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <string>
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

std::string getStringFromUser(string message) { // function to get input from user
	cout << endl << endl << message + ": ";
	string entry;
	cin >> entry;
	cout << endl;
	return entry;
}

bool generateRandomVector(vector<int> &values, int length) {

	if (length < 1) { // check for 0 or negative cases
		cout << endl << "Cannot add " << length << " nodes to the list. Number of nodes must be greater than 0.\n";
		return false; // return false if zero or negative items
	}
	else {
		// clear vector
		values.clear();

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

	return true;
}

bool generateVectorFromFile(vector<int> &values, string filename) { // pass pointer to save data vector into this function
	ifstream in(filename);
	int value;
	int line = 0; // to track line number for exception handling
	if (!in) { // CHECK IF FILE OBJECT IS VALID
		cout << endl << "**********CANNOT OPEN FILE**********" << endl << endl;
		return false; // return false if file cannot be opened, as it is invalid
	}

	values.clear(); // clear the vector

	string str;
	while (getline(in, str)) { // read next line from file until end is reached
		line++; // increment line number by 1 at the beginning of the loop
		try { // handle exception if unable to convert value to integer (in the case of string or other non-integer value). if exception occurs, simply move on to the next line.
			value = stoi(str); // convert string to integer
			values.push_back(value); // writes line to the vector<int>
		}
		catch (exception& err) {
			cout << endl << "VALUE OF '" << str << "' ON LINE #" << line << " OF " << filename << " IS NOT AN INTEGER!!!\n(skipping this line...)\n";
		}
	}
	in.close(); // close file

	return true; // return true if values were successfully added to the vector
}

void intro() {
	cout << "Welcome to DOUBLY LINKED LISTS!" << endl <<
		"This application allows you to create doubly linked lists either from randomly-sorted integers from 1 to" << endl <<
		"your desired MAX_NUMBER, or from a data file containing one integer per line. Various functions can be" << endl <<
		"performed on the linked list, including insertion, deletion, node memory address retrieval, and sorting" << endl <<
		"using either insertion-sort or bubble-sort algorithms. Sorting operations are timed for performance" << endl <<
		"analysis purposes, and results are displayed in the console output. LET'S GET STARTED!" << endl << endl;
}

int main() {
	intro();
	DLL<int> list; // instantiate doubly linked list object (head is set to null during construction)
	vector<int> values; // declare vector

    for (;;) { // main loop
        cout << "\nWhat would you like to do?" << endl <<
			"1. Create new linked list with specified number of integers" << endl <<
			"2. Create new linked list with values from file" << endl <<
			"3. Print list FORWARD" << endl <<
			"4. Print list in REVERSE" << endl <<
			"5. Insert new node before head" << endl <<
			"6. Append new node to end of list" << endl <<
			"7. Get memory address of node with specified value (FIND)" << endl <<
			"8. Get minimum and maximum values in the list" << endl <<
			"9. Delete a node of specified index" << endl <<
			"10. Print Insertion-Sorted List *" << endl <<
			"11. Print Bubble-Sorted List *" << endl <<
			"12. Reset entire list to empty" << endl <<
			"0. EXIT" << endl << endl <<
			"(* indicates operations with timed performance analysis)" << endl << endl;
		int choice = getNumberFromUser("ENTER A CHOICE");
        switch (choice) {
        case 1: // create new list with n items
			if (generateRandomVector(values, getNumberFromUser("ENTER DESIRED NUMBER OF NODES TO ADD TO THE LIST"))) {
				list.deleteList(); // reset list
				list.populateListFromVector(values); // add nodes to list
			}
			else {
				cout << endl << "NOTHING WAS ADDED TO THE LIST!!!" << endl;
			}
			continue;
        case 2: // create new list with values from file
			if (generateVectorFromFile(values, getStringFromUser("ENTER FILENAME"))) {
				list.deleteList(); // reset list
				list.populateListFromVector(values);
			}
			else {
				cout << endl << "NOTHING WAS ADDED TO THE LIST!!!" << endl;
			}
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
		case 10: // print selection sorted list
			list.PrintInsertionSortedList();
			continue;
		case 11: // print bubble sorted list
			list.PrintBubbleSortedList();
			continue;
		case 12: // reset list to empty
			list.deleteList();
	;
			continue;
        case 0: // exit
            cout << "\n\nBYE!!!\n\n";
            break; // exit loop
        }
        break; // exit program
    }
}