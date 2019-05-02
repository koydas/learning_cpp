#include <iostream>
#include <string>
#include <compare>

using namespace std;

int number = rand() % 100 + 1;

int main() {
	bool quit = false;
	while (!quit) {
		string input;
		cout << "You can press q to quit." << endl;
		cout << "Try to guess a number between 1 and 100." << endl;
		cin >> input;

		if (input == "q" || input == "Q") {
			break;
		}

		bool invalid = false;
		int guessedNumber;
		try {
			guessedNumber = std::stoi(input);
		}
		catch (const std::exception & e) {
			invalid = true;
		}
		
		if (invalid || (guessedNumber < 0 || guessedNumber > 100)) {
			cout << "Invalid number." << endl;
		}
		else {
			if (guessedNumber < number) {
				cout << "Wrong! The number is higher." << endl;
			}
			else if(guessedNumber > number) {
				cout << "Wrong! The number is lower." << endl;
			}
			else {
				system("cls");
				cout << "You got it." << endl;
				break;
			}
		}
	}

	return 0;
}