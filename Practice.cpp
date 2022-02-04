#include <iostream>
#include <conio.h>
#include<cstdlib>
#include<ctime>
#include <Windows.h>
#include <vector>
using namespace std;

int width = 28, height = 15, fX, fY, score = 0, k = NULL;
bool End = false, fruit = false, Tail = false;

vector <vector<int>> snakePos = { {3, 7} };

void Logic()
{
	if (snakePos[0][0] == width + 1 || snakePos[0][0] == 0 || snakePos[0][1] == height + 1 || snakePos[0][1] == 0 ) {
		End = true;
	}
	for (auto iter = 1; iter < snakePos.size(); ++iter)
	{
		if (snakePos[0] == snakePos[iter])
		{
			End = true;
		}
	}
	if (fX + 1 == snakePos[0][0] && fY + 1  == snakePos[0][1]) {
		Tail = true;
		fruit = false;
		score++;
	}
	if (Tail == true)
	{
		snakePos.insert(snakePos.begin() + 1, 1, snakePos[0]);
		while (snakePos.size() > score + 1)
		{
			snakePos.pop_back();
		}
	}

	if (!fruit) {
		srand(time(0) + rand());
		fX = (rand() % 27) + 1;
		fY = (rand() % 14) + 1;
		fruit = true;
	}
}

void GameControls()
{
	Sleep(200);
	if (k == NULL) {
		k = _getch();
	}
	if (_kbhit()) {
		k = _getch();
	}
		switch (k)
		{
		case 119: // w
			snakePos[0][1]--;
			break;
		case 115: // a
			snakePos[0][1]++;
			break;
		case 97: // s
			snakePos[0][0]--;
			break;
		case 100: // d
			snakePos[0][0]++;
			break;
		case 27: // esc
			End = true;
			break;
		default:
			cout << "use WASD to move, ESC to exit";
			break;
		}
		
}
	
void Draw()
{
	system("CLS");
	for (int i = 0; i < width + 1; i++) {
		cout << "-";
	}
	cout << "\n";
	for (int i = 0; i < height; i++) {
		cout << "|";
		for (int j = 1; j < width; j++) 
		{
			bool flag = false;
			for (auto iter = 0; iter < snakePos.size(); ++iter) 
			{
				if (j + 1 == snakePos[iter][0] && i + 1 == snakePos[iter][1])
				{
					if (iter == 0) 
					{
						cout << "@";
						flag = true;
					}
					else
					{
						cout << "#";
						flag = true;
					}
				}
			}
			if (j == fX && i == fY)
			{
				cout << "%";
				continue;
			}
			if (flag == true)
			{
				continue;
			}
			cout << " ";
		}
		cout << "|\n";
	}
	for (int i = 0; i < width + 1; i++) {
		cout << "-";
	}
	cout << "\nScore: " << score << endl;
}

int main() {
	cout << "use WASD to move, ESC to exit" << endl;
	do {
		Logic();
		GameControls();
		Draw();
	} while (!End);
	cout << "\nGame Over!";
	return 0;
}