/*
���� : ���ں������ ������
1~25������ ���ڰ� �ְ� �� ���ڸ� ���� ��� 5 x 5�� ����Ѵ�.
�÷��̾�� ���ڸ� �Է¹޴´�. 1~25 ������ ���ڸ� �Է¹޾ƾ� �Ѵ�.
0�� �Է��ϸ� ������ �����Ѵ�.

���ڸ� �Է¹޾����� ���ڸ�� �� �Է¹��� ���ڸ� ã�Ƽ� *�� ������ش�.
���ڸ� *�� ���� �Ŀ� ���� �� ���� üũ�Ѵ�. 5x5�̱� ������ ���� 5�� ���� 5�� �밢�� 2���� ���� �� �ִ�.
�������� ���������� üũ�ؼ� ȭ�鿡 �����ش�. 5�� �̻��� ��� ������ �����Ѵ�.

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

	// AI ���̵��� �����Ѵ�. 
	AI_MODE aiMode = selectAIMode();
	

	while (true) {

		system("cls");

		// Player ���� ���
		std::cout << "============ Player ============" << endl;
		outputNumber(bingoBoard, bingoCount);
		
		// AI ���� ���
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

		// ���� ����
		if (bingoCount >= 5) {
			std::cout << "Player �¸�" << endl;
			break;
		}

		if (aiBingoCount >= 5) {
			std::cout << "AI �¸�" << endl;
			break;
		}

		// ���� �Է�
		std::cout << "�� �������� ���� �� �ϳ��� �Է����ּ���(0 : ����)" << endl;
		
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

		// ai�� ���ڸ� ����
		input = selectAINumber(aiBingoBoard, aiMode);


		changeNumber(bingoBoard, input);
		changeNumber(aiBingoBoard, input);


		// ���� üũ
		bingoCount = bingoCounting(bingoBoard);
		aiBingoCount = bingoCounting(aiBingoBoard);


		
	}

	std::cout << "������ �����մϴ�." << endl;

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
		std::cout << "AI ��带 �����ϼ��� : ";
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

		// ���� üũ
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

		// ���� üũ
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

		// �����Ʒ� �밢�� üũ
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

		// �޾Ʒ� �밢�� üũ
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

	// ������ üũ
	bingo += bingoCountingH(pArray);
	// ������ üũ
	bingo += bingoCountingV(pArray);
	// ���� ��� �밢�� üũ
	bingo += bingoCountingLTD(pArray);
	// ������ ��� �밢�� üũ
	bingo += bingoCountingRTD(pArray);

	return bingo;
}

int bingoCountingH(int* pArray) {
	int count = 0;
	int bingoCount = 0;
	for (int i = 0; i < 5; i++) {
		// ���� ���� üũ
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
		// ���� ���� üũ
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