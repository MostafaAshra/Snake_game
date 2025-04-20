#include <iostream>
#include <conio.h> // consol input output library 
#include <Windows.h>
using namespace std;


int width, height;
int foodx, foody;
int headx, heady, tailN;
int tailx[50], taily[50];
int score;
bool gameover;
enum direction { top = 1, down, Right, Left };
direction dir;

void shiftright(int arr[], int size) {
	for (int i = size - 2;i >= 0;i--)
		arr[i + 1] = arr[i];
}
void setup() {
	width = 40;
	height = 20;
	foodx = (rand() % (width - 2)) + 1; // 1 to 38
	foody = (rand() % (height - 2)) + 1; // 1 to 38
	headx = width / 2;
	heady = height / 2;
	tailN = 0;
	score = 0;
	gameover = false;
}
void draw() {
	system("cls"); // clear screen to avoid drawing infinity loop for the board
	for (int i = 0;i < height;i++) {
		for (int j = 0;j < width;j++) {
			if (i == 0 || i == height - 1) //draw the width line in the first line and the last line
				cout << "*";
			else if (j == 0 || j == width - 1)
				cout << "*";
			else if (i == heady && j == headx)
				cout << "O";
			else if (i == foody && j == foodx)
				cout << "$";
			else {
				bool printed = false;
				for (int z = 0;z < tailN;z++) {
					if (tailx[z] == j && taily[z] == i) {
						cout << "o";
						printed = true;
						break;
					}
				}
				if (!printed) {
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	cout << "player score: " << score << endl;
}
void Input() {
	if (_kbhit()) {
		char c = _getch();
		switch (c)
		{
		case 'w': dir = top;
			break;
		case 's': dir = down;
			break;
		case 'd': dir = Right;
			break;
		case 'a': dir = Left;
			break;
		case 'x': exit(0);

		}
	}


}
void move() {
	shiftright(tailx, 50);
	shiftright(taily, 50);
	tailx[0] = headx;
	taily[0] = heady;
	switch (dir)
	{
	case top: heady--;
		break;
	case down: heady++;
		break;
	case Right: headx++;
		break;
	case Left: headx--;
		break;
	}
	if (heady <= 0 || heady >= height || headx <= 0 || headx >= width) {
		gameover = true;
		cout << "game over";
	}
	if (headx == foodx && heady == foody) {
		score++;
		foodx = (rand() % (width - 2)) + 1; // 1 to 38
		foody = (rand() % (height - 2)) + 1; // 1 to 38
		tailN++;
	}
	
}

int main() {
	setup();
	while (!gameover)
	{
		draw();
		Input();
		move();
		Sleep(50);  //from windows.h library to slow the motion
	}
}