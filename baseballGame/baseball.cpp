#include <iostream>
#include <time.h>

using namespace std;

int main() {

	srand((unsigned int)time(0));

	int nums[9] = {};
	for (int i = 0; i < 9; i++) {
		nums[i] = i + 1;
	}

	// Shuffle
	int idx1, idx2, temp;
	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 9;
		idx2 = rand() % 9;

		temp = nums[idx1];
		nums[idx1] = nums[idx2];
		nums[idx2] = temp;
	}

	// ���� ����
	int givenNum[3] = {};
	for (int i = 0; i < 3; i++) {
		givenNum[i] = nums[i];
	}

	cout << "[ ���� �߱� ���� ]" << endl;
	cout << "*  *  *" << endl;
	int inputNum[3];
	int tryCount = 1;

	while (true) {
		// ����� �Է�
		cout << endl;
		cout << "�� �ڸ� ���ڸ� �Է��ϼ���.(0 : ����) ";
		cin >> inputNum[0] >> inputNum[1] >> inputNum[2];
		
		// ����� �Է� ����ó��
		if (inputNum[0] == 0 || inputNum[1] == 0 || inputNum[2] == 0)
			break;
		else if (inputNum[0] < 0 || inputNum[0] > 9 || inputNum[1] < 0 || inputNum[1] > 9 || inputNum[2] < 0 || inputNum[2] > 9) {
			cout << "�߸��� ���ڸ� �Է��Ͽ����ϴ�." << endl;
			continue;
		}
		else if (inputNum[0] == inputNum[1] || inputNum[0] == inputNum[2] || inputNum[1] == inputNum[2]) {
			cout << "�ߺ��� ���ڸ� �Է��Ͽ����ϴ�." << endl;
			continue;
		}
		
		cout << "[" << tryCount << "��° �õ�]" << endl;
		tryCount += 1;

		// strike, ball ���
		int strikeCount = 0;
		int ballCount = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (givenNum[i] == inputNum[j]) {
					if (i == j)
						strikeCount += 1;
					else {
						ballCount += 1;
					}
				}
			}
		}

		// ��� ���
		if (strikeCount == 0 && ballCount == 0) {
			cout << "out!" << endl;
		}
		else if (strikeCount == 3) {
			cout << tryCount-1 <<"��° �õ����� �����ϼ̽��ϴ�!" << endl;
			break;
		}
		else {
			cout << "strike : " << strikeCount << "     ball : " << ballCount << endl;
		}
	}

	return 0;
}