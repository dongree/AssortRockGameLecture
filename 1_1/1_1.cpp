#include <iostream>
#include <time.h>

using namespace std;

/*
8��
����ü : ���ӵ� ���ڿ� �̸��� �ο��� �� �ִ� ����̴�.
����ü���� �̿��ؼ� ����ü Ÿ���� ���� ���� �����ϴ�.
��, ����ü ��ü�� ��B������ ���� Ÿ���� �� ���� �ִ�.
*/
enum NUM {
	NUM_0,		//�ƹ��͵� �ο����� ���� ��� 0���� 1�� ���ʷ� ���� �ο��ȴ�.
	NUM_1,
	NUM_2,
	NUM_3
};


int main() {
	/*
	1��
	std::cout << "Hello World" << std::endl;

	return 0;
	*/
	

	/*
	3��
	��Ģ ������ : +, -, *, /, %(������ ������)
	���� ������ : <, <=, >, >=,  ==, !=		(�� �� ���� �����Ͽ� ��/�������� ����� ��ȯ�Ѵ�.)
	�� ������ : AND(&&), OR(||), NOT(!)	(��/���� �� ��/������ �����Ͽ� ��/�������� ����� ��ȯ�Ѵ�.)

	4��
	���� : 2����, 8����, 10����, 16����
	2���� : 0 ~ 1
	8���� : 0 ~ 7
	10���� : 0 ~ 9
	16���� 0 ~ 15 : 0 ~ f
	�������� ���� �ٸ� ������ ��ȯ�� �����ϴ�.


	87�� 2����, 16������ ��ȯ�غ���.
	2������ ��ȯ :
	87 / 2 = 43		- 1
	43 / 2 = 21		- 1
	21 / 2 = 10		- 1
	10 / 2 = 5		- 0
	5 / 2 = 2		- 1
	2 / 2 = 1		- 0
	1 / 2 = 1		- 1

	1010111

	16������ ��ȯ
	101 0111  ->  57

	��Ʈ���� �������� : 2���� ������ ������ �Ѵ�. �� �� ���� �����Ͽ� ������ ���´�.
	���� : AND(&), OR(|), NOT(~), XOR(^)
	A B XOR
	0 0 0
	1 0 1
	0 1 1
	1 1 0
	
	*/



	/*
	5��
	*/
	const int iAttack = 0x00000001;		// 1
	const int iArmor = 0x00000002;		// 10
	const int iHP = 0x00000004;			// 100
	const int iMP = 0x00000008;			// 1000
	const int iCritical = 0x00000010;	// 10000

	// 001 | 100 = 101    00101 | 10000 = 10101 
	// -> OR������ �̿��ؼ� �� ��Ʈ�� ų �� �ִ�.
	int iBuf = iAttack | iHP | iCritical;

	// AND������ �̿��ؼ� �� ��Ʈ���� �����ִ��� �����ִ��� �� �� �ִ�.
	// 10101 & 00001 = 1
	cout << "Attack : " << (iBuf & iAttack) << endl;

	// 10101 & 00010 = 0
	cout << "Armor : " << (iBuf & iArmor) << endl;

	// XOR������ �̿��ؼ� ���� �״� ����ġ ���
	// 10101 ^ 00100 = 10001
	iBuf ^= iHP;

	// 10101 ^ 00100 = 10101
	iBuf ^= iHP;
	
	/*
	����Ʈ ������ : <<, >> �� �� ���� �����Ͽ� ������ ������ �ȴ�.
	20 << 2 = 80
	1010000

	20 << 3 = 160
	10100000

	20 << 4 = 320
	101000000
	
	20�� 2�� x���� ���� �Ͱ� ����.

	<<�� ���� ���ϱ��� �θ���.
	


	20 >> 2 = 5 
	101

	20 >> 3 = 2
	10

	20 >> 4 = 1
	1

	20�� 2�� x���� ���� �Ͱ� ����.

	>>�� ���� �������� �θ���.
	*/
	

	// ���������� : ++, --


	/*
	6��
	�б⹮���� ũ�� 2���� ������ �ִ�. if��, switch���� �����Ѵ�.
	*/
	if (true)
	{
		cout << "if�� ������ true �Դϴ�" << endl;
	}

	if ((iBuf & iAttack) != 0)
		cout << "Attack ������ �ֽ��ϴ�." << endl;

	if ((iBuf & iArmor) != 0)
		cout << "Armor ������ �ֽ��ϴ�." << endl;

	if ((iBuf & iHP) != 0)
		cout << "HP ������ �ֽ��ϴ�." << endl;

	if ((iBuf & iMP) != 0)
		cout << "MP ������ �ֽ��ϴ�." << endl;

	if ((iBuf & iCritical) != 0)
		cout << "Critical ������ �ֽ��ϴ�." << endl;


	/*
	7��
	���� �߻�
	*/

	srand((unsigned int)time(0));

	cout << rand()%100 << endl;
	cout << rand()%100 << endl;
	cout << rand()%100 << endl;
	cout << (rand() % 101 + 100) << endl;		// 100 ~ 200
	cout << rand() % 10000 / 100.0 << endl;		// 0 ~ 99.99


	//int iUpgrade = 0;
	//cout << "Upgrade �⺻ ��ġ�� �Է��ϼ��� : ";
	//cin >> iUpgrade;


	//// ��ȭ Ȯ���� ���Ѵ�.
	//float fPercent = rand() % 10000 / 100.f;

	// ��ȭ Ȯ�� : ���׷��̵尡 0~3 : 100% ����   4~6 : 40%    7~9 : 10%    10~13 : 1%  14~15 " 0.01%

	//cout << "Upgrade : " << iUpgrade << endl;
	//cout << "Percent : " << fPercent << endl;

	//if (iUpgrade <= 3)
	//	cout << "��ȭ ����" << endl;
	//else if (4 <= iUpgrade && iUpgrade <= 6) {
	//	if (fPercent < 40.f)
	//		cout << "��ȭ ����" << endl;
	//	else
	//		cout << "��ȭ ����" << endl;
	//}
	//else if (7 <= iUpgrade && iUpgrade <= 9) {
	//	if (fPercent < 10.f)
	//		cout << "��ȭ ����" << endl;
	//	else
	//		cout << "��ȭ ����" << endl;
	//}
	//else if (10 <= iUpgrade && iUpgrade <= 13) {
	//	if (fPercent < 1.f)
	//		cout << "��ȭ ����" << endl;
	//	else
	//		cout << "��ȭ ����" << endl;
	//}
	//else if (14 <= iUpgrade && iUpgrade <= 15) {
	//	if (fPercent < 0.01f)
	//		cout << "��ȭ ����" << endl;
	//	else
	//		cout << "��ȭ ����" << endl;
	//}

	/*
	8��
	switch��
	if���� ������ üũ�ϴ� �б⹮�̶�� switch���� ���� ������ üũ�ϴ� �б⹮�̴�.
	���� : switch(����) {} �� ���·� �����ȴ�.
	*/
	/*int iNumber;
	cout << "���ڸ� �Է��ϼ��� : ";
	cin >> iNumber;

	switch (iNumber) {
	case NUM_1:
		cout << "�Է��� ���ڴ� 1�Դϴ�." << endl;
		break;
	case NUM_2:
		cout << "�Է��� ���ڴ� 2�Դϴ�." << endl;
		break;
	case NUM_3:
		cout << "�Է��� ���ڴ� 3�Դϴ�." << endl;
		break;
	default:
		cout << "�� ���� �����Դϴ�." << endl;
		break;
	}*/


	
}

