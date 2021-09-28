// #paragma once : �� ��������� �� 1�ո� ���Խ�Ű�ڴ� ��� �ǹ��̴�.
#pragma once

#include <iostream>

using namespace std;

enum OUTPUT_TYPE {
	OT_NONE,
	OT_OUTPUT,
	OT_INVERSE
};

// ������Ͽ��� ���� �Լ� ����κ��� ������ش�.
#define NAME_SIZE 32

typedef struct Student {
	char name[NAME_SIZE];
	int number;
	int korScore;
	int engScore;
	int mathScore;
	int total;
	float avg;
}STUDENT, * PSTUDENT;


// ����Ʈ ��带 �����.
typedef struct Node {
	STUDENT student;
	Node* pNext;
	Node* pPrev;
} NODE, * PNODE;

// ����Ʈ ����ü�� ������ش�.
typedef struct List {
	// begin�� end�� ��������� ó���� ���� �ǹ��ϵ��� �����. ���� �����͸� �����ϴ�
	// ���� �ƴϴ�. ���� �����͸� �����ϴ� ���� begin�� end���̿� �����ϰ� ������ش�.
	PNODE begin;
	PNODE end;
	int size;
} LIST, * PLIST;


static int inputInt() {
	int input;
	cin >> input;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;
	}

	return input;
}

static void inputString(char* pString, int size) {
	cin.clear();
	cin.ignore(1024, '\n');
	cin.getline(pString, size - 1);
}

void initList(PLIST pList);
//void clearList(PLIST pList);
void destroyList(PLIST pList);
void push_back(PLIST pList);
void push_front(PLIST pList);
void outputStudent(const PSTUDENT pStudent);
void output(PLIST pList);
void search(PLIST pList);
void Delete(PLIST pList);