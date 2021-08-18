#include <iostream>
#include <time.h>

using namespace std;

int main() {

	srand((unsigned int)time(0));

	int Lotto[45] = {};

	for (int i = 0; i < 45; i++) {
		Lotto[i] = i + 1;
	}

	// Shuffle
	int temp, idx1, idx2;

	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 45;
		idx2 = rand() % 45;

		temp = Lotto[idx1];
		Lotto[idx1] = Lotto[idx2];
		Lotto[idx2] = temp;
	}

	for (int i = 0; i < 6; i++) {
		cout << Lotto[i] << '\t';
	}

	cout << "보너스 번호 : " << Lotto[6] << endl;

	return 0;
}

