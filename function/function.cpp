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
�Լ��� �����ε� : ���� �̸��� �Լ����� ����� �ٸ����� ���ڰ� �ٸ� �Լ��� ���Ѵ�.
�����ε��� ���� : �Լ� �̸��� ������ ���ƾ� �Ѵ�. ��, ������ ���� Ȥ�� Ÿ���� �޶�� �����ε��� ������ �ȴ�.
��ȯŸ���� �����ε��� ������ ���� �ʴ´�.
*/

// Call by address
void changeNumber(int *num) {
	*num = 9999;
}

// �Լ��� ����Ʈ����
// ����Ʈ ���ڴ� ���� �����ʺ��� �������־�� �Ѵ�.

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