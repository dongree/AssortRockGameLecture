#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;

/*
0 : ��
1 : ��
2 : ������
3 : ������
4 : ��ź
5 : �Ŀ�������
6 : ���б� ������
7 : ���������
*/

struct tagPoint {
	int x;
	int y;
};

typedef tagPoint POINT;
typedef tagPoint* PPOINT;

typedef struct Player {
	tagPoint pos;
	bool wallPush;
	bool pushOnOff;
	bool transparency;
	int bombPower;
}PLAYER, *PPLAYER;

void setMaze(char maze[21][21], PPLAYER player, PPOINT startPos, PPOINT endPos) {
	startPos->x = 0;
	startPos->y = 0;

	endPos->x = 19;
	endPos->y = 19;

	player->pos = *startPos;

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

void outputMaze(char maze[21][21], PPLAYER player) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (maze[i][j] == '4')
				cout << "��";
			else if (player->pos.x == j && player->pos.y == i)
				cout << "��";
			else if (maze[i][j] == '0')
				cout << "��";
			else if (maze[i][j] == '1')
				cout << "  ";
			else if (maze[i][j] == '2')
				cout << "��";
			else if (maze[i][j] == '3')
				cout << "��";
			else if (maze[i][j] == '5')
				cout << "��";
			else if (maze[i][j] == '6')
				cout << "��";
			else if (maze[i][j] == '7')
				cout << "��";
		}
		cout << endl;
	}
	
	cout << "��ź�Ŀ� : " << player->bombPower << endl;
	cout << "����� : ";
	if (player->transparency)
		cout << "ON\t";
	else
		cout << "OFF\t";
	cout << "���б� : ";
	if (player->wallPush) {
		cout << "���� / ";
		if (player->pushOnOff)
			cout << "ON";
		else
			cout << "OFF";
	}
	else
		cout << "�Ұ��� / OFF";
	cout << endl << endl;
}

bool addItem(char itemType, PPLAYER player) {
	if (itemType == '5') {
		if(player->bombPower < 5)
			player->bombPower++;
		return true;
	}
	else if (itemType == '6') {
		player->wallPush = true;
		player->pushOnOff = true;
		return true;
	}
	else if (itemType == '7') {
		player->transparency = true;
		return true;
	}

	return false;
}

void moveUp(char maze[21][21], PPLAYER player) {

	if (player->pos.y - 1 >= 0) {
		

		if (maze[player->pos.y - 1][player->pos.x] != '0' &&
			maze[player->pos.y - 1][player->pos.x] != '4') {
			player->pos.y--;
		}

		else if (player->wallPush && maze[player->pos.y - 1][player->pos.x] == '0') {
			if (player->pushOnOff) {
				if (player->pos.y - 2 >= 0) {
					if (maze[player->pos.y - 2][player->pos.x] == '0') {
						if (player->transparency)
							player->pos.y--;
					}
					else if (maze[player->pos.y - 2][player->pos.x] == '1') {
						maze[player->pos.y - 2][player->pos.x] = '0';
						maze[player->pos.y - 1][player->pos.x] = '1';
						player->pos.y--;
					}
				}
				else if (player->transparency)
					player->pos.y--;
			}
			else if (player->transparency)
				player->pos.y--;
		}

		else if (player->transparency)
			player->pos.y--;

		if (addItem(maze[player->pos.y][player->pos.x], player)) 
			maze[player->pos.y][player->pos.x] = '1';
		
	}
}

void moveDown(char maze[21][21], PPLAYER player) {
	if (player->pos.y + 1 < 20) {
		if (maze[player->pos.y + 1][player->pos.x] != '0' &&
			maze[player->pos.y + 1][player->pos.x] != '4') {
			player->pos.y++;
		}

		else if (player->wallPush && maze[player->pos.y + 1][player->pos.x] == '0') {
			if (player->pushOnOff) {
				if (player->pos.y + 2 < 20) {
					if (maze[player->pos.y + 2][player->pos.x] == '0') {
						if (player->transparency)
							player->pos.y++;
					}
					else if (maze[player->pos.y + 2][player->pos.x] == '1') {
						maze[player->pos.y + 2][player->pos.x] = '0';
						maze[player->pos.y + 1][player->pos.x] = '1';
						player->pos.y++;
					}
				}
				else if (player->transparency)
					player->pos.y++;
			}
			else if (player->transparency)
				player->pos.y++;
		}

		else if (player->transparency)
			player->pos.y++;

		if (addItem(maze[player->pos.y][player->pos.x], player)) 
			maze[player->pos.y][player->pos.x] = '1';
	}
}


void moveLeft(char maze[21][21], PPLAYER player) {
	if (player->pos.x - 1 >= 0) {
		if (maze[player->pos.y][player->pos.x - 1] != '0' &&
			maze[player->pos.y][player->pos.x - 1] != '4') {
			player->pos.x--;
		}

		else if (player->wallPush && maze[player->pos.y][player->pos.x-1] == '0') {
			if (player->pushOnOff) {
				if (player->pos.x - 2 >= 0) {
					if (maze[player->pos.y][player->pos.x - 2] == '0') {
						if (player->transparency)
							player->pos.x--;
					}
					else if (maze[player->pos.y][player->pos.x - 2] == '1') {
						maze[player->pos.y][player->pos.x - 2] = '0';
						maze[player->pos.y][player->pos.x - 1] = '1';
						player->pos.x--;
					}
				}
				else if (player->transparency)
					player->pos.x--;
			}
			else if (player->transparency)
				player->pos.x--;
		}

		else if (player->transparency)
			player->pos.x--;

		if (addItem(maze[player->pos.y][player->pos.x], player)) 
			maze[player->pos.y][player->pos.x] = '1';
	}
}

void moveRight(char maze[21][21], PPLAYER player) {
	if (player->pos.x + 1 < 20) {
		if (maze[player->pos.y][player->pos.x + 1] != '0' &&
			maze[player->pos.y][player->pos.x + 1] != '4') {
			player->pos.x++;
		}

		else if (player->wallPush && maze[player->pos.y][player->pos.x + 1] == '0') {
			if (player->pushOnOff) {
				if (player->pos.x + 2 < 20) {
					if (maze[player->pos.y][player->pos.x + 2] == '0') {
						if (player->transparency)
							player->pos.x++;
					}
					else if (maze[player->pos.y][player->pos.x + 2] == '1') {
						maze[player->pos.y][player->pos.x + 2] = '0';
						maze[player->pos.y][player->pos.x + 1] = '1';
						player->pos.x++;
					}
				}
				else if (player->transparency)
					player->pos.x++;
			}
			else if (player->transparency)
				player->pos.x++;
		}

		else if (player->transparency)
			player->pos.x++;

		if (addItem(maze[player->pos.y][player->pos.x], player)) 
			maze[player->pos.y][player->pos.x] = '1';
	}
}

void movePlayer(char maze[21][21], PPLAYER player, char input) {
	switch (input) {
	case 'w':
	case 'W':
		moveUp(maze, player);
		break;
	case 's':
	case 'S':
		moveDown(maze, player);
		break;
	case 'a':
	case 'A':
		moveLeft(maze, player);
		break;
	case 'd':
	case 'D':
		moveRight(maze, player);
		break;
	}
}

void createBomb(char maze[21][21], const PPLAYER player, PPOINT bombArr, int* bombCount) {
	if (*bombCount == 5)
		return;

	else if (maze[player->pos.y][player->pos.x] == '0')
		return;

	for (int i = 0; i < *bombCount; i++) {
		if (player->pos.x == bombArr[i].x &&
			player->pos.y == bombArr[i].y)
			return;
	}

	bombArr[*bombCount] = player->pos;
	(*bombCount)++;

	maze[player->pos.y][player->pos.x] = '4';
}

void fire(char maze[21][21], PPLAYER player, PPOINT bombArr, int* bombCount) {
	for (int i = 0; i < *bombCount; i++) {
		maze[bombArr[i].y][bombArr[i].x] = '1';

		if (player->pos.x == bombArr[i].x && player->pos.y == bombArr[i].y) {
			player->pos.x = 0;
			player->pos.y = 0;
		}

		for (int j = 1; j < player->bombPower+1; j++) 
		{
			if (bombArr[i].y - j >= 0) {
				if (maze[bombArr[i].y - j][bombArr[i].x] == '0') {
					// ������ Ȯ���� ���Ѵ�.
					if (rand() % 100 < 20) {
						int percent = rand() % 100;
						if (percent < 70) {
							maze[bombArr[i].y - j][bombArr[i].x] = '5';
						}
						else if (percent < 80) {
							maze[bombArr[i].y - j][bombArr[i].x] = '6';
						}
						else {
							maze[bombArr[i].y - j][bombArr[i].x] = '7';
						}
					}
					else
						maze[bombArr[i].y - j][bombArr[i].x] = '1';
				}
				if (player->pos.x == bombArr[i].x && player->pos.y == bombArr[i].y - j) {
					player->pos.x = 0;
					player->pos.y = 0;
				}
			}

			if (bombArr[i].y + j < 20) {
				if (maze[bombArr[i].y + j][bombArr[i].x] == '0') {
					if (rand() % 100 < 20) {
						int percent = rand() % 100;
						if (percent < 70) {
							maze[bombArr[i].y + j][bombArr[i].x] = '5';
						}
						else if (percent < 80) {
							maze[bombArr[i].y + j][bombArr[i].x] = '6';
						}
						else {
							maze[bombArr[i].y + j][bombArr[i].x] = '7';
						}
					}
					else
						maze[bombArr[i].y + j][bombArr[i].x] = '1';
				}
				if (player->pos.x == bombArr[i].x && player->pos.y == bombArr[i].y + j) {
					player->pos.x = 0;
					player->pos.y = 0;
				}
			}

			if (bombArr[i].x - j >= 0) {
				if (maze[bombArr[i].y][bombArr[i].x - j] == '0') {
					if (rand() % 100 < 20) {
						int percent = rand() % 100;
						if (percent < 70) {
							maze[bombArr[i].y][bombArr[i].x - j] = '5';
						}
						else if (percent < 80) {
							maze[bombArr[i].y][bombArr[i].x - j] = '6';
						}
						else {
							maze[bombArr[i].y][bombArr[i].x - j] = '7';
						}
					}
					else
						maze[bombArr[i].y][bombArr[i].x - j] = '1';
				}
				if (player->pos.x == bombArr[i].x - j && player->pos.y == bombArr[i].y) {
					player->pos.x = 0;
					player->pos.y = 0;
				}
			}

			if (bombArr[i].x + j < 20) {
				if (maze[bombArr[i].y][bombArr[i].x + j] == '0') {
					if (rand() % 100 < 20) {
						int percent = rand() % 100;
						if (percent < 70) {
							maze[bombArr[i].y][bombArr[i].x + j] = '5';
						}
						else if (percent < 80) {
							maze[bombArr[i].y][bombArr[i].x + j] = '6';
						}
						else {
							maze[bombArr[i].y][bombArr[i].x + j] = '7';
						}
					}
					else
						maze[bombArr[i].y][bombArr[i].x + j] = '1';
				}
				if (player->pos.x == bombArr[i].x + j && player->pos.y == bombArr[i].y) {
					player->pos.x = 0;
					player->pos.y = 0;
				}
			}
		}
		
	}


	*bombCount = 0;
}

int main() {
	srand((unsigned int)time(0));
	// 20 x 20 �̷θ� ������ش�.
	char maze[21][21];

	PLAYER player = {};
	POINT startPos;
	POINT endPos;

	player.bombPower = 1;

	int bombCount = 0;

	POINT bombPos[5];

	setMaze(maze, &player, &startPos, &endPos);
	while (true) {
		system("cls");
		outputMaze(maze, &player);
		if (player.pos.x == endPos.x && player.pos.y == endPos.y) {
			cout << "�����߽��ϴ�" << endl;
			break;
		}
		cout << "| �� : ��ź�Ŀ� up | �� : �� �б� | �� : ���������� |" << endl;
		cout << "| t : ��ź��ġ | u : ��ź ��Ʈ���� | i : ���б� ON/OFF | " << endl;
		cout << "| w : �� | s : �Ʒ� | a : ���� | d : ������ | q : ���� | : ";
		char input = _getch();
		if (input == 'q' || input == 'Q')
			break;
		else if (input == 't' || input == 'T')
			createBomb(maze, &player, bombPos, &bombCount);
		else if (input == 'u' || input == 'U')
			fire(maze, &player, bombPos, &bombCount);
		else if (input == 'i' || input == 'I')
		{
			if (player.wallPush)
				player.pushOnOff = !player.pushOnOff;
		}

		movePlayer(maze, &player, input);
		
	}
	return 0;
}