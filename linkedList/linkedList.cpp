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
��ũ�帮��Ʈ : �ڷᱸ���� �� �����̴�. �ڷᱸ���� �����͸� �����ϴ� ����� ���Ѵ�.
��ũ�帮��Ʈ�� ������ ����� ������Ѽ� ������ �� �ִ� ������ �����Ѵ�.
��ũ�帮��Ʈ�� �����͸� �����ϱ� ���� ����� ���� �����Ѵ�. �� ����� Ư¡��
���� ��带 �� �� �ְ� �ȴ�.(��������� �޸� �ּҸ� �����Ѵٴ� �ǹ��̴�.)
����Ʈ�� ���������� �Ǿ��ִ�. �׷��� ������ �迭ó�� Ư�� ��ҿ� �ٷ� ������ �Ұ����ϴ�.
������ �տ������� ���ʴ�� Ÿ�� ���� �Ѵ�.
��带 ���� �߰��� ���� ��带 �����ϰ� ������ ��忡 ���Ḹ ���ָ� �Ǳ� ������ ������ ������ ����.
*/


// ����Ʈ ��带 �����.
typedef struct Node {
	STUDENT student;
	Node* pNext;
} NODE, *PNODE;

// ����Ʈ ����ü�� ������ش�.
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
	cout << "1. �л��߰�" << endl;
	cout << "2. �л�����" << endl;
	cout << "3. �л�Ž��" << endl;
	cout << "4. �л����" << endl;
	cout << "5. ����" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int input = inputInt();
	if (input <= MM_NONE || input >> MM_EXIT)
		return MM_NONE;
	
	return input;
}

void insert(PLIST pList) {
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

	// �߰��� ����Ʈ ��带 �����Ѵ�.
	PNODE pNode = new NODE;

	// ���� �߰��ϴ� ���� ���� �������� �߰��� ���̱� ������ ���� ��尡 �������� �ʴ´�.
	// �׷��� ���� ���� NULL�� �ʱ�ȭ�ǰ� ������ ������ �Է¹��� �л������� �ֵ��� �Ѵ�.
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
	cout << "�̸� : " << pStudent->name << endl;
	cout << "�й� : " << pStudent->number << endl;
	cout << "���� : " << pStudent->korScore << endl;
	cout << "���� : " << pStudent->engScore << endl;
	cout << "���� : " << pStudent->mathScore << endl;
	cout << "���� : " << pStudent->total << endl;
	cout << "��� : " << pStudent->avg << endl << endl;
	
}

void ouput(PLIST pList) {
	system("cls");
	cout << "=========================== �л���� ===========================" << endl;

	PNODE pNode = pList->begin;

	while (pNode != NULL) {
		outputStudent(&pNode->student);
		pNode = pNode->pNext;
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

	PNODE pNode = pList->begin;

	while (pNode != NULL) {
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

	PNODE pNode = pList->begin;
	PNODE pPrev = NULL;

	while (pNode != NULL) {
		if (strcmp(pNode->student.name, name) == 0) {
			PNODE pNext = pNode->pNext;
			// ���� ���� ��尡 NULL�̶�� ���� ù��° ��带 ����ٴ� �ǹ�
			if (pPrev == NULL) {
				delete pNode;
				pList->begin = pNext;
				if (pNext == NULL)
					pList->end = NULL;
			}
			// ���� ��尡 ���� ��쿡�� ��������� ������ ���� ����� �������� �������ش�
			else {
				delete pNode;
				pPrev->pNext = pNext;

				if (pNext == NULL) 
					pList->end = pPrev;
				
			}

			cout << name << "�л� �����Ϸ�!!" << endl;
			system("pause");
			pList->size--;
			return;
		}
		// �ش� �л��� �ƴ϶�� ��
		pPrev = pNode;
		pNode = pNode->pNext;
	}

	cout << "������ �л��� ã�� �� �����ϴ�." << endl;
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