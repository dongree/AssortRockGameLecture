#include <iostream>

using namespace std;

int main() {

	/*
	�迭 : ���� ���� ������ �ѹ��� �������� �� �ִ� ����̴�.
	*/

	// �迭 0���� �ʱ�ȭ
	int array[10] = {};

	for (int i = 0; i < 10; i++) {
		cout << array[i] << endl;
	}

	int array2[10][10] = { {1,2,3} ,{4,5,6} };

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << array2[i][j] << '\t';
		}
		cout << endl;
	}

	return 0;
}