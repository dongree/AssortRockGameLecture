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
		9��
		�ݺ��� : Ư�� �۾��� �ݺ��ؼ� �������ִ� ����̴�.
		���� : for, while, do while
		*/

	int number = 0;

	system("cls");

	srand((unsigned int)time(0));
	int my;

	while (true) {
		int com = rand() % 3 + 1;

		cout << "1: ���� 2: ���� 3: �� 4: ����" << endl;
		cout << "���� �� �����ϼ���" << endl;
		cin >> my;

		if (my < Sissor || my > End) {
			cout << "���� �߸� �Է��Ͽ����ϴ�" << endl;
			continue;
		}
		else if (my == End) {
			break;
		}

		// ���� Ǯ�� -
		switch (com) {
		case 1:
			cout << "com : ����" << endl;
			break;
		case 2:
			cout << "com : ����" << endl;
			break;
		case 3:
			cout << "com : ��" << endl;
			break;
		}

		int win = my - com;
		if (win == 1 || win == -2)
			cout << "�¸�" << endl;
		else if (win == 0)
			cout << "���º�" << endl;
		else
			cout << "�й�" << endl;

		// �� Ǯ�� - �Ϲ����� Ǯ��
		/*else if (my == Sissor) {
			if (com == Sissor) {
				cout << "my : ���� com : ����   ���º��Դϴ�." << endl;
			}
			else if (com == Rock) {
				cout << "my : ���� com : ����   �й��Ͽ����ϴ�." << endl;
			}
			else if (com == Paper) {
				cout << "my : ���� com : ��   �¸��Ͽ����ϴ�." << endl;
			}
		}
		else if (my == Rock) {
			if (com == Sissor) {
				cout << "my : ���� com : ����   �¸��Ͽ����ϴ�." << endl;
			}
			else if (com == Rock) {
				cout << "my : ���� com : ����   ���º��Դϴ�." << endl;
			}
			else if (com == Paper) {
				cout << "my : ���� com : ��   �й��Ͽ����ϴ�." << endl;
			}
		}
		else if (my == Paper) {
			if (com == Sissor) {
				cout << "my : �� com : ����   �й��Ͽ����ϴ�." << endl;
			}
			else if (com == Rock) {
				cout << "my : �� com : ����   �¸��Ͽ����ϴ�." << endl;
			}
			else if (com == Paper) {
				cout << "my : �� com : ��   ���º��Դϴ�." << endl;
			}
		}*/



	}
}