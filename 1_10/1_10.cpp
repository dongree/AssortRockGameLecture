#include <iostream>

using namespace std;

int main() {
	/*
	for��
	���� : for(�ʱⰪ; ���ǽ�; ������) {}
	*/

	for (int i = 0; i < 10; i++) {
		cout << i << endl;
	}

	// ������ 2��
	for (int i = 1; i < 10; i++) {
		cout << "2 x " << i << " = " << 2 * i << endl;
	}

	// 1~100 ������ �� �� ¦���� ���
	for (int i = 2; i < 101; i += 2) {
		cout << i << endl;
	}

	// 1~100 ������ ���� �� 3�� 7�� ������� ����ϴ� if���� ������.
	for (int i = 1; i <= 100; i++) {
		if (i % 3 == 0 && i % 7 == 0) {
			cout << i << endl;
		}
	}

	// ��ø for��
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << "i = " << i << " j = " << j << endl;
		}
	}
	
	
	//// ����1 : �������� 2�ܺ��� 9�ܱ��� ����ϴ� ��ø for�� ������

	//for (int i = 2; i < 10; i++) {
	//	cout << i << "��" << endl;
	//	for (int j = 1; j < 10; j++) {
	//		cout << i << " X " << j << " = " << i * j << endl;
	//	}
	//}

	///* 
	//����2: ���� �Ʒ��� ���·� ��µǰ� �Ѵ�.
	//*
	//**
	//***
	//****
	//*****
	// 
	//����3: ���� �Ʒ��� ���·� ��µǰ� �Ѵ�.
	//*****
	//****
	//***
	//**
	//*

	//����4: ���� �Ʒ��� ���·� ��µǰ� �Ѵ�.
	//   *
	//  ***
	// *****
	//*******
	//*/
	//
	//for (int i = 1; i < 6; i++) {
	//	for (int j = 0; j < i; j++) {
	//		cout << "*";
	//	}
	//	cout << endl;
	//}

	//cout << endl;

	//for (int i = 5; i > 0; i--) {
	//	for (int j = 0; j < i; j++) {
	//		cout << "*";
	//	}
	//	cout << endl;
	//}

	//cout << endl;

	//for (int i = 1; i <= 7; i += 2) {
	//	for (int j = 0; j < (7-i)/2; j++) {
	//		cout << " ";
	//	}
	//	for (int j = 0; j < i; j++) {
	//		cout << "*";
	//	}
	//	cout << endl;
	//}


	/*
	2�� 3�� 4��
	5�� 6�� 7��
	8�� 9�� 10��
	*/
	for (int i = 2; i < 9; i+=3) {
		for (int j = 1; j < 10; j++) {

			for (int k = i; k < i+3; k++) {
				cout << k << " X " << j << " = " << k * j << '\t';
			}
			cout << endl;
		}
		cout << endl;
	}


	/*
	   *
	  ***
	 *****
	*******
	 *****
	  ***
	   *
	*/

	// �� Ǯ��
	/*for (int i = 0; i < 7; i++) {
		if (i <= 3) {
			for (int j = 0; j < 3-i; j++) {
				cout << " ";
			}
			for (int j = 0; j < i*2+1; j++) {
				cout << "*";
			}
			cout << endl;
		}
		else {
			for (int j = 0; j < i - 3; j++) {
				cout << " ";
			}
			for (int j = 0; j < (7-i) * 2 - 1; j++) {
				cout << "*";
			}
			cout << endl;
		}
	}*/


	// ���� Ǯ��
	int line = 7;
	int count = 0;

	for (int i = 0; i < line; i++){
		count = i;

		if (i > line / 2) {
			count = line - 1 - i;
		}

		for (int j = 0; j < line / 2 - count; j++) {
			cout << " ";
		}

		for (int j = 0; j < count * 2 + 1; j++ ) {
			cout << "*";
		}
		cout << endl;


	}


	/*
	11��
	do while��
	*/
	int a = 0;

	do
	{
		cout << a << endl;
	} while (a > 0);


	return 0;
}