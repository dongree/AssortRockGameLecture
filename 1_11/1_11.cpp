#include <iostream>

using namespace std;

int main() {

	/*
	배열 : 여러 개의 변수를 한번에 생성해줄 수 있는 기능이다.
	*/

	// 배열 0으로 초기화
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