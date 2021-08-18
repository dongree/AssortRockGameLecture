#include <iostream>
#include <time.h>
// console input output �������, �ܼ�â���� ����� �ϴ� ��ɵ��� �������ִ� ��������̴�.
#include <conio.h>

using namespace std;

int main() {
	srand((unsigned int)time(0));

	int iNumber[25] = {};

	for (int i = 0; i < 24; i++) {
		iNumber[i] = i + 1;
	}


	// ���� ������ ĭ�� �������� ����д�.
	// ������ �ǹ��ϴ� ������ Ư���� ���� ����Ұǵ� INT_MAX��� ���� ����� ���̴�.
	// INT_MAX�� �̹� ���ǵǾ��ִ� ������ int�� ǥ���� �� �ִ� �ִ밪�̴�.

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
		// �� Ǯ��
		/*for (int i = 0; i < 25; i++) {
			if (i % 5 == 0) {
				cout << endl;
			}
			cout << iNumber[i] << '\t';
		}*/

		// ���� Ǯ��
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

		// ���� ���߾����� Ȯ��
		bool bWin = true;

		for (int i = 0; i < 24; i++) {
			if (iNumber[i] != i + 1) {
				bWin = false;
				break;
			}
		}

		if (bWin == true) {
			cout << "���ڸ� ��� ������ϴ�" << endl;
			break;
		}

		cout << "| w : �� | s : �Ʒ� | a : ���� | d : ������ | q : ���� |" << endl;
		// _getch() �Լ��� ���� 1���� �Է¹޴� �Լ��̴�.
		// �� �Լ��� enter�� ġ�� �ʴ��� ���ڸ� ������ ���� �ٷ� �� ���ڸ� ��ȯ�ϰ� �����Ѵ�.
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

	cout << "������ �����մϴ�." << endl;
	return 0;
}