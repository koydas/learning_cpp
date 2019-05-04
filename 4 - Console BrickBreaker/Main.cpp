#include "main.h"
#include <conio.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <future>

using namespace std;

const int width = 14;
const int height = 7;

enum tileType { wall, brick, ball, paddle, none, dead };

tileType tilemap[height+1][width] = {
	{wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall },
	{wall, brick,brick,brick,brick,brick,brick,brick,brick,brick,brick,brick,brick, wall},
	{wall, none, none, none, none, none, none, none, none, none, none, none, none, wall},
	{wall, none, none, none, none, none, none, none, none, none, none, none, none, wall},
	{wall, none, none, none, none, none, none, none, none, none, none, none, none, wall},
	{wall, none, none, none, none, none, none, none, none, none, none, none, none, wall},
	{wall, none, none, none, none, none, none, none, none, none, none, none, none, wall},
	{dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead, dead},
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
int balls = 3;

int main() {
	future<void> f = async(updateBallPosition);

	while (!quit) {
		if (balls <= 0) {
			quit = true;
		}

		if (ballFreezed) {
			ballX = paddleX + 1;
			ballY = 5;
		}

		input();
		clearMovingElements();
		updatePaddlePosition();

		tilemap[ballY][ballX] = ball;

		draw();
	}

	return 0;
}

void draw() {
	system("cls");

	std::cout << "Score : "<< score << std::endl;
	std::cout << "Balls : "<< balls << std::endl;
	
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
				if (paddleX + 4 < width)
					paddleX++;
				break;
			case ' ':
				if (ballFreezed) {
					ballVelocityX = 1;
					ballVelocityY = -1;

					ballFreezed = false;
				}
				break;
			}
		}
	}


void clearMovingElements() {
	tilemap[ballY][ballX] = none;
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
	while (!quit) {
		int expectedY = ballY + ballVelocityY;
		int expectedX = ballX + ballVelocityX;

		if (tilemap[expectedY][ballX] == dead) {
			ballFreezed = true;
			balls--;
		}

		if (tilemap[expectedY][ballX] != none) {
			ballVelocityY *= -1;
		}
		if (tilemap[ballY][expectedX] != none) {
			ballVelocityX *= -1;
		}

		if (tilemap[expectedY][expectedX] == brick) {
			score += 100;
			tilemap[expectedY][expectedX] = none;
		}

		
		if(!ballFreezed) {
			ballX += ballVelocityX;
			ballY += ballVelocityY;
		}

		Sleep(1000);
	}
}