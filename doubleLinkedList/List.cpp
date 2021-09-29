#include "List.h"

void outputStudent(const PSTUDENT pStudent) {
	cout << "이름 : " << pStudent->name << endl;
	cout << "학번 : " << pStudent->number << endl;
	cout << "국어 : " << pStudent->korScore << endl;
	cout << "영어 : " << pStudent->engScore << endl;
	cout << "수학 : " << pStudent->mathScore << endl;
	cout << "총점 : " << pStudent->total << endl;
	cout << "평균 : " << pStudent->avg << endl << endl;
}

void initList(PLIST pList) {
	pList->size = 0;

	pList->begin = new NODE;
	pList->end = new NODE;

	pList->begin->pNext = pList->end;
	pList->end->pPrev = pList->begin;

	pList->begin->pPrev = NULL;
	pList->end->pNext = NULL;
}

void destroyList(PLIST pList)
{
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

void push_back(PLIST pList)
{
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

	PNODE pNode = new NODE;

	pNode->student = student;

	// 새로 추가되는 노드는 end노드의 이전노드와 end노드 사이에 추가해야 한다.
	// 그래서 end의 prev 노드를 구해놓는다.
	PNODE pPrev = pList->end->pPrev;

	pPrev->pNext = pNode;
	pNode->pPrev = pPrev;

	pNode->pNext = pList->end;
	pList->end->pPrev = pNode;

	pList->size++;
}

void push_front(PLIST pList)
{
}

void output(PLIST pList)
{	
	int menu;
	while (true) {
		system("cls");
		cout << "=========================== 학생출력 ===========================" << endl;
		cout << "1. 정방향 출력" << endl;
		cout << "2. 역방향 출력" << endl;
		cout << "메뉴를 선택하세요 : ";
		menu = inputInt();

		if (menu > OT_NONE && menu <= OT_INVERSE)
			break;
	}

	PNODE pNode = NULL;

	switch (menu) {
	case OT_OUTPUT:
		pNode = pList->begin->pNext;
		while (pNode != pList->end) {
			outputStudent(&pNode->student);
			pNode = pNode->pNext;
		}
		break;
	case OT_INVERSE:
		pNode = pList->end->pPrev;
		while (pNode != pList->begin) {
			outputStudent(&pNode->student);
			pNode = pNode->pPrev;
		}
		break;
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

	PNODE pNode = pList->begin->pNext;

	while (pNode != pList->end) {
		if (strcmp(pNode->student.name, name) == 0) {
			outputStudent(&pNode->student);
			system("pause");
			return;
		}
		pNode = pNode->pNext;
	}

	cout << "찾는 학생이 없습니다." << endl;
	system("pause");

}

void Delete(PLIST pList) {
	system("cls");
	cout << "=========================== 학생삭제 ===========================" << endl;

	cout << "삭제할 이름을 입력하세요 : ";
	char name[NAME_SIZE] = {};
	inputString(name, NAME_SIZE);

	PNODE pNode = pList->begin->pNext;

	while (pNode != pList->end) {
		if (strcmp(pNode->student.name, name) == 0) {
			PNODE pNext = pNode->pNext;
			pNode->pPrev->pNext = pNode->pNext;
			pNode->pNext->pPrev = pNode->pPrev;
			delete pNode;
			pList->size--;

			cout << name << "학생 삭제완료!!" << endl;
			system("pause");
			
			return;
		}
		
		pNode = pNode->pNext;
	}

	cout << "삭제할 학생을 찾을 수 없습니다." << endl;
	system("pause");
}

void sort(PLIST pList)
{
	int menu;
	system("cls");
	cout << "=========================== 학생정렬 ===========================" << endl;

	while (true) {
		cout << "1. 학번정렬" << endl;
		cout << "2. 점수정렬" << endl;
		cout << "번호를 입력해주세요 : ";
		menu = inputInt();
		if (menu > ST_NONE && menu <= ST_SCORE) {
			cout << "잘못 선택하였습니다." << endl;
			system("pause");
			return;
		}
	}
	
	PNODE pNode = pList->begin->pNext;
	PNODE pNext = NULL;

	switch(menu) {
	case ST_NUMBER:
		// 학번순으로 정렬
		for (int i = pList->size; i > 0 ; i--) {
			for (int j = 0; j < i-1; j++) {
				pNext = pNode->pNext; 
				if (pNode->student.number > pNext->student.number) {
					pNode->pNext = pNext->pNext;
					pNext->pPrev = pNode->pPrev;
					pNode->pPrev->pNext = pNext;
					pNode->pNext->pPrev = pNode;
					pNode->pPrev = pNext;
					pNext->pNext = pNode;
				}
				else {
					pNode = pNode->pNext;
				}
			}
			pNode = pList->begin->pNext;
		}

		break;
	case ST_SCORE:
		// 점수순으로 정렬
		for (int i = pList->size; i > 0; i--) {
			for (int j = 0; j < i - 1; j++) {
				pNext = pNode->pNext;
				if (pNode->student.total > pNext->student.total) {
					pNode->pNext = pNext->pNext;
					pNext->pPrev = pNode->pPrev;
					pNode->pPrev->pNext = pNext;
					pNode->pNext->pPrev = pNode;
					pNode->pPrev = pNext;
					pNext->pNext = pNode;
				}
				else {
					pNode = pNode->pNext;
				}
			}
			pNode = pList->begin->pNext;
		}
		break;
	}
	while (pNode != pList->end) {
		outputStudent(&pNode->student);
		pNode = pNode->pNext;
	}
	system("pause");
}
