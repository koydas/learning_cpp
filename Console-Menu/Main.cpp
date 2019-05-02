#include <iostream>
#include <string>

#include "Main.h"

using namespace std;

const string choice1 = "First";
const string choice2 = "Second";
const string choice3 = "Third";

int main() {
	string choice = "";
	while (choice != "0")
	{
		string choiceString = "";

		displayMenu();

		cin >> choice;

		bool valid = setChoiceString(choice, choiceString);

		displayResult(valid, choiceString);
	}

	return 0;
}

void displayMenu() {
	cout << " ==--== Menu ==--==" << endl;
	cout << "1. " << choice1 << endl;
	cout << "2. " << choice2 << endl;
	cout << "3. " << choice3 << endl;
	cout << "0. Quit" << endl;
}

void displayResult(bool valid, string choiceString) {
	if (valid) {
		cout << "You choose : " << choiceString << endl;
	}
	else {
		cout << choiceString << endl;
	}
}

int getNumericValue(string choice) {
	int i;

	try {
		i = std::stoi(choice);
	}
	catch (const std::exception & e) {
		i = -1;
	}

	return i;
}

bool setChoiceString(string choice, string &choiceString) {
	bool valid = true;

	int i = getNumericValue(choice);
	
	switch (i) {
		case 1:
			choiceString = choice1;
			break;
		case 2:
			choiceString = choice2;
			break;
		case 3:
			choiceString = choice3;
			break;

		default:
			choiceString = "Invalid choice";
			valid = false;
			break;
	}

	return valid;
}