#include "List.h"

void outputStudent(const PSTUDENT pStudent) {
	cout << "�̸� : " << pStudent->name << endl;
	cout << "�й� : " << pStudent->number << endl;
	cout << "���� : " << pStudent->korScore << endl;
	cout << "���� : " << pStudent->engScore << endl;
	cout << "���� : " << pStudent->mathScore << endl;
	cout << "���� : " << pStudent->total << endl;
	cout << "��� : " << pStudent->avg << endl << endl;
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
	cout << "=========================== �л��߰� ===========================" << endl;
	STUDENT student = {};

	cout << "�̸� : ";
	inputString(student.name, NAME_SIZE);

	cout << "�й� : ";
	student.number = inputInt();

	cout << "���� : ";
	student.korScore = inputInt();

	cout << "���� : ";
	student.engScore = inputInt();

	cout << "���� : ";
	student.mathScore = inputInt();

	student.total = student.korScore + student.engScore + student.mathScore;
	student.avg = student.total / 3.f;

	PNODE pNode = new NODE;

	pNode->student = student;

	// ���� �߰��Ǵ� ���� end����� �������� end��� ���̿� �߰��ؾ� �Ѵ�.
	// �׷��� end�� prev ��带 ���س��´�.
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
		cout << "=========================== �л���� ===========================" << endl;
		cout << "1. ������ ���" << endl;
		cout << "2. ������ ���" << endl;
		cout << "�޴��� �����ϼ��� : ";
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

	cout << "�л� �� : " << pList->size << endl;
	system("pause");
}

void search(PLIST pList) {
	system("cls");
	cout << "=========================== �л�Ž�� ===========================" << endl;

	cout << "Ž���� �̸��� �Է��ϼ��� : ";
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

	cout << "ã�� �л��� �����ϴ�." << endl;
	system("pause");

}

void Delete(PLIST pList) {
	system("cls");
	cout << "=========================== �л����� ===========================" << endl;

	cout << "������ �̸��� �Է��ϼ��� : ";
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

			cout << name << "�л� �����Ϸ�!!" << endl;
			system("pause");
			
			return;
		}
		
		pNode = pNode->pNext;
	}

	cout << "������ �л��� ã�� �� �����ϴ�." << endl;
	system("pause");
}