#include <iostream>
#include <time.h>

using namespace std;

enum SRP {
	Sissor = 1,
	Rock,
	Paper,
	End
};

int main() {
	/*
		9강
		반복문 : 특정 작업을 반복해서 수행해주는 기능이다.
		종류 : for, while, do while
		*/

	int number = 0;

	system("cls");

	srand((unsigned int)time(0));
	int my;

	while (true) {
		int com = rand() % 3 + 1;

		cout << "1: 가위 2: 바위 3: 보 4: 종료" << endl;
		cout << "다음 중 선택하세요" << endl;
		cin >> my;

		if (my < Sissor || my > End) {
			cout << "값을 잘못 입력하였습니다" << endl;
			continue;
		}
		else if (my == End) {
			break;
		}

		// 강의 풀이 -
		switch (com) {
		case 1:
			cout << "com : 가위" << endl;
			break;
		case 2:
			cout << "com : 바위" << endl;
			break;
		case 3:
			cout << "com : 보" << endl;
			break;
		}

		int win = my - com;
		if (win == 1 || win == -2)
			cout << "승리" << endl;
		else if (win == 0)
			cout << "무승부" << endl;
		else
			cout << "패배" << endl;

		// 내 풀이 - 일반적인 풀이
		/*else if (my == Sissor) {
			if (com == Sissor) {
				cout << "my : 가위 com : 가위   무승부입니다." << endl;
			}
			else if (com == Rock) {
				cout << "my : 가위 com : 바위   패배하였습니다." << endl;
			}
			else if (com == Paper) {
				cout << "my : 가위 com : 보   승리하였습니다." << endl;
			}
		}
		else if (my == Rock) {
			if (com == Sissor) {
				cout << "my : 바위 com : 가위   승리하였습니다." << endl;
			}
			else if (com == Rock) {
				cout << "my : 바위 com : 바위   무승부입니다." << endl;
			}
			else if (com == Paper) {
				cout << "my : 바위 com : 보   패배하였습니다." << endl;
			}
		}
		else if (my == Paper) {
			if (com == Sissor) {
				cout << "my : 보 com : 가위   패배하였습니다." << endl;
			}
			else if (com == Rock) {
				cout << "my : 보 com : 바위   승리하였습니다." << endl;
			}
			else if (com == Paper) {
				cout << "my : 보 com : 보   무승부입니다." << endl;
			}
		}*/



	}
}