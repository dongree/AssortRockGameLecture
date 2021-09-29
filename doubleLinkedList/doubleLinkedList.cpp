#include "List.h"

using namespace std;

enum MAIN_MENU {
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_SEARCH,
	MM_OUTPUT,
	MM_SORT,
	MM_EXIT

};


int outputMenu() {
	system("cls");
	cout << "1. 학생추가" << endl;
	cout << "2. 학생삭제" << endl;
	cout << "3. 학생탐색" << endl;
	cout << "4. 학생출력" << endl;
	cout << "5. 학생정렬" << endl;
	cout << "6. 종료" << endl;
	cout << "메뉴를 선택하세요 : ";
	int input = inputInt();
	if (input <= MM_NONE || input >> MM_EXIT)
		return MM_NONE;

	return input;
}


int main() {
	List list;

	initList(&list);

	while (true) {
		int menu = outputMenu();
		if (menu == MM_EXIT)
			break;

		switch (menu)
		{
		case MM_INSERT:
			push_back(&list);
			break;
		case MM_DELETE:
			Delete(&list);
			break;
		case MM_SEARCH:
			search(&list);
			break;
		case MM_OUTPUT:
			output(&list);
			break;
		case MM_SORT:
			sort(&list);
			break;
		}

	}
	
	destroyList(&list);

	return 0;
}