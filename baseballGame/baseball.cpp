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

	// 숫자 설정
	int givenNum[3] = {};
	for (int i = 0; i < 3; i++) {
		givenNum[i] = nums[i];
	}

	cout << "[ 숫자 야구 게임 ]" << endl;
	cout << "*  *  *" << endl;
	int inputNum[3];
	int tryCount = 1;

	while (true) {
		// 사용자 입력
		cout << endl;
		cout << "세 자리 숫자를 입력하세요.(0 : 종료) ";
		cin >> inputNum[0] >> inputNum[1] >> inputNum[2];
		
		// 사용자 입력 예외처리
		if (inputNum[0] == 0 || inputNum[1] == 0 || inputNum[2] == 0)
			break;
		else if (inputNum[0] < 0 || inputNum[0] > 9 || inputNum[1] < 0 || inputNum[1] > 9 || inputNum[2] < 0 || inputNum[2] > 9) {
			cout << "잘못된 숫자를 입력하였습니다." << endl;
			continue;
		}
		else if (inputNum[0] == inputNum[1] || inputNum[0] == inputNum[2] || inputNum[1] == inputNum[2]) {
			cout << "중복된 숫자를 입력하였습니다." << endl;
			continue;
		}
		
		cout << "[" << tryCount << "번째 시도]" << endl;
		tryCount += 1;

		// strike, ball 계산
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

		// 결과 출력
		if (strikeCount == 0 && ballCount == 0) {
			cout << "out!" << endl;
		}
		else if (strikeCount == 3) {
			cout << tryCount-1 <<"번째 시도만에 성공하셨습니다!" << endl;
			break;
		}
		else {
			cout << "strike : " << strikeCount << "     ball : " << ballCount << endl;
		}
	}

	return 0;
}