#include <iostream>

using namespace std;

enum MAIN_MENU {
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_SEARCH,
	MM_OUTPUT,
	MM_EXIT
	
};


#define NAME_SIZE 32


typedef struct Student {
	char name[NAME_SIZE];
	int number;
	int korScore;
	int engScore;
	int mathScore;
	int total;
	float avg;
}STUDENT, *PSTUDENT;


/*
링크드리스트 : 자료구조의 한 종류이다. 자료구조란 데이터를 관리하는 방법을 말한다.
링크드리스트는 데이터 목록을 연결시켜서 접근할 수 있는 구조를 제공한다.
링크드리스트는 데이터를 저장하기 위한 노드라는 것이 존재한다. 각 노드의 특징은
다음 노드를 알 수 있게 된다.(다음노드의 메모리 주소를 저장한다는 의미이다.)
리스트는 선형구조로 되어있다. 그렇기 때문에 배열처럼 특정 요소에 바로 접근이 불가능하다.
무조건 앞에서부터 차례대로 타고 들어가야 한다.
노드를 새로 추가할 때는 노드를 생성하고 마지막 노드에 연결만 해주면 되기 때문에 개수의 제한이 없다.
*/


// 리스트 노드를 만든다.
typedef struct Node {
	STUDENT student;
	Node* pNext;
} NODE, *PNODE;

// 리스트 구조체를 만들어준다.
typedef struct List {
	PNODE begin;
	PNODE end;
	int size;
} LIST, *PLIST;

int inputInt() {
	int input;
	cin >> input;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;
	}

	return input;
}

void inputString(char* pString, int size) {
	cin.clear();
	cin.ignore(1024, '\n');
	cin.getline(pString, size-1);
}

void initList(PLIST pList) {
	pList->begin = NULL;
	pList->end = NULL;
	pList->size = 0;
}

int outputMenu() {
	system("cls");
	cout << "1. 학생추가" << endl;
	cout << "2. 학생삭제" << endl;
	cout << "3. 학생탐색" << endl;
	cout << "4. 학생출력" << endl;
	cout << "5. 종료" << endl;
	cout << "메뉴를 선택하세요 : ";
	int input = inputInt();
	if (input <= MM_NONE || input >> MM_EXIT)
		return MM_NONE;
	
	return input;
}

void insert(PLIST pList) {
	system("cls");
	cout << "=========================== 학생추가 ===========================" << endl;
	STUDENT student = {};

	cout << "이름 : ";
	inputString(student.name, NAME_SIZE);

	cout << "학번 : ";
	student.number = inputInt();

	cout << "국어 : ";
	student.korScore = inputInt();

	cout << "영어 : ";
	student.engScore = inputInt();

	cout << "수학 : ";
	student.mathScore = inputInt();

	student.total = student.korScore + student.engScore + student.mathScore;
	student.avg = student.total / 3.f;

	// 추가할 리스트 노드를 생성한다.
	PNODE pNode = new NODE;

	// 현재 추가하는 노드는 가장 마지막에 추가될 것이기 때문에 다음 노드가 존재하지 않는다.
	// 그래서 다음 노드는 NULL로 초기화되고 정보는 위에서 입력받은 학생정보를 주도록 한다.
	pNode->pNext = NULL;
	pNode->student = student;

	if (pList->begin == NULL)
		pList->begin = pNode;
	else
		pList->end->pNext = pNode;

	pList->end = pNode;

	++pList->size;
}

void clearList(PLIST pList) {
	PNODE pNode = pList->begin;

	while (pNode != NULL) {
		PNODE pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}

	pList->begin = NULL;
	pList->end = NULL;
	pList->size = 0;
}

void outputStudent(const PSTUDENT pStudent) {
	cout << "이름 : " << pStudent->name << endl;
	cout << "학번 : " << pStudent->number << endl;
	cout << "국어 : " << pStudent->korScore << endl;
	cout << "영어 : " << pStudent->engScore << endl;
	cout << "수학 : " << pStudent->mathScore << endl;
	cout << "총점 : " << pStudent->total << endl;
	cout << "평균 : " << pStudent->avg << endl << endl;
	
}

void ouput(PLIST pList) {
	system("cls");
	cout << "=========================== 학생출력 ===========================" << endl;

	PNODE pNode = pList->begin;

	while (pNode != NULL) {
		outputStudent(&pNode->student);
		pNode = pNode->pNext;
	}

	cout << "학생 수 : " << pList->size << endl;
	system("pause");
}

void search(PLIST pList) {
	system("cls");
	cout << "=========================== 학생탐색 ===========================" << endl;
	
	cout << "탐색할 이름을 입력하세요 : ";
	char name[NAME_SIZE] = {};
	inputString(name, NAME_SIZE);

	PNODE pNode = pList->begin;

	while (pNode != NULL) {
		if (strcmp(pNode->student.name, name) == 0) {
			outputStudent(&pNode->student);
			system("pause");
			return;
		}
		pNode = pNode->pNext;
	}

	cout << "찾을 학생이 없습니다." << endl;
	system("pause");

}


void Delete(PLIST pList) {
	system("cls");
	cout << "=========================== 학생삭제 ===========================" << endl;

	cout << "삭제할 이름을 입력하세요 : ";
	char name[NAME_SIZE] = {};
	inputString(name, NAME_SIZE);

	PNODE pNode = pList->begin;
	PNODE pPrev = NULL;

	while (pNode != NULL) {
		if (strcmp(pNode->student.name, name) == 0) {
			PNODE pNext = pNode->pNext;
			// 만약 이전 노드가 NULL이라면 제일 첫번째 노드를 지운다는 의미
			if (pPrev == NULL) {
				delete pNode;
				pList->begin = pNext;
				if (pNext == NULL)
					pList->end = NULL;
			}
			// 이전 노드가 있을 경우에는 이전노드의 다음을 지운 노드의 다음노드로 연결해준다
			else {
				delete pNode;
				pPrev->pNext = pNext;

				if (pNext == NULL) 
					pList->end = pPrev;
				
			}

			cout << name << "학생 삭제완료!!" << endl;
			system("pause");
			pList->size--;
			return;
		}
		// 해당 학생이 아니라면 현
		pPrev = pNode;
		pNode = pNode->pNext;
	}

	cout << "삭제할 학생을 찾을 수 없습니다." << endl;
	system("pause");
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
			insert(&list);
			break;
		case MM_DELETE:
			Delete(&list);
			break;
		case MM_SEARCH:
			search(&list);
			break;
		case MM_OUTPUT:
			ouput(&list);
			break;
		}
	}


	return 0;
}