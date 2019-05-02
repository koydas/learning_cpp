#include "main.h"
#include <conio.h>
#include <iostream>
#include <future>
#include <chrono>
#include <string>

bool quit = false;

const int paddleStartX = 6;
int paddleX = paddleStartX;
int paddleWidth = 3;

int GetLineFromCin() {

	return _getch();
}
auto future = std::async(std::launch::async, GetLineFromCin);

int main() {
	

	while (!quit) {
		update();
		draw();
	}

	return 0;
}

void update() {
	if (future.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
		int i = future.get();

		future = std::async(std::launch::async, GetLineFromCin);

		switch (i) {
			case 27: // Escape
				quit = true;
				break;
			case 224 : // Left Arrow
				if (paddleX > 1)
					paddleX--;
				break;
			case 77 :
				if (paddleX < 14)
					paddleX++;
				break;

		}
	}

}

void draw() {
	system("cls");

	std::cout << "##############" << std::endl;
	std::cout << "#            #" << std::endl;
	std::cout << "#            #" << std::endl;
	std::cout << "#            #" << std::endl;
	std::cout << "#            #" << std::endl;
	
	std::string left = "";
	std::string right = "";

	int rightSpace = 14 - paddleX - paddleWidth;
	for (int i = 1; i < paddleX; i++) {
		left += " ";
	}

	for (int i = 1; i < rightSpace; i++) {
		right += " ";
	}

	std::cout << "#" << left << "---" << right << "#" << std::endl;
	
	
	//std::cout << "#     ---    #" << std::endl;



	std::cout << "##############" << std::endl;
}