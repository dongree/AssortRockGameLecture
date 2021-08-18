#include <iostream>

using namespace std;

int main() {
	/*
	for문
	형태 : for(초기값; 조건식; 증감값) {}
	*/

	for (int i = 0; i < 10; i++) {
		cout << i << endl;
	}

	// 구구단 2단
	for (int i = 1; i < 10; i++) {
		cout << "2 x " << i << " = " << 2 * i << endl;
	}

	// 1~100 사이의 수 중 짝수만 출력
	for (int i = 2; i < 101; i += 2) {
		cout << i << endl;
	}

	// 1~100 사이의 숫자 중 3과 7의 공배수만 출력하는 if문을 만들어보자.
	for (int i = 1; i <= 100; i++) {
		if (i % 3 == 0 && i % 7 == 0) {
			cout << i << endl;
		}
	}

	// 중첩 for문
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << "i = " << i << " j = " << j << endl;
		}
	}
	
	
	//// 숙제1 : 구구단을 2단부터 9단까지 출력하는 중첩 for문 만들어보자

	//for (int i = 2; i < 10; i++) {
	//	cout << i << "단" << endl;
	//	for (int j = 1; j < 10; j++) {
	//		cout << i << " X " << j << " = " << i * j << endl;
	//	}
	//}

	///* 
	//숙제2: 별을 아래의 형태로 출력되게 한다.
	//*
	//**
	//***
	//****
	//*****
	// 
	//숙제3: 별을 아래의 형태로 출력되게 한다.
	//*****
	//****
	//***
	//**
	//*

	//숙제4: 별을 아래의 형태로 출력되게 한다.
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
	2단 3단 4단
	5단 6단 7단
	8단 9단 10단
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

	// 내 풀이
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


	// 영상 풀이
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
	11강
	do while문
	*/
	int a = 0;

	do
	{
		cout << a << endl;
	} while (a > 0);


	return 0;
}