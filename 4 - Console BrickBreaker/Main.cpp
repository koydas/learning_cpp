#include "main.h"
#include <conio.h>
using namespace std;
#include <iostream>
#include <string>

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
{wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall, wall },
};

bool quit = false;

const int paddleStartX = 6;
int paddleX = paddleStartX;
int paddleWidth = 3;

const int ballStartX = 7;
const int ballStartY = 7;

int ballX = ballStartX;

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

	updatePaddlePosition();
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
		}
	}
}

void updatePaddlePosition() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (tilemap[i][j] == paddle) {
				tilemap[i][j] = none;
			}
		}
	}

	tilemap[5][paddleX] = paddle;
	tilemap[5][paddleX + 1] = paddle;
	tilemap[5][paddleX + 2] = paddle;
}