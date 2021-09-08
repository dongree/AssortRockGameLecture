#include <iostream>
#include <conio.h>

using namespace std;

/*
0 : º®
1 : ±æ
2 : ½ÃÀÛÁ¡
3 : µµÂøÁ¡
4 : ÆøÅº
*/

struct tagPoint {
	int x;
	int y;
};

typedef tagPoint POINT;
typedef tagPoint* PPOINT;

void setMaze(char maze[21][21], PPOINT playerPos, PPOINT startPos, PPOINT endPos) {
	startPos->x = 0;
	startPos->y = 0;

	endPos->x = 19;
	endPos->y = 19;

	*playerPos = *startPos;

	strcpy_s(maze[0],  "21100000000000000000");
	strcpy_s(maze[1],  "00111111111100000000");
	strcpy_s(maze[2],  "00100010000111111000");
	strcpy_s(maze[3],  "00100010000000001000");
	strcpy_s(maze[4],  "00100011110001111000");
	strcpy_s(maze[5],  "00100000001111000000");
	strcpy_s(maze[6],  "01111100001000000000");
	strcpy_s(maze[7],  "00010000001000000000");
	strcpy_s(maze[8],  "00010000001111110000");
	strcpy_s(maze[9],  "00011110000000010000");
	strcpy_s(maze[10], "00000011110000010000");
	strcpy_s(maze[11], "00000010000000010000");
	strcpy_s(maze[12], "00000010011111111100");
	strcpy_s(maze[13], "00000010010000000100");
	strcpy_s(maze[14], "00011111010000000100");
	strcpy_s(maze[15], "00010000010000000111");
	strcpy_s(maze[16], "00010011110000000000");
	strcpy_s(maze[17], "00010000010000011111");
	strcpy_s(maze[18], "01110000010000010001");
	strcpy_s(maze[19], "01000000011111111103");
	
}

void outputMaze(char maze[21][21], PPOINT playerPos) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (maze[i][j] == '4')
				cout << "¢Í";
			else if (playerPos->x == j && playerPos->y == i)
				cout << "¡Ù";
			else if (maze[i][j] == '0')
				cout << "¡á";
			else if (maze[i][j] == '1')
				cout << "  ";
			else if (maze[i][j] == '2')
				cout << "¡Ú";
			else if (maze[i][j] == '3')
				cout << "¡Ý";
		}
		cout << endl;
	}
}

void moveUp(char maze[21][21], PPOINT playerPos) {
	if (playerPos->y - 1 >= 0) {
		if (maze[playerPos->y - 1][playerPos->x] != '0' &&
			maze[playerPos->y - 1][playerPos->x] != '4') {
			playerPos->y--;
		}
	}
}

void moveDown(char maze[21][21], PPOINT playerPos) {
	if (playerPos->y + 1 < 20) {
		if (maze[playerPos->y + 1][playerPos->x] != '0' &&
			maze[playerPos->y + 1][playerPos->x] != '4') {
			playerPos->y++;
		}
	}
}

void moveLeft(char maze[21][21], PPOINT playerPos) {
	if (playerPos->x - 1 >= 0) {
		if (maze[playerPos->y][playerPos->x - 1] != '0' &&
			maze[playerPos->y][playerPos->x - 1] != '4') {
			playerPos->x--;
		}
	}
}

void moveRight(char maze[21][21], PPOINT playerPos) {
	if (playerPos->x + 1 < 20) {
		if (maze[playerPos->y][playerPos->x + 1] != '0' &&
			maze[playerPos->y][playerPos->x + 1] != '4') {
			playerPos->x++;
		}
	}
}

void movePlayer(char maze[21][21], PPOINT playerPos, char input) {
	switch (input) {
	case 'w':
	case 'W':
		moveUp(maze, playerPos);
		break;
	case 's':
	case 'S':
		moveDown(maze, playerPos);
		break;
	case 'a':
	case 'A':
		moveLeft(maze, playerPos);
		break;
	case 'd':
	case 'D':
		moveRight(maze, playerPos);
		break;
	}
}

void createBomb(char maze[21][21], const PPOINT playerPos, PPOINT bombArr, int* bombCount) {
	if (*bombCount == 5)
		return;

	for (int i = 0; i < *bombCount; i++) {
		if (playerPos->x == bombArr[i].x &&
			playerPos->y == bombArr[i].y)
			return;
	}

	bombArr[*bombCount] = *playerPos;
	(*bombCount)++;

	maze[playerPos->y][playerPos->x] = '4';
}

void fire(char maze[21][21], PPOINT playerPos, PPOINT bombArr, int* bombCount) {
	for (int i = 0; i < *bombCount; i++) {
		maze[bombArr[i].y][bombArr[i].x] = '1';

		if (playerPos->x == bombArr[i].x && playerPos->y == bombArr[i].y) {
			playerPos->x = 0;
			playerPos->y = 0;
		}

		if (bombArr[i].y - 1 >= 0) {
			if (maze[bombArr[i].y - 1][bombArr[i].x] == '0') {
				maze[bombArr[i].y - 1][bombArr[i].x] = '1';
			}
			if (playerPos->x == bombArr[i].x && playerPos->y == bombArr[i].y-1) {
				playerPos->x = 0;
				playerPos->y = 0;
			}
		}
		
		if (bombArr[i].y + 1 < 20) {
			if (maze[bombArr[i].y + 1][bombArr[i].x] == '0') {
				maze[bombArr[i].y + 1][bombArr[i].x] = '1';
			}
			if (playerPos->x == bombArr[i].x && playerPos->y == bombArr[i].y+1) {
				playerPos->x = 0;
				playerPos->y = 0;
			}
		}

		if (bombArr[i].x - 1 >= 0) {
			if (maze[bombArr[i].y][bombArr[i].x - 1] == '0') {
				maze[bombArr[i].y][bombArr[i].x - 1] = '1';
			}
			if (playerPos->x == bombArr[i].x-1 && playerPos->y == bombArr[i].y) {
				playerPos->x = 0;
				playerPos->y = 0;
			}
		}

		if (bombArr[i].x + 1 < 20) {
			if (maze[bombArr[i].y][bombArr[i].x + 1] == '0') {
				maze[bombArr[i].y][bombArr[i].x + 1] = '1';
			}
			if (playerPos->x == bombArr[i].x+1 && playerPos->y == bombArr[i].y) {
				playerPos->x = 0;
				playerPos->y = 0;
			}
		}
		
	}


	*bombCount = 0;
}

int main() {

	// 20 x 20 ¹Ì·Î¸¦ ¸¸µé¾îÁØ´Ù.
	char maze[21][21];

	POINT playerPos;
	POINT startPos;
	POINT endPos;

	int bombCount = 0;

	POINT bombPos[5];

	setMaze(maze, &playerPos, &startPos, &endPos);
	while (true) {
		system("cls");
		outputMaze(maze, &playerPos);
		if (playerPos.x == endPos.x && playerPos.y == endPos.y) {
			cout << "µµÂøÇß½À´Ï´Ù" << endl;
			break;
		}
		cout << "| t : ÆøÅº¼³Ä¡ | u : ÆøÅº ÅÍÆ®¸®±â |" << endl;
		cout << "| w : À§ | s : ¾Æ·¡ | a : ¿ÞÂÊ | d : ¿À¸¥ÂÊ | q : Á¾·á | : ";
		char input = _getch();
		if (input == 'q' || input == 'Q')
			break;
		else if (input == 't' || input == 'T')
			createBomb(maze, &playerPos, bombPos, &bombCount);
		else if (input == 'u' || input == 'U')
			fire(maze, &playerPos, bombPos, &bombCount);

		movePlayer(maze, &playerPos, input);
		
	}
	return 0;
}