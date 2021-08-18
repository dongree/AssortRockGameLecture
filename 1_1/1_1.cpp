#include <iostream>
#include <time.h>

using namespace std;

/*
8강
열거체 : 연속된 숫자에 이름을 부여할 수 있는 기능이다.
열거체명을 이용해서 열거체 타입의 변수 선언도 가능하다.
즉, 열거체 자체가 사욪자지정 변수 타입이 될 수도 있다.
*/
enum NUM {
	NUM_0,		//아무것도 부여하지 않을 경우 0부터 1씩 차례로 값이 부여된다.
	NUM_1,
	NUM_2,
	NUM_3
};


int main() {
	/*
	1강
	std::cout << "Hello World" << std::endl;

	return 0;
	*/
	

	/*
	3강
	사칙 연산자 : +, -, *, /, %(나머지 연산자)
	관계 연산자 : <, <=, >, >=,  ==, !=		(값 대 값을 연산하여 참/거짓으로 결과를 반환한다.)
	논리 연산자 : AND(&&), OR(||), NOT(!)	(참/거짓 대 참/거짓을 연산하여 참/거짓으로 결과를 반환한다.)

	4강
	진수 : 2진수, 8진수, 10진수, 16진수
	2진수 : 0 ~ 1
	8진수 : 0 ~ 7
	10진수 : 0 ~ 9
	16진수 0 ~ 15 : 0 ~ f
	진수들은 서로 다른 진수로 변환이 가능하다.


	87을 2진수, 16진수로 변환해보자.
	2진수로 변환 :
	87 / 2 = 43		- 1
	43 / 2 = 21		- 1
	21 / 2 = 10		- 1
	10 / 2 = 5		- 0
	5 / 2 = 2		- 1
	2 / 2 = 1		- 0
	1 / 2 = 1		- 1

	1010111

	16진수로 변환
	101 0111  ->  57

	비트단위 논리연산자 : 2진수 단위의 연산을 한다. 값 대 값을 연산하여 값으로 나온다.
	종류 : AND(&), OR(|), NOT(~), XOR(^)
	A B XOR
	0 0 0
	1 0 1
	0 1 1
	1 1 0
	
	*/



	/*
	5강
	*/
	const int iAttack = 0x00000001;		// 1
	const int iArmor = 0x00000002;		// 10
	const int iHP = 0x00000004;			// 100
	const int iMP = 0x00000008;			// 1000
	const int iCritical = 0x00000010;	// 10000

	// 001 | 100 = 101    00101 | 10000 = 10101 
	// -> OR연산을 이용해서 각 비트를 킬 수 있다.
	int iBuf = iAttack | iHP | iCritical;

	// AND연산을 이용해서 각 비트들이 켜져있는지 꺼져있는지 알 수 있다.
	// 10101 & 00001 = 1
	cout << "Attack : " << (iBuf & iAttack) << endl;

	// 10101 & 00010 = 0
	cout << "Armor : " << (iBuf & iArmor) << endl;

	// XOR연산을 이용해서 껐다 켰다 스위치 기능
	// 10101 ^ 00100 = 10001
	iBuf ^= iHP;

	// 10101 ^ 00100 = 10101
	iBuf ^= iHP;
	
	/*
	쉬프트 연산자 : <<, >> 값 대 값을 연산하여 값으로 나오게 된다.
	20 << 2 = 80
	1010000

	20 << 3 = 160
	10100000

	20 << 4 = 320
	101000000
	
	20과 2의 x승을 곱한 것과 같다.

	<<를 빠른 곱하기라고도 부른다.
	


	20 >> 2 = 5 
	101

	20 >> 3 = 2
	10

	20 >> 4 = 1
	1

	20을 2의 x승을 나눈 것과 같다.

	>>를 빠른 나누기라고도 부른다.
	*/
	

	// 증감연산자 : ++, --


	/*
	6강
	분기문에는 크게 2가지 종류가 있다. if문, switch문이 존재한다.
	*/
	if (true)
	{
		cout << "if문 조건이 true 입니다" << endl;
	}

	if ((iBuf & iAttack) != 0)
		cout << "Attack 버프가 있습니다." << endl;

	if ((iBuf & iArmor) != 0)
		cout << "Armor 버프가 있습니다." << endl;

	if ((iBuf & iHP) != 0)
		cout << "HP 버프가 있습니다." << endl;

	if ((iBuf & iMP) != 0)
		cout << "MP 버프가 있습니다." << endl;

	if ((iBuf & iCritical) != 0)
		cout << "Critical 버프가 있습니다." << endl;


	/*
	7강
	난수 발생
	*/

	srand((unsigned int)time(0));

	cout << rand()%100 << endl;
	cout << rand()%100 << endl;
	cout << rand()%100 << endl;
	cout << (rand() % 101 + 100) << endl;		// 100 ~ 200
	cout << rand() % 10000 / 100.0 << endl;		// 0 ~ 99.99


	//int iUpgrade = 0;
	//cout << "Upgrade 기본 수치를 입력하세요 : ";
	//cin >> iUpgrade;


	//// 강화 확률을 구한다.
	//float fPercent = rand() % 10000 / 100.f;

	// 강화 확률 : 업그레이드가 0~3 : 100% 성공   4~6 : 40%    7~9 : 10%    10~13 : 1%  14~15 " 0.01%

	//cout << "Upgrade : " << iUpgrade << endl;
	//cout << "Percent : " << fPercent << endl;

	//if (iUpgrade <= 3)
	//	cout << "강화 성공" << endl;
	//else if (4 <= iUpgrade && iUpgrade <= 6) {
	//	if (fPercent < 40.f)
	//		cout << "강화 성공" << endl;
	//	else
	//		cout << "강화 실패" << endl;
	//}
	//else if (7 <= iUpgrade && iUpgrade <= 9) {
	//	if (fPercent < 10.f)
	//		cout << "강화 성공" << endl;
	//	else
	//		cout << "강화 실패" << endl;
	//}
	//else if (10 <= iUpgrade && iUpgrade <= 13) {
	//	if (fPercent < 1.f)
	//		cout << "강화 성공" << endl;
	//	else
	//		cout << "강화 실패" << endl;
	//}
	//else if (14 <= iUpgrade && iUpgrade <= 15) {
	//	if (fPercent < 0.01f)
	//		cout << "강화 성공" << endl;
	//	else
	//		cout << "강화 실패" << endl;
	//}

	/*
	8강
	switch문
	if문이 조건을 체크하는 분기문이라면 switch문은 값이 뭔지를 체크하는 분기문이다.
	형태 : switch(변수) {} 의 형태로 구성된다.
	*/
	/*int iNumber;
	cout << "숫자를 입력하세요 : ";
	cin >> iNumber;

	switch (iNumber) {
	case NUM_1:
		cout << "입력한 숫자는 1입니다." << endl;
		break;
	case NUM_2:
		cout << "입력한 숫자는 2입니다." << endl;
		break;
	case NUM_3:
		cout << "입력한 숫자는 3입니다." << endl;
		break;
	default:
		cout << "그 외의 숫자입니다." << endl;
		break;
	}*/


	
}

