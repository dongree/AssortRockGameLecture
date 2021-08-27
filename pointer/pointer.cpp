#include <iostream>

using namespace std;

struct Student {
	int kor;
	int eng;
	int math;
	int total;
	float avg;
};


int main() {
	/*
	������ : ����Ű��. �Ϲ� ������ �Ϲ����� ���� �����ϰ� ������
	������ ������ �޸� �ּҸ� �����ϰ� �ȴ�. ��� ���� Ÿ���� ������ Ÿ���� ������ �� �ִ�.
	int������ �ּҴ� int ������ ������ ������ �ؾ��Ѵ�.
	�����ʹ� �޸� �ּҸ� ��Ƴ��� �����̱� ������
	x86���� ������ ���� ������ 4byte�� ���´�.
	x64�� ���� 8byte�� ���´�.

	�����ʹ� �ڱ� ������ �ƹ��� �ϵ� �� �� ����. �ݵ�� �ٸ� ������ �޹���
	�ּҸ� ������ �־�� ���� �� �� �ִµ� ������ �ִ� �� �޸� �ּҿ�
	�����ؼ� ���� ������ �� �ִ�.

	���� : ����Ÿ�� * ������; �� ���·� �����Ѵ�.

	*/

	int num = 100;
	int* pNum = &num;

	cout << sizeof(int*) << endl;
	cout << sizeof(char*) << endl;
	cout << sizeof(double*) << endl;

	cout << "number address : " << &num << endl;
	cout << "pNum value : " << pNum << endl;
	cout << "pNum address : " << &pNum << endl;
	cout << *pNum << endl;

	/*
	�����Ϳ� �迭�� ���� : �迭���� �����ʹ�.
	*/

	int iArray[10] = { 1,2,3,4,5,6,7,8,9,10 };

	cout << "array address : " << iArray << endl;
	cout << "array address : " << &iArray << endl;

	int* pArray = iArray;

	cout << pArray[2] << endl;

	/*
	������ ����
	*/

	cout << *(pArray + 2) << endl;
	cout << *(pArray)+ 100 << endl;


	// char pointer
	const char* pText = "���ڿ�";

	cout << pText << endl;
	cout << (int*)pText << endl;

	pText = "abcd";

	cout << pText << endl;
	cout << (int*)pText << endl;


	// ����ü pointer

	Student student = { };

	student.kor = 100;
	Student* pStudent = &student;

	// ������ �켱���� ������ .�� ���� �ν��ϰ� �ȴ�.
	(*pStudent).kor = 50;

	pStudent->kor = 80;

	cout << student.kor << endl;

	// void pointer
	// void* ������ �����ϰ� �Ǹ� �� ������ � Ÿ���� �޸� �ּҵ� ��� ���尡���ϴ�.
	// �� �������� �Ұ����ϰ� �޸� �ּҸ� ���� �����ϴ�.

	void* pVoid = &num;
	cout << "num Address : " << pVoid <<endl;

	pVoid = &student;
	cout << "student Adress : " << pVoid << endl;


	// ���� ������
	// �������� ������, �� ������ ������ �޸� �ּҸ� �����ϴ� �b����
	int num1 = 1111;
	num = 2222;
	pNum = &num;

	int **ppNum = &pNum;

	*ppNum = &num1;
	*pNum = 3333;

	cout << "num1 : " << num1 << endl;
	cout << "num : " << num << endl;
	cout << "num address : " << &num << endl;
	cout << "*pNum : " << *pNum << endl;
	cout << "pNum value : " << pNum << endl;
	cout << "pNum address : " << &pNum << endl;
	cout << "*ppNum : " << *ppNum << endl;
	cout << "**PPNum : " << **ppNum << endl;
	cout << "ppNum value : " << ppNum << endl;
	cout << "ppNum address : " << &ppNum << endl;



	return 0;
}