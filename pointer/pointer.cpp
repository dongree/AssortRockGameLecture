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
	포인터 : 가리키다. 일반 변수는 일반적인 값을 저장하게 되지만
	포인터 변수는 메모리 주소를 저장하게 된다. 모든 변수 타입은 포인터 타입을 선언할 수 있다.
	int변수의 주소는 int 포인터 변수에 저장을 해야한다.
	포인터는 메모리 주소를 담아놓는 변수이기 때문에
	x86으로 개발할 때는 무조건 4byte가 나온다.
	x64일 때는 8byte가 나온다.

	포인터는 자기 스스로 아무런 일도 할 수 없다. 반드시 다른 변수의 메무리
	주소를 가지고 있어야 일을 할 수 있는데 가지고 있는 그 메모리 주소에
	접근해서 값을 제어할 수 있다.

	형태 : 변수타입 * 변수명; 의 형태로 선언한다.

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
	포인터와 배열의 관계 : 배열명은 포인터다.
	*/

	int iArray[10] = { 1,2,3,4,5,6,7,8,9,10 };

	cout << "array address : " << iArray << endl;
	cout << "array address : " << &iArray << endl;

	int* pArray = iArray;

	cout << pArray[2] << endl;

	/*
	포인터 연산
	*/

	cout << *(pArray + 2) << endl;
	cout << *(pArray)+ 100 << endl;


	// char pointer
	const char* pText = "문자열";

	cout << pText << endl;
	cout << (int*)pText << endl;

	pText = "abcd";

	cout << pText << endl;
	cout << (int*)pText << endl;


	// 구조체 pointer

	Student student = { };

	student.kor = 100;
	Student* pStudent = &student;

	// 연산자 우선순위 때문에 .을 먼저 인식하게 된다.
	(*pStudent).kor = 50;

	pStudent->kor = 80;

	cout << student.kor << endl;

	// void pointer
	// void* 변수를 선언하게 되면 이 변수는 어떤 타입의 메모리 주소든 모두 저장가능하다.
	// 단 역참조가 불가능하고 메모리 주소만 저장 가능하다.

	void* pVoid = &num;
	cout << "num Address : " << pVoid <<endl;

	pVoid = &student;
	cout << "student Adress : " << pVoid << endl;


	// 이중 포인터
	// 포인터의 포인터, 즉 포인터 변수의 메모리 주소를 저장하는 푕ㄴ터
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