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

		// ai 숫자 섞기
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

	// AI 난이도를 선택한다.  
	while(true) {
		system("cls");
		std::cout << "1. Easy" << endl;
		std::cout << "2. Hard" << endl;
		std::cout << "AI 모드를 선택하세요 : ";
		std::cin >> aiMode;
		if (aiMode >= AM_EASY && aiMode <= AM_HARD)
			break;
	}


	int input;
	/*
	AI Easy 모드는 현재 AI의 숫자목록중 *로 바뀌지 않은 숫자 목록을 만들어서 그 목록 중 하나를 선택하게 한다.(랜덤하게)
	*/
	int noneSelect[25];
	int noneSelectCount = 0;

	// AI Hard 모드
	int line = 0;
	int starCount = 0;
	int saveCount = 0;

	while (true) {

		system("cls");

		// Player 빙고 출력
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
		std::cout << "Player 빙고 수는 " << bingoCount << " 입니다." << endl;
		std::cout << endl;

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

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (aiBingoBoard[i * 5 + j] == INT_MAX)
					std::cout << '*' << '\t';
				else
					std::cout << aiBingoBoard[i * 5 + j] << '\t';
			}
			std::cout << endl;
		}
		std::cout << "AI 빙고 수는 " << aiBingoCount << " 입니다." << endl;
		std::cout << endl;


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

		// AI 난이도 선택
		
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

			// 가로 체크
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

			// 세로 체크
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

			// 오른아래 대각선 체크
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

			// 왼아래 대각선 체크
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


		// 빙고 체크
		bingoCount = 0;
		aiBingoCount = 0;

		for (int i = 0; i < 5; i++) {
			// 가로 빙고 체크
			for (int j = 0; j < 5; j++) {
				if (bingoBoard[i * 5 + j] == INT_MAX) {
					count++;
				}
			}
			if (count == 5) {
				bingoCount++;
			}
			count = 0;

			// 세로 빙고 체크
			for (int j = 0; j < 5; j++) {
				if (bingoBoard[j * 5 + i] == INT_MAX) {
					count++;
				}
			}
			if (count == 5) {
				bingoCount++;
			}
			count = 0;

			// ai 가로 빙고 체크
			for (int j = 0; j < 5; j++) {
				if (aiBingoBoard[i * 5 + j] == INT_MAX) {
					count++;
				}
			}
			if (count == 5) {
				aiBingoCount++;
			}
			count = 0;

			// ai 세로 빙고 체크
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


		// 오른아래 대각선 체크
		for (int i = 0; i < 5; i++) {
			if (bingoBoard[6 * i] == INT_MAX) {
				count++;
			}
		}
		if (count == 5) {
			bingoCount++;
		}
		count = 0;

		// 왼아래 대각선 체크
		for (int i = 0; i < 5; i++) {
			if (bingoBoard[4 * (i + 1)] == INT_MAX) {
				count++;
			}
		}
		if (count == 5) {
			bingoCount++;
		}
		count = 0;

		// ai 오른아래 대각선 체크
		for (int i = 0; i < 5; i++) {
			if (aiBingoBoard[6 * i] == INT_MAX) {
				count++;
			}
		}
		if (count == 5) {
			aiBingoCount++;
		}
		count = 0;

		// ai 왼아래 대각선 체크
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

	std::cout << "게임을 종료합니다." << endl;

	return 0;
}