/*
숙제 : 숫자빙고게임 만들어보자
1~25까지의 숫자가 있고 이 숫자를 골고루 섞어서 5 x 5로 출력한다.
플레이어는 숫자를 입력받는다. 1~25 사이의 숫자를 입력받아야 한다.
0을 입력하면 게임을 종료한다.

숫자를 입력받았으면 숫자목록 중 입력받은 숫자를 찾아서 *로 만들어준다.
숫자를 *로 만든 후에 빙고 줄 수를 체크한다. 5x5이기 때문에 가로 5줄 세로 5줄 대각선 2줄이 나올 수 있다.
빙고줄이 몇줄인지를 체크해서 화면에 보여준다. 5줄 이상일 경우 게임을 종료한다.

*/

#include <iostream>
#include <time.h>

using namespace std;

enum AI_MODE {
	AM_EASY = 1,
	AM_HARD
};

enum LINE_NUMBER {
	LN_H1,
	LN_H2,
	LN_H3,
	LN_H4,
	LN_H5,
	LN_V1,
	LN_V2,
	LN_V3,
	LN_V4,
	LN_V5,
	LN_LT,
	LN_RT
};

void setNumber(int *pArray);
void shuffle(int* pArray);
AI_MODE selectAIMode();
void outputNumber(int *pArray, int bingoCount);
bool changeNumber(int* pArray, int input);
int selectAINumber(int* pArray, AI_MODE mode);
int bingoCounting(int* pArray);
int bingoCountingH(int* pArray);
int bingoCountingV(int* pArray);
int bingoCountingLTD(int* pArray);
int bingoCountingRTD(int* pArray);


int main() {

	srand((unsigned int)time(0));

	int bingoBoard[25] = {};
	int aiBingoBoard[25] = {};

	setNumber(bingoBoard);
	setNumber(aiBingoBoard);
	
	shuffle(bingoBoard);
	shuffle(aiBingoBoard);

	int bingoCount = 0;
	int aiBingoCount = 0;

	// AI 난이도를 선택한다. 
	AI_MODE aiMode = selectAIMode();
	

	while (true) {

		system("cls");

		// Player 빙고 출력
		std::cout << "============ Player ============" << endl;
		outputNumber(bingoBoard, bingoCount);
		
		// AI 빙고 출력
		std::cout << "============== AI ==============" << endl;

		switch (aiMode) {
		case AM_EASY:
			cout << "AIMode : Easy" << endl;
			break;
		case AM_HARD:
			cout << "AIMode : Hard" << endl;
			break;
		}

		outputNumber(aiBingoBoard, aiBingoCount);

		// 승패 결정
		if (bingoCount >= 5) {
			std::cout << "Player 승리" << endl;
			break;
		}

		if (aiBingoCount >= 5) {
			std::cout << "AI 승리" << endl;
			break;
		}

		// 숫자 입력
		std::cout << "위 빙고판의 숫자 중 하나를 입력해주세요(0 : 종료)" << endl;
		
		int input;
		std::cin >> input;

		if (input == 0)
			break;
		else if (input < 1 || input > 25)
			continue;

		// player
		bool flag = changeNumber(bingoBoard, input);

		if (flag)
			continue;

		// AI
		changeNumber(aiBingoBoard, input);

		// ai가 숫자를 선택
		input = selectAINumber(aiBingoBoard, aiMode);


		changeNumber(bingoBoard, input);
		changeNumber(aiBingoBoard, input);


		// 빙고 체크
		bingoCount = bingoCounting(bingoBoard);
		aiBingoCount = bingoCounting(aiBingoBoard);


		
	}

	std::cout << "게임을 종료합니다." << endl;

	return 0;
}


void setNumber(int* pArray) {
	for (int i = 0; i < 25; i++) {
		pArray[i] = i + 1;
	}
}

void shuffle(int* pArray) {
	int temp, idx1, idx2;

	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		temp = pArray[idx1];
		pArray[idx1] = pArray[idx2];
		pArray[idx2] = temp;
	}
}

AI_MODE selectAIMode() {
	int aiMode;
	while (true) {
		system("cls");
		std::cout << "1. Easy" << endl;
		std::cout << "2. Hard" << endl;
		std::cout << "AI 모드를 선택하세요 : ";
		std::cin >> aiMode;
		if (aiMode >= AM_EASY && aiMode <= AM_HARD)
			break;
	}
	return (AI_MODE)aiMode;
}

void outputNumber(int* pArray, int bingoCount) {
	
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (pArray[i * 5 + j] == INT_MAX)
				std::cout << '*' << '\t';
			else
				std::cout << pArray[i * 5 + j] << '\t';
		}
		std::cout << endl;
	}

	cout << "bingo Line : " << bingoCount << endl << endl;
}

bool changeNumber(int* pArray, int input) {
	for (int i = 0; i < 25; i++) {
		if (pArray[i] == input) {
			pArray[i] = INT_MAX;
			return false;
		}
	}
	return true;
}

int selectAINumber(int* pArray, AI_MODE mode) {
	int noneSelect[25] = {};
	int noneSelectCount;
	switch (mode) {
	case AM_EASY:
		noneSelectCount = 0;
		for (int i = 0; i < 25; i++) {
			if (pArray[i] != INT_MAX) {
				noneSelect[noneSelectCount] = pArray[i];
				noneSelectCount++;
			}
		}
		return noneSelect[rand() % noneSelectCount];

	case AM_HARD:
		int line = 0;
		int starCount = 0;
		int saveCount = 0;

		// 가로 체크
		for (int i = 0; i < 5; i++) {
			starCount = 0;
			for (int j = 0; j < 5; j++) {
				if (pArray[i * 5 + j] == INT_MAX)
					starCount++;
			}
			if (starCount < 5 && saveCount < starCount) {
				line = i;
				saveCount = starCount;
			}
		}

		// 세로 체크
		for (int i = 0; i < 5; i++) {
			starCount = 0;
			for (int j = 0; j < 5; j++) {
				if (pArray[j * 5 + i] == INT_MAX)
					starCount++;
			}
			if (starCount < 5 && saveCount < starCount) {
				line = i + 5;
				saveCount = starCount;
			}
		}

		// 오른아래 대각선 체크
		starCount = 0;
		for (int i = 0; i < 5; i++) {
			if (pArray[6 * i] == INT_MAX) {
				starCount++;
			}
		}
		if (starCount < 5 && saveCount < starCount) {
			line = LN_LT;
			saveCount = starCount;
		}

		// 왼아래 대각선 체크
		starCount = 0;
		for (int i = 0; i < 5; i++) {
			if (pArray[4 * (i + 1)] == INT_MAX) {
				starCount++;
			}
		}
		if (starCount < 5 && saveCount < starCount) {
			line = LN_RT;
			saveCount = starCount;
		}


		if (line <= LN_H5) {
			for (int i = 0; i < 5; i++) {
				if (pArray[line * 5 + i] != INT_MAX) {
					return pArray[line * 5 + i];
				}
			}
		}
		else if (line <= LN_V5) {
			for (int i = 0; i < 5; i++) {
				if (pArray[i * 5 + line - 5] != INT_MAX) {
					return pArray[i * 5 + line - 5];
				}
			}
		}
		else if (line == LN_LT) {
			for (int i = 0; i < 5; i++) {
				if (pArray[6 * i] == INT_MAX) {
					return pArray[6 * i];
				}
			}
		}

		else if (line == LN_RT) {
			for (int i = 0; i < 5; i++) {
				if (pArray[4 * (i + 1)] == INT_MAX) {
					return pArray[4 * (i + 1)];
				}
			}
		}

		break;
	}

	return -1;
}

int bingoCounting(int* pArray) {
	int bingo = 0;

	// 가로줄 체크
	bingo += bingoCountingH(pArray);
	// 세로줄 체크
	bingo += bingoCountingV(pArray);
	// 왼쪽 상단 대각선 체크
	bingo += bingoCountingLTD(pArray);
	// 오른쪽 상단 대각선 체크
	bingo += bingoCountingRTD(pArray);

	return bingo;
}

int bingoCountingH(int* pArray) {
	int count = 0;
	int bingoCount = 0;
	for (int i = 0; i < 5; i++) {
		// 가로 빙고 체크
		for (int j = 0; j < 5; j++) {
			if (pArray[i * 5 + j] == INT_MAX) {
				count++;
			}
		}
		if (count == 5)
			bingoCount++;
		count = 0;
	}
	return bingoCount;
		
}

int bingoCountingV(int* pArray) {
	int count = 0;
	int bingoCount = 0;
	for (int i = 0; i < 5; i++) {
		// 가로 빙고 체크
		for (int j = 0; j < 5; j++) {
			if (pArray[j * 5 + i] == INT_MAX) {
				count++;
			}
		}
		if (count == 5)
			bingoCount++;
		count = 0;
	}
	return bingoCount;
}
	


int bingoCountingLTD(int* pArray) {
	int count = 0;
	int bingoCount = 0;
	for (int i = 0; i < 5; i++) {
		if (pArray[6 * i] == INT_MAX) {
			count++;
		}
	}
	if (count == 5) 
		bingoCount++;
	return bingoCount;
}


int bingoCountingRTD(int* pArray) {
	int count = 0;
	int bingoCount = 0;
	for (int i = 0; i < 5; i++) {
		if (pArray[4 * (i + 1)] == INT_MAX) {
			count++;
		}
	}
	if (count == 5) 
		bingoCount++;
	return bingoCount;
}