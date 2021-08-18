#include <iostream>
#include <time.h>
// console input output 헤더파일, 콘솔창에서 입출력 하는 기능들을 제공해주는 헤더파일이다.
#include <conio.h>

using namespace std;

int main() {
	srand((unsigned int)time(0));

	int iNumber[25] = {};

	for (int i = 0; i < 24; i++) {
		iNumber[i] = i + 1;
	}


	// 가장 마지막 칸은 공백으로 비워둔다.
	// 공백을 의미하는 값으로 특수한 값을 사용할건데 INT_MAX라는 것을 사용할 것이다.
	// INT_MAX는 이미 정의되어있는 값으로 int로 표현할 수 있는 최대값이다.

	iNumber[24] = INT_MAX;

	int temp, idx1, idx2;

	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 24;
		idx2 = rand() % 24;

		temp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = temp;
	}

	int starLoc = 24;

	while (true) {
		// 내 풀이
		/*for (int i = 0; i < 25; i++) {
			if (i % 5 == 0) {
				cout << endl;
			}
			cout << iNumber[i] << '\t';
		}*/

		// 영상 풀이
		system("cls");
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (iNumber[i * 5 + j] == INT_MAX)
					cout << '*' << '\t';
				else
					cout << iNumber[i * 5 + j] << '\t';
			}
			cout << endl;
		}

		// 퍼즐 맞추었는지 확인
		bool bWin = true;

		for (int i = 0; i < 24; i++) {
			if (iNumber[i] != i + 1) {
				bWin = false;
				break;
			}
		}

		if (bWin == true) {
			cout << "숫자를 모두 맞췄습니다" << endl;
			break;
		}

		cout << "| w : 위 | s : 아래 | a : 왼쪽 | d : 오른쪽 | q : 종료 |" << endl;
		// _getch() 함수는 문자 1개를 입력받는 함수이다.
		// 이 함수는 enter를 치지 않더라도 문자를 누르는 순간 바로 그 문자를 반환하고 종료한다.
		char cInput = _getch();
		
		if (cInput == 'q' || cInput == 'Q')
			break;
		
		
		switch (cInput) {
		case 'w':
		case 'W':
			if (starLoc >= 5) {
				iNumber[starLoc] = iNumber[starLoc - 5];
				starLoc -= 5;
				iNumber[starLoc] = INT_MAX;
			}
			break;
		case 's':
		case 'S':
			if (starLoc <= 19) {
				iNumber[starLoc] = iNumber[starLoc + 5];
				starLoc += 5;
				iNumber[starLoc] = INT_MAX;
			}
			break;
		case 'a':
		case 'A':
			if (starLoc > (starLoc / 5) * 5) { // starLoc % 5 != 0     
				iNumber[starLoc] = iNumber[starLoc - 1];
				starLoc -= 1;
				iNumber[starLoc] = INT_MAX;
			}
			break;
		case 'd':
		case 'D':
			if (starLoc < (starLoc / 5) * 5 + 4) { // starLoc % 5 != 4
				iNumber[starLoc] = iNumber[starLoc + 1];
				starLoc += 1;
				iNumber[starLoc] = INT_MAX;
			}
			break;
		default:
			break;
		}
	}

	cout << "게임을 종료합니다." << endl;
	return 0;
}