#include <iostream>

using namespace std;

// Call by Value
int sum(int a, int b) {
	return a + b;
}

void outputText() {
	cout << "outputText function" << endl;
}


void changeNumber(int num) {
	num = 1111;
}

/*
함수의 오버로딩 : 같은 이름의 함수지만 기능이 다르던가 인자가 다른 함수를 말한다.
오버로딩의 조건 : 함수 이름이 무조건 같아야 한다. 단, 인자의 개수 혹은 타입이 달라야 오버로딩이 성립이 된다.
반환타입은 오버로딩에 영향을 주지 않는다.
*/

// Call by address
void changeNumber(int *num) {
	*num = 9999;
}

// 함수의 디폴트인자
// 디폴트 인자는 가장 오른쪽부터 지정해주어야 한다.

void output(int num1, int num2 = 10) {
	cout << num1 << endl;
	cout << num2 << endl;
}


int main() {

	cout << sum(10, 20) << endl;
	cout << sum(102, 304) << endl;
	cout << sum(50, 123) << endl;

	outputText();
	outputText();

	int a = 3;
	changeNumber(a);
	cout << a << endl;


	changeNumber(&a);

	cout << a << endl;


	output(30);

	return 0;
}