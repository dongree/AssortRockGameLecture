// #paragma once : 이 헤더파일을 딱 1먼만 포함시키겠다 라는 의미이다.
#pragma once

#include <iostream>

using namespace std;

enum OUTPUT_TYPE {
	OT_NONE,
	OT_OUTPUT,
	OT_INVERSE
};

// 헤더파일에는 보통 함수 선언부분을 만들어준다.
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


// 리스트 노드를 만든다.
typedef struct Node {
	STUDENT student;
	Node* pNext;
	Node* pPrev;
} NODE, * PNODE;

// 리스트 구조체를 만들어준다.
typedef struct List {
	// begin과 end는 명시적으로 처음과 끝을 의미하도록 만든다. 실제 데이터를 저장하는
	// 노드는 아니다. 실제 데이터를 저장하는 노드는 begin과 end사이에 존재하게 만들어준다.
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