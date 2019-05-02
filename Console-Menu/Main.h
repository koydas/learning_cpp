#include <iostream>
#include <string>

#pragma once

void displayMenu();
void displayResult(bool valid, std::string choiceString);
int getNumericValue(std::string choice);
bool setChoiceString(std::string choice, std::string &choiceString);