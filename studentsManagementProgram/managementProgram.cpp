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

		cout << "1. �л����" << endl;
		cout << "2. �л�����" << endl;
		cout << "3. �л�Ž��" << endl;
		cout << "4. �л����" << endl;
		cout << "5. ����" << endl;
		cout << "�޴��� �����ϼ��� : ";

		int menu;
		cin >> menu;

		if (cin.fail()) {
			// �������� ����
			cin.clear();
			// �Է¹��ۿ� \n�� ���������Ƿ� �Է¹��۸� �˻��Ͽ� \n�� �����ش�.
			cin.ignore(1024, '\n');
			continue;
		}

		if (menu == MENU_EXIT)
			break;

		switch (menu) {
		case MENU_INSERT:
			system("cls");
			cout << "============ �л��߰� ============" << endl;

			if (studentCount == STUDENT_MAX) {
				break;
			}

			cout << "�̸� : ";
			cin >> studentArray[studentCount].name;

			cin.ignore(1024, '\n');

			cout << "�ּ� : ";
			cin.getline(studentArray[studentCount].address, ADDRESS_SIZE);

			cout << "��ȭ��ȣ : ";
			cin.getline(studentArray[studentCount].phoneNum, PHONE_SIZE);

			cout << "���� ���� : ";
			cin >> studentArray[studentCount].korScore;

			cout << "���� ���� : ";
			cin >> studentArray[studentCount].mathScore;

			cout << "���� ���� : ";
			cin >> studentArray[studentCount].engScore;

			studentArray[studentCount].total =
				studentArray[studentCount].korScore +
				studentArray[studentCount].mathScore +
				studentArray[studentCount].engScore;
			studentArray[studentCount].avg = studentArray[studentCount].total / 3.f;

			studentArray[studentCount].number = studentNumber;
			studentNumber++;
			studentCount++;

			cout << "�л� �߰� �Ϸ�" << endl;
			break;

		case MENU_DELETE:
			system("cls");
			cout << "============ �л����� ============" << endl;

			cin.ignore(1024, '\n');

			cout << "������ �̸��� �Է��ϼ��� : ";
			cin.getline(searchName, NAME_SIZE);
			for (int i = 0; i < studentCount; i++) {
				if (strcmp(studentArray[i].name, searchName) == 0) {
					for (int j = i; j < studentCount - 1; j++) {
						studentArray[j] = studentArray[j + 1];
					}
					studentCount--;

					cout << "�л��� �����Ͽ����ϴ�" << endl;
				}
			}

			break;
		case MENU_SEARCH:
			system("cls");
			cout << "============ �л�Ž�� ============" << endl;
			
			cin.ignore(1024, '\n');

			cout << "Ž���� �̸��� �Է��ϼ��� : ";
			cin.getline(searchName, NAME_SIZE);

			for (int i = 0; i < studentCount; i++) {
				if (strcmp(studentArray[i].name, searchName) == 0) {
					cout << "�̸� : " << studentArray[i].name << endl;
					cout << "�ּ� : " << studentArray[i].address << endl;
					cout << "��ȭ��ȣ : " << studentArray[i].phoneNum << endl;
					cout << "�й� : " << studentArray[i].number << endl;
					cout << "�������� : " << studentArray[i].korScore << endl;
					cout << "�������� : " << studentArray[i].mathScore << endl;
					cout << "�������� : " << studentArray[i].engScore << endl;
					cout << "���� : " << studentArray[i].total << endl;
					cout << "��� : " << studentArray[i].avg << endl << endl;
					break;
				}
			}

			break;
		case MENU_OUTPUT:
			system("cls");
			cout << "============ �л���� ============" << endl;

			for (int i = 0; i < studentCount; i++) {
				cout << "�̸� : " << studentArray[i].name << endl;
				cout << "�ּ� : " << studentArray[i].address << endl;
				cout << "��ȭ��ȣ : " << studentArray[i].phoneNum << endl;
				cout << "�й� : " << studentArray[i].number << endl;
				cout << "�������� : " << studentArray[i].korScore << endl;
				cout << "�������� : " << studentArray[i].mathScore << endl;
				cout << "�������� : " << studentArray[i].engScore << endl;
				cout << "���� : " << studentArray[i].total << endl;
				cout << "��� : " << studentArray[i].avg << endl << endl;
			}

			break;
		default:
			cout << "�޴��� �߸� �����߽��ϴ�." << endl;
			break;
		}
		
		system("pause");
	}

	return 0;
}