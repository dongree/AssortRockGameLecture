#include <iostream>

using namespace std;

#define NAME_SIZE 32
#define ADDRESS_SIZE 128
#define PHONE_SIZE 14
#define STUDENT_MAX 10

struct Student {
	char name[NAME_SIZE];
	char address[ADDRESS_SIZE];
	char phoneNum[PHONE_SIZE];
	int number;
	int korScore;
	int engScore;
	int mathScore;
	int total;
	float avg;
};

enum MENU {
	MENU_NONE,
	MENU_INSERT,
	MENU_DELETE,
	MENU_SEARCH,
	MENU_OUTPUT,
	MENU_EXIT
};

int main() {

	Student studentArray[STUDENT_MAX] = {};
	int studentCount = 0;
	int studentNumber = 1;
	char searchName[NAME_SIZE] = {};

	while (true) {
		system("cls");

		cout << "1. 학생등록" << endl;
		cout << "2. 학생삭제" << endl;
		cout << "3. 학생탐색" << endl;
		cout << "4. 학생출력" << endl;
		cout << "5. 종료" << endl;
		cout << "메뉴를 선택하세요 : ";

		int menu;
		cin >> menu;

		if (cin.fail()) {
			// 에러버퍼 비우기
			cin.clear();
			// 입력버퍼에 \n이 남아있으므로 입력버퍼를 검색하여 \n을 지워준다.
			cin.ignore(1024, '\n');
			continue;
		}

		if (menu == MENU_EXIT)
			break;

		switch (menu) {
		case MENU_INSERT:
			system("cls");
			cout << "============ 학생추가 ============" << endl;

			if (studentCount == STUDENT_MAX) {
				break;
			}

			cout << "이름 : ";
			cin >> studentArray[studentCount].name;

			cin.ignore(1024, '\n');

			cout << "주소 : ";
			cin.getline(studentArray[studentCount].address, ADDRESS_SIZE);

			cout << "전화번호 : ";
			cin.getline(studentArray[studentCount].phoneNum, PHONE_SIZE);

			cout << "국어 점수 : ";
			cin >> studentArray[studentCount].korScore;

			cout << "수학 점수 : ";
			cin >> studentArray[studentCount].mathScore;

			cout << "영어 점수 : ";
			cin >> studentArray[studentCount].engScore;

			studentArray[studentCount].total =
				studentArray[studentCount].korScore +
				studentArray[studentCount].mathScore +
				studentArray[studentCount].engScore;
			studentArray[studentCount].avg = studentArray[studentCount].total / 3.f;

			studentArray[studentCount].number = studentNumber;
			studentNumber++;
			studentCount++;

			cout << "학생 추가 완료" << endl;
			break;

		case MENU_DELETE:
			system("cls");
			cout << "============ 학생삭제 ============" << endl;

			cin.ignore(1024, '\n');

			cout << "삭제할 이름을 입력하세요 : ";
			cin.getline(searchName, NAME_SIZE);
			for (int i = 0; i < studentCount; i++) {
				if (strcmp(studentArray[i].name, searchName) == 0) {
					for (int j = i; j < studentCount - 1; j++) {
						studentArray[j] = studentArray[j + 1];
					}
					studentCount--;

					cout << "학생을 삭제하였습니다" << endl;
				}
			}

			break;
		case MENU_SEARCH:
			system("cls");
			cout << "============ 학생탐색 ============" << endl;
			
			cin.ignore(1024, '\n');

			cout << "탐색할 이름을 입력하세요 : ";
			cin.getline(searchName, NAME_SIZE);

			for (int i = 0; i < studentCount; i++) {
				if (strcmp(studentArray[i].name, searchName) == 0) {
					cout << "이름 : " << studentArray[i].name << endl;
					cout << "주소 : " << studentArray[i].address << endl;
					cout << "전화번호 : " << studentArray[i].phoneNum << endl;
					cout << "학번 : " << studentArray[i].number << endl;
					cout << "국어점수 : " << studentArray[i].korScore << endl;
					cout << "수학점수 : " << studentArray[i].mathScore << endl;
					cout << "영어점수 : " << studentArray[i].engScore << endl;
					cout << "총점 : " << studentArray[i].total << endl;
					cout << "평균 : " << studentArray[i].avg << endl << endl;
					break;
				}
			}

			break;
		case MENU_OUTPUT:
			system("cls");
			cout << "============ 학생출력 ============" << endl;

			for (int i = 0; i < studentCount; i++) {
				cout << "이름 : " << studentArray[i].name << endl;
				cout << "주소 : " << studentArray[i].address << endl;
				cout << "전화번호 : " << studentArray[i].phoneNum << endl;
				cout << "학번 : " << studentArray[i].number << endl;
				cout << "국어점수 : " << studentArray[i].korScore << endl;
				cout << "수학점수 : " << studentArray[i].mathScore << endl;
				cout << "영어점수 : " << studentArray[i].engScore << endl;
				cout << "총점 : " << studentArray[i].total << endl;
				cout << "평균 : " << studentArray[i].avg << endl << endl;
			}

			break;
		default:
			cout << "메뉴를 잘못 선택했습니다." << endl;
			break;
		}
		
		system("pause");
	}

	return 0;
}