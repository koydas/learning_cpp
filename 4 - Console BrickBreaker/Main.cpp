#include "main.h"
#include <conio.h>
using namespace std;
#include <iostream>
#include <string>
#include <windows.h>

const int width = 14;
const int height = 7;

enum tileType { wall, brick, ball, paddle, none };

tileType tilemap[height][width] = {
	{wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall },
	{wall, brick,brick,brick,brick,brick,brick,brick,brick,brick,brick,brick,brick, wall},
	{wall, brick,brick,brick,brick,brick,brick,brick,brick,brick,brick,brick,brick, wall},
	{wall, none, none, none, none, none, none, none, none, none, none, none, none, wall},
	{wall, none, none, none, none, none, none, none, none, none, none, none, none, wall},
	{wall, none, none, none, none, none, none, none, none, none, none, none, none, wall},
	{wall, none, none, none, none, none, none, none, none, none, none, none, none, wall}
};

bool quit = false;

const int paddleStartX = 6;
int paddleX = paddleStartX;
int paddleWidth = 3;

bool ballFreezed = true;
int ballX;
int ballY;
float ballVelocityX = 0;
float ballVelocityY = 0;

int score = 0;

int main() {
	while (!quit) {
		update();
		draw();
	}

	return 0;
}

void update() {
	input();

	clearMovingElements();
	updatePaddlePosition();
	updateBallPosition();

	Sleep(500);
}

void draw() {
	system("cls");

	std::cout << "Score : "<< score << std::endl;
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			string s;
			switch (tilemap[i][j])
			{
				case wall:
					s = "#";
					break;
				case brick:
					s = "=";
					break;
				case paddle:
					s = "-";
					break;
				case ball:
					s = "O";
					break;
				case none:
					s = " ";
					break;
				default:
					s = "";
			}

			cout << s;
		}

		cout << endl;
	}
}

void input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 27: // Escape
			quit = true;
			break;
		case 'z': // Left Arrow
			if (paddleX > 1)
				paddleX--;
			break;
		case 'x': // Right Arrow
			if (paddleX+4 < width)
				paddleX++;
			break;
		case ' ':
			if (ballFreezed) {
				ballVelocityX = -1;
				ballVelocityY = -1;

				ballFreezed = false;
			}
			break;
		}
	}
}

void clearMovingElements() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (tilemap[i][j] == paddle || tilemap[i][j] == ball) {
				tilemap[i][j] = none;
			}
		}
	}
}

void updatePaddlePosition() {
	tilemap[6][paddleX] = paddle;
	tilemap[6][paddleX + 1] = paddle;
	tilemap[6][paddleX + 2] = paddle;
}

void updateBallPosition() {
	if (ballFreezed) {
		ballX = paddleX + 1;
		ballY = 5;
	}
	else {
		ballX += ballVelocityX;
		ballY += ballVelocityY;
	}

	if (tilemap[ballY][ballX] == none) {
		tilemap[ballY][ballX] = ball;
	}
	else {
		ballVelocityX *= -1;
		ballVelocityY *= -1;
	}

	
}