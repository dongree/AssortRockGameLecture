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

int main() {

	srand((unsigned int)time(0));

	int bingoBoard[25] = {};
	int aiBingoBoard[25] = {};

	for (int i = 0; i < 25; i++) {
		bingoBoard[i] = i + 1;
		aiBingoBoard[i] = i + 1;
	}
	
	int temp, idx1, idx2;

	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		temp = bingoBoard[idx1];
		bingoBoard[idx1] = bingoBoard[idx2];
		bingoBoard[idx2] = temp;

		// ai ���� ����
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		temp = aiBingoBoard[idx1];
		aiBingoBoard[idx1] = aiBingoBoard[idx2];
		aiBingoBoard[idx2] = temp;
	}

	int count = 0;
	int bingoCount = 0;
	int aiBingoCount = 0;
	int aiMode;

	// AI ���̵��� �����Ѵ�.  
	while(true) {
		system("cls");
		std::cout << "1. Easy" << endl;
		std::cout << "2. Hard" << endl;
		std::cout << "AI ��带 �����ϼ��� : ";
		std::cin >> aiMode;
		if (aiMode >= AM_EASY && aiMode <= AM_HARD)
			break;
	}


	int input;
	/*
	AI Easy ���� ���� AI�� ���ڸ���� *�� �ٲ��� ���� ���� ����� ���� �� ��� �� �ϳ��� �����ϰ� �Ѵ�.(�����ϰ�)
	*/
	int noneSelect[25];
	int noneSelectCount = 0;

	// AI Hard ���
	int line = 0;
	int starCount = 0;
	int saveCount = 0;

	while (true) {

		system("cls");

		// Player ���� ���
		std::cout << "============ Player ============" << endl;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (bingoBoard[i *5 +j] == INT_MAX)
					std::cout << '*' << '\t';
				else
					std::cout << bingoBoard[i * 5 + j] << '\t';
			}
			std::cout << endl;
		}
		std::cout << "Player ���� ���� " << bingoCount << " �Դϴ�." << endl;
		std::cout << endl;

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

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (aiBingoBoard[i * 5 + j] == INT_MAX)
					std::cout << '*' << '\t';
				else
					std::cout << aiBingoBoard[i * 5 + j] << '\t';
			}
			std::cout << endl;
		}
		std::cout << "AI ���� ���� " << aiBingoCount << " �Դϴ�." << endl;
		std::cout << endl;


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

		int a;
		std::cin >> a;

		if (a == 0)
			break;
		else if (a < 1 || a > 25)
			continue;

		bool flag = true;
		// Player
		for (int i = 0; i < 25; i++) {
			if (bingoBoard[i] == a) {
				flag = false;
				bingoBoard[i] = INT_MAX;
				break;
			}
		}

		if (flag)
			continue;

		// AI
		for (int i = 0; i < 25; i++) {
			if (aiBingoBoard[i] == a) {
				aiBingoBoard[i] = INT_MAX;
				break;
			}
		}

		// AI ���̵� ����
		
		switch (aiMode) {
		case AM_EASY:
			noneSelectCount = 0;
			for (int i = 0; i < 25; i++) {
				if (aiBingoBoard[i] != INT_MAX) {
					noneSelect[noneSelectCount] = aiBingoBoard[i];
					noneSelectCount++;
				}
			}
			input = noneSelect[rand() % noneSelectCount];

			break;


		case AM_HARD:
			line = 0;
			starCount = 0;
			saveCount = 0;

			// ���� üũ
			for (int i = 0; i < 5; i++) {
				starCount = 0;
				for (int j = 0; j < 5; j++) {
					if (aiBingoBoard[i * 5 + j] == INT_MAX)
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
					if (aiBingoBoard[j * 5 + i] == INT_MAX)
						starCount++;
				}
				if (starCount < 5 && saveCount < starCount) {
					line = i+5;
					saveCount = starCount;
				}
			}

			// �����Ʒ� �밢�� üũ
			starCount = 0;
			for (int i = 0; i < 5; i++) {
				if (bingoBoard[6 * i] == INT_MAX) {
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
				if (bingoBoard[4 * (i + 1)] == INT_MAX) {
					starCount++;
				}
			}
			if (starCount < 5 && saveCount < starCount) {
				line = LN_RT;
				saveCount = starCount;
			}


			if (line <= LN_H5) {
				for (int i = 0; i < 5; i++) {
					if (aiBingoBoard[line * 5 + i] != INT_MAX) {
						input = aiBingoBoard[line * 5 + i];
						break;
					}
				}
			}
			else if (line <= LN_V5) {
				for (int i = 0; i < 5; i++) {
					if (aiBingoBoard[i * 5 + line - 5] != INT_MAX) {
						input = aiBingoBoard[i * 5 + line - 5];
						break;
					}
				}
			}
			else if (line == LN_LT) {
				for (int i = 0; i < 5; i++) {
					if (aiBingoBoard[6 * i] == INT_MAX) {
						input = aiBingoBoard[6 * i];
						break;
					}
				}
			}

			else if (line == LN_RT) {
				for (int i = 0; i < 5; i++) {
					if (aiBingoBoard[4 * (i+1)] == INT_MAX) {
						input = aiBingoBoard[4 * (i + 1)];
						break;
					}
				}
			}

			break;
		default:
			break;
		}

		for (int i = 0; i < 25; i++) {
			if (bingoBoard[i] == input) {
				bingoBoard[i] = INT_MAX;
				break;
			}
		}

		for (int i = 0; i < 25; i++) {
			if (aiBingoBoard[i] == input) {
				aiBingoBoard[i] = INT_MAX;
				break;
			}
		}


		// ���� üũ
		bingoCount = 0;
		aiBingoCount = 0;

		for (int i = 0; i < 5; i++) {
			// ���� ���� üũ
			for (int j = 0; j < 5; j++) {
				if (bingoBoard[i * 5 + j] == INT_MAX) {
					count++;
				}
			}
			if (count == 5) {
				bingoCount++;
			}
			count = 0;

			// ���� ���� üũ
			for (int j = 0; j < 5; j++) {
				if (bingoBoard[j * 5 + i] == INT_MAX) {
					count++;
				}
			}
			if (count == 5) {
				bingoCount++;
			}
			count = 0;

			// ai ���� ���� üũ
			for (int j = 0; j < 5; j++) {
				if (aiBingoBoard[i * 5 + j] == INT_MAX) {
					count++;
				}
			}
			if (count == 5) {
				aiBingoCount++;
			}
			count = 0;

			// ai ���� ���� üũ
			for (int j = 0; j < 5; j++) {
				if (aiBingoBoard[j * 5 + i] == INT_MAX) {
					count++;
				}
			}
			if (count == 5) {
				aiBingoCount++;
			}
			count = 0;
		}


		// �����Ʒ� �밢�� üũ
		for (int i = 0; i < 5; i++) {
			if (bingoBoard[6 * i] == INT_MAX) {
				count++;
			}
		}
		if (count == 5) {
			bingoCount++;
		}
		count = 0;

		// �޾Ʒ� �밢�� üũ
		for (int i = 0; i < 5; i++) {
			if (bingoBoard[4 * (i + 1)] == INT_MAX) {
				count++;
			}
		}
		if (count == 5) {
			bingoCount++;
		}
		count = 0;

		// ai �����Ʒ� �밢�� üũ
		for (int i = 0; i < 5; i++) {
			if (aiBingoBoard[6 * i] == INT_MAX) {
				count++;
			}
		}
		if (count == 5) {
			aiBingoCount++;
		}
		count = 0;

		// ai �޾Ʒ� �밢�� üũ
		for (int i = 0; i < 5; i++) {
			if (aiBingoBoard[4 * (i + 1)] == INT_MAX) {
				count++;
			}
		}
		if (count == 5) {
			aiBingoCount++;
		}
		count = 0;

	}

	std::cout << "������ �����մϴ�." << endl;

	return 0;
}