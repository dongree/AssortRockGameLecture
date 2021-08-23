#include <iostream>
#include <time.h>

/*
1. ����������� �Ǹ��� ������ ����� ������ְ� �ش� ����� ������ش�.
2. ����� �� �տ� ��ȣ�� �ο����ְ� ��ȣ�� �Է¹޾Ƽ� �ش� ��ȣ�� �������� �����ϰ� ���ش�. ���� ������ ��ȣ�� �ڷΰ��� ����� �����.
��, ������ ��á�ų� ���� ������ ��� �������� ���ϰ� �Ѵ�.
3. ������ �����ϸ� ������� �������� �����ش�.

*/


using namespace std;

enum MAIN_MENU {
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT
};

enum MAP_TYPE {
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK
};

enum JOB {
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END
};

enum BATTLE {
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
};

enum ITEM_TYPE {
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};

enum STORE_MENU {
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
};

enum EQUIP {
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};


#define NAME_SIZE 32
#define ITEM_DESC_LENGTH 512
#define INVENTORY_MAX 20
#define STORE_WEAPON_MAX 3
#define STORE_ARMOR_MAX 3
#define LEVEL_MAX 10

struct Item {
	char name[NAME_SIZE];
	char typeName[NAME_SIZE];
	ITEM_TYPE type;
	int min;
	int max;
	int price;
	int sell;
	char desc[ITEM_DESC_LENGTH];
};

struct Inventory {
	Item items[INVENTORY_MAX];
	int itemCount;
	int gold;
};

struct Player {
	char name[NAME_SIZE];
	char jobName[NAME_SIZE];
	JOB  job;
	int attackMin;
	int attackMax;
	int armorMin;
	int armorMax;
	int HP;
	int HPMax;
	int MP;
	int MPMax;
	int exp;
	int level;
	Item iEquip[EQ_MAX];
	bool bEquip[EQ_MAX];
	Inventory inventory;
};


struct Monster {
	char name[NAME_SIZE];
	int attackMin;
	int attackMax;
	int armorMin;
	int armorMax;
	int HP;
	int HPMax;
	int MP;
	int MPMax;
	int level;
	int exp;
	int goldMin;
	int goldMax;
};

struct levelUpStatus {
	int attackMin;
	int attackMax;
	int armorMin;
	int armorMax;
	int HPMax;
	int MPMax;
};


int main() 
{
	srand((unsigned int)time(0));

	// �������� �ʿ��� ����ġ ���
	const int levelUpExp[LEVEL_MAX] = {4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000};

	levelUpStatus levelupTable[JOB_END - 1] = {};

	levelupTable[JOB_KNIGHT - 1].attackMin = 4;
	levelupTable[JOB_KNIGHT - 1].attackMax = 10;
	levelupTable[JOB_KNIGHT - 1].armorMin = 8;
	levelupTable[JOB_KNIGHT - 1].armorMax = 16;
	levelupTable[JOB_KNIGHT - 1].HPMax = 150;
	levelupTable[JOB_KNIGHT - 1].MPMax = 20;

	levelupTable[JOB_ARCHER - 1].attackMin = 10;
	levelupTable[JOB_ARCHER - 1].attackMax = 15;
	levelupTable[JOB_ARCHER - 1].armorMin = 5;
	levelupTable[JOB_ARCHER - 1].armorMax = 10;
	levelupTable[JOB_ARCHER - 1].HPMax = 80;
	levelupTable[JOB_ARCHER - 1].MPMax = 40;

	levelupTable[JOB_WIZARD - 1].attackMin = 15;
	levelupTable[JOB_WIZARD - 1].attackMax = 20;
	levelupTable[JOB_WIZARD - 1].armorMin = 3;
	levelupTable[JOB_WIZARD - 1].armorMax = 7;
	levelupTable[JOB_WIZARD - 1].HPMax = 50;
	levelupTable[JOB_WIZARD - 1].MPMax = 60;
	

	Player player = {};

	cout << "�̸� : ";
	cin.getline(player.name, NAME_SIZE - 1);

	int job = JOB_NONE;
	while (job == JOB_NONE) 
	{
		system("cls");
		cout << "1. ���" << endl;
		cout << "2. �ü�" << endl;
		cout << "3. ������" << endl;
		cout << "������ �����ϼ��� : ";

		cin >> job;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		else if (job <= JOB_NONE || job >= JOB_END)
			job = JOB_NONE;
	}

	player.level = 1;
	player.exp = 0;
	player.job = (JOB)job;
	player.inventory.gold = 10000;

	switch (player.job) 
	{
	case JOB_KNIGHT:
		strcpy_s(player.jobName, "���");
		player.attackMin = 5;
		player.attackMax = 10;
		player.armorMin = 15;
		player.armorMax = 20;
		player.HPMax = 500;
		player.HP = 500;
		player.MPMax = 100;
		player.MP = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(player.jobName, "�ü�");
		player.attackMin = 10;
		player.attackMax = 15;
		player.armorMin = 10;
		player.armorMax = 15;
		player.HPMax = 400;
		player.HP = 400;
		player.MPMax = 200;
		player.MP = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(player.jobName, "������");
		player.attackMin = 15;
		player.attackMax = 20;
		player.armorMin = 5;
		player.armorMax = 10;
		player.HPMax = 300;
		player.HP = 300;
		player.MPMax = 300;
		player.MP = 300;
		break;
	}

	// ���� ����
	Monster monsterArray[MT_BACK - 1] = {};

	// ��� ����
	strcpy_s(monsterArray[0].name, "���");
	monsterArray[0].attackMin = 20;
	monsterArray[0].attackMax = 30;
	monsterArray[0].armorMin = 2;
	monsterArray[0].armorMax = 5;
	monsterArray[0].HP = 100;
	monsterArray[0].HPMax = 100;
	monsterArray[0].MP = 10;
	monsterArray[0].MPMax = 10;
	monsterArray[0].level = 1;
	monsterArray[0].exp = 1000;
	monsterArray[0].goldMin = 500;
	monsterArray[0].goldMax = 1500;


	// Ʈ�� ����
	strcpy_s(monsterArray[1].name, "Ʈ��");
	monsterArray[1].attackMin = 80;
	monsterArray[1].attackMax = 130;
	monsterArray[1].armorMin = 60;
	monsterArray[1].armorMax = 90;
	monsterArray[1].HP = 2000;
	monsterArray[1].HPMax = 2000;
	monsterArray[1].MP = 100;
	monsterArray[1].MPMax = 100;
	monsterArray[1].level = 5;
	monsterArray[1].exp = 7000;
	monsterArray[1].goldMin = 6000;
	monsterArray[1].goldMax = 8000;

	// Ʈ�� ����
	strcpy_s(monsterArray[2].name, "�巡��");
	monsterArray[2].attackMin = 250;
	monsterArray[2].attackMax = 500;
	monsterArray[2].armorMin = 200;
	monsterArray[2].armorMax = 400;
	monsterArray[2].HP = 30000;
	monsterArray[2].HPMax = 30000;
	monsterArray[2].MP = 20000;
	monsterArray[2].MPMax = 20000;
	monsterArray[2].level = 10;
	monsterArray[2].exp = 30000;
	monsterArray[2].goldMin = 20000;
	monsterArray[2].goldMax = 50000;

	// �������� �Ǹ��� ������ ��� ����
	Item storeWeapon[STORE_WEAPON_MAX] = {};
	Item storeArmor[STORE_ARMOR_MAX] = {};

	// �� ������ �������� ����
	strcpy_s(storeWeapon[0].name, "�����");
	strcpy_s(storeWeapon[0].typeName, "����");
	storeWeapon[0].type = IT_WEAPON;
	storeWeapon[0].min = 10;
	storeWeapon[0].max = 20;
	storeWeapon[0].price = 1000;
	storeWeapon[0].sell = 500;
	strcpy_s(storeWeapon[0].desc, "�Ѷ�꿡�� �ֿ� �����");

	strcpy_s(storeWeapon[1].name, "�Ѷ�� Ȱ");
	strcpy_s(storeWeapon[1].typeName, "����");
	storeWeapon[1].type = IT_WEAPON;
	storeWeapon[1].min = 20;
	storeWeapon[1].max = 30;
	storeWeapon[1].price = 3000;
	storeWeapon[1].sell = 1500;
	strcpy_s(storeWeapon[1].desc, "���������� �Ѷ���� ����ϴ� ������ ���� Ȱ");

	strcpy_s(storeWeapon[2].name, "���� ������");
	strcpy_s(storeWeapon[2].typeName, "����");
	storeWeapon[2].type = IT_WEAPON;
	storeWeapon[2].min = 100;
	storeWeapon[2].max = 150;
	storeWeapon[2].price = 10000;
	storeWeapon[2].sell = 5000;
	strcpy_s(storeWeapon[2].desc, "�� �����̷� ���ֵ��� ��������ٴ� ������ �ִ�");
	
	strcpy_s(storeArmor[0].name, "õ����");
	strcpy_s(storeArmor[0].typeName, "��");
	storeArmor[0].type = IT_ARMOR;
	storeArmor[0].min = 2;
	storeArmor[0].max = 10;
	storeArmor[0].price = 1000;
	storeArmor[0].sell = 500;
	strcpy_s(storeArmor[0].desc, "õ���� ���� ����");

	strcpy_s(storeArmor[1].name, "���װ���");
	strcpy_s(storeArmor[1].typeName, "��");
	storeArmor[1].type = IT_ARMOR;
	storeArmor[1].min = 15;
	storeArmor[1].max = 30;
	storeArmor[1].price = 3000;
	storeArmor[1].sell = 1500;
	strcpy_s(storeArmor[1].desc, "�������� ���� ����");

	strcpy_s(storeArmor[2].name, "������ ����");
	strcpy_s(storeArmor[2].typeName, "��");
	storeArmor[2].type = IT_ARMOR;
	storeArmor[2].min = 50;
	storeArmor[2].max = 150;
	storeArmor[2].price = 10000;
	storeArmor[2].sell = 5000;
	strcpy_s(storeArmor[2].desc, "����������� �ִ� ���������� ���� ����");

	// �κ��丮

	while (true)
	{
		system("cls");
		cout << "**************************** �κ� ****************************" << endl;
		cout << "1. ��" << endl;
		cout << "2. ����" << endl;
		cout << "3. ����" << endl;
		cout << "4. ����" << endl;

		cout << "�޴��� �����ϼ��� : ";

		int menu;
		cin >> menu;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		else if (menu == MM_EXIT)
			break;

		switch (menu) 
		{
		case MM_MAP:
			while (true)
			{
				system("cls");
				cout << "**************************** �� ****************************" << endl;
				cout << "1. ����" << endl;
				cout << "2. ����" << endl;
				cout << "3. �����" << endl;
				cout << "4. �ڷΰ���" << endl;
				cin >> menu;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				if (menu == MT_BACK)
					break;

				Monster monster = monsterArray[menu - 1];
				while (true)
				{
					system("cls");
					switch (menu) {
					case MT_EASY:
						cout << "**************************** ���� ****************************" << endl;
						break;
					case MT_NORMAL:
						cout << "**************************** ���� ****************************" << endl;
						break;
					case MT_HARD:
						cout << "**************************** ����� ****************************" << endl;
						break;
					}
					// �÷��̾� ���� ���
					cout << "============================= Player =============================" << endl;
					cout << "�̸� : " << player.name << "\t���� : " <<
						player.jobName << endl;
					cout << "���� : " << player.level << "\t����ġ : " <<
						player.exp << "/" << levelUpExp[player.level-1] << endl;
					
					// ���⸦ �����ϰ� ���� ��� ���ݷ¿� ���� ���ݷ��� �߰��Ͽ� ����Ѵ�.
					if (player.bEquip[EQ_WEAPON] == true) {
						cout << "���ݷ� : " << player.attackMin << " + " << player.iEquip[EQ_WEAPON].min
							<< " - " << player.attackMax << " + " << player.iEquip[EQ_WEAPON].max << endl;
					}
					else {
						cout << "���ݷ� : " << player.attackMin << " - " << player.attackMax << endl;
					}

					// ���⸦ �����ϰ� ���� ��� ���ݷ¿� ���� ���ݷ��� �߰��Ͽ� ����Ѵ�.
					if (player.bEquip[EQ_ARMOR] == true) {
						cout << "���� : " << player.armorMin << " + " << player.iEquip[EQ_ARMOR].min
							<< " - " << player.armorMax << " + " << player.iEquip[EQ_ARMOR].max << endl;
					}
					else {
						cout << "���� : " << player.armorMin << " - " << player.armorMax << endl;
					}

					cout << "ü�� : " << player.HP << " / " <<
						player.HPMax << "\t���� : " << player.MP << " / " << player.MPMax << endl;

					if (player.bEquip[EQ_WEAPON] == true) {
						cout << "��������: " << player.iEquip[EQ_WEAPON].name;
					}
					else {
						cout << "��������: ����";
					}

					if (player.bEquip[EQ_ARMOR] == true) {
						cout << "\t������: " << player.iEquip[EQ_ARMOR].name << endl;
					}
					else {
						cout << "\t������: ����" << endl;
					}

					cout << "������� : " << player.inventory.gold << " Gold" << endl;

					//���� ���� ���
					cout << "============================= Monster =============================" << endl;
					cout << "�̸� : " << monster.name << "\t���� : " <<
						monster.level << endl;

					cout << "���ݷ� : " << monster.attackMin << " - " <<
						monster.attackMax << "\t���� : " << monster.armorMin <<
						" - " << monster.armorMax << endl;
					cout << "ü�� : " << monster.HP << " / " <<
						monster.HPMax << "\t���� : " << monster.MP << " / " << monster.MPMax << endl;
					cout << "ȹ�����ġ : " << monster.exp << "\tȹ���� : " <<
						monster.goldMin << " - " << monster.goldMax << endl;

					cout << "1. ����" << endl;
					cout << "2. ��������" << endl;
					cout << "�޴��� �����ϼ��� : ";
					cin >> menu;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					else if (menu == BATTLE_BACK)
						break;

					switch (menu)
					{
					case BATTLE_ATTACK:
						int attackMin = player.attackMin;
						int attackMax = player.attackMax;

						if (player.bEquip[EQ_WEAPON] == true) {
							attackMin += player.iEquip[EQ_WEAPON].min;
							attackMax += player.iEquip[EQ_WEAPON].max;
						}


						int attack = rand() % (attackMax - attackMin + 1) + attackMin;
						int armor = rand() % (monster.armorMax - monster.armorMin + 1) + monster.armorMin;

						int damage = attack - armor;

						damage = damage < 1 ? 1 : damage;

						monster.HP -= damage;

						cout << player.name << "�� " << monster.name <<
							"���� " << damage << " ���ظ� �������ϴ�." << endl;

						// ���� �׾��� ���
						if (monster.HP <= 0) {
							cout << monster.name << " ���Ͱ� ����Ͽ����ϴ�." << endl;

							player.exp += monster.exp;
							int gold = (rand() % (monster.goldMax - monster.goldMin + 1) + monster.goldMin);
							player.inventory.gold += gold;

							cout << monster.exp << " ����ġ�� ȹ���Ͽ����ϴ�." << endl;
							cout << gold << " ��带 ȹ���Ͽ����ϴ�." << endl;

							monster.HP = monster.HPMax;
							monster.MP = monster.MPMax;

							if (player.exp >= levelUpExp[player.level - 1]) {
								player.exp -= levelUpExp[player.level - 1];
								player.level += 1;
								cout << "������ �ϼ̽��ϴ�." << endl;
							
								// �ɷ�ġ ���
								int jobIndex = player.job - 1;

								player.attackMin += levelupTable[jobIndex].attackMin;
								player.attackMax += levelupTable[jobIndex].attackMax;
								player.armorMin += levelupTable[jobIndex].armorMin;
								player.attackMax += levelupTable[jobIndex].attackMax;
								player.HPMax += levelupTable[jobIndex].HPMax;
								player.MPMax += levelupTable[jobIndex].MPMax;
								
								// ü�� ȸ��
								player.HP = player.HPMax;
								player.MP = player.MPMax;
							}



							system("pause");
							break;
						}

						// ���Ͱ� ����ִٸ� �÷��̾ �����Ѵ�.
						attack = rand() % (monster.attackMax - monster.attackMin + 1) + monster.attackMin;

						int armorMin = player.armorMin;
						int armorMax = player.armorMax;

						if (player.bEquip[EQ_ARMOR] == true) {
							armorMin += player.iEquip[EQ_ARMOR].min;
							armorMax += player.iEquip[EQ_ARMOR].max;
						}

						armor = rand() % (armorMax - armorMin + 1) + armorMin;

						damage = attack - armor;

						damage = damage < 1 ? 1 : damage;

						player.HP -= damage;

						cout << monster.name << "�� " << player.name <<
							"���� " << damage << " ���ظ� �������ϴ�." << endl;

						if (player.HP <= 0) {
							cout << player.name << " �÷��̾ ����Ͽ����ϴ�." << endl;

							int exp = player.exp * 0.1f;
							int gold = player.inventory.gold * 0.1f;

							player.exp -= exp;
							player.inventory.gold -= gold;

							cout << exp << " ����ġ�� �Ҿ����ϴ�." << endl;
							cout << gold << " ��带 �Ҿ����ϴ�." << endl;

							player.HP = player.HPMax;
							player.MP = player.MPMax;

						}
						system("pause");

						break;
					}

				}
			}
			break;
		case MM_STORE:
			while (true) 
			{
				system("cls");
				cout << "**************************** ���� ****************************" << endl;
				cout << "1. �������" << endl;
				cout << "2. ������" << endl;
				cout << "3. �ڷΰ���" << endl;
				cout << "������ �����ϼ��� : ";
				cin >> menu;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				else if (menu == SM_BACK)
					break;

				switch (menu) 
				{
				case(SM_WEAPON):
					while (true) 
					{
						system("cls");
						cout << "**************************** ������� ****************************" << endl;
						// �Ǹ� ����� �����ش�.
						for (int i = 0; i < STORE_WEAPON_MAX; i++) {
							cout << i + 1 << ". �̸� : " << storeWeapon[i].name << endl;
							cout << "���� : " << storeWeapon[i].typeName << endl;
							cout << "���ݷ� : " << storeWeapon[i].min << " - " << storeWeapon[i].max << endl;
							cout << "���Ű��� : " << storeWeapon[i].price << endl;
							cout << "�ǸŰ��� : " << storeWeapon[i].sell << endl;
							cout << "���� : " << storeWeapon[i].desc << endl << endl;
						}

						cout << STORE_WEAPON_MAX + 1 << ". �ڷΰ���" << endl;
						cout << "�����ݾ� : " << player.inventory.gold << " Gold" << endl;
						cout << "�������� : " << INVENTORY_MAX - player.inventory.itemCount << endl;
						cout << "������ �������� �����ϼ��� : ";
						cin >> menu;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}

						else if (menu == STORE_WEAPON_MAX + 1)
							break;

						else if (menu < 1 || menu > STORE_WEAPON_MAX + 1) {
							cout << "�߸� �����Ͽ����ϴ�." << endl;
							system("pause");
							continue;
						}

						int weaponIndex = menu - 1;

						if (player.inventory.itemCount == INVENTORY_MAX) {
							cout << "������ �� á���ϴ�." << endl;
							system("pause");
							continue;
						}
						else if (player.inventory.gold < storeWeapon[weaponIndex].price) {
							cout << "�����ݾ��� �����մϴ�." << endl;
							system("pause");
							continue;
						}

						player.inventory.gold -= storeWeapon[weaponIndex].price;
						player.inventory.items[player.inventory.itemCount] = storeWeapon[weaponIndex];
						player.inventory.itemCount += 1;

						cout << storeWeapon[weaponIndex].name << " �������� �����Ͽ����ϴ�." << endl;
						system("pause");
					}
					break;
				case(SM_ARMOR):
					while (true) 
					{
						system("cls");
						cout << "**************************** ������ ****************************" << endl;
						// �Ǹ� ����� �����ش�.
						for (int i = 0; i < STORE_ARMOR_MAX; i++) {
							cout << i + 1 << ". �̸� : " << storeArmor[i].name << endl;
							cout << "���� : " << storeArmor[i].typeName << endl;
							cout << "���� : " << storeArmor[i].min << " - " << storeArmor[i].max << endl;
							cout << "���Ű��� : " << storeArmor[i].price << endl;
							cout << "�ǸŰ��� : " << storeArmor[i].sell << endl;
							cout << "���� : " << storeArmor[i].desc << endl << endl;
						}
						cout << STORE_ARMOR_MAX + 1 << ". �ڷΰ���" << endl;
						cout << "�����ݾ� : " << player.inventory.gold << " Gold" << endl;
						cout << "�������� : " << INVENTORY_MAX - player.inventory.itemCount << endl;
						cout << "������ �������� �����ϼ��� : ";
						cin >> menu;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}

						else if (menu == STORE_ARMOR_MAX + 1)
							break;

						else if (menu < 1 || menu > STORE_ARMOR_MAX + 1) {
							cout << "�߸� �����Ͽ����ϴ�." << endl;
							system("pause");
							continue;
						}

						int armorIndex = menu - 1;

						if (player.inventory.itemCount == INVENTORY_MAX) {
							cout << "������ �� á���ϴ�." << endl;
							system("pause");
							continue;
						}
						else if (player.inventory.gold < storeArmor[armorIndex].price) {
							cout << "�����ݾ��� �����մϴ�." << endl;
							system("pause");
							continue;
						}

						player.inventory.gold -= storeArmor[armorIndex].price;
						player.inventory.items[player.inventory.itemCount] = storeArmor[armorIndex];
						player.inventory.itemCount += 1;

						cout << storeArmor[armorIndex].name << " �������� �����Ͽ����ϴ�." << endl;
						system("pause");
					}
					break;
				}

			}
			break;
		case MM_INVENTORY:
			while (true) 
			{
				system("cls");
				cout << "**************************** ���� ****************************" << endl;

				cout << "�̸� : " << player.name << "\t���� : " <<
					player.jobName << endl;
				cout << "���� : " << player.level << "\t����ġ : " <<
					player.exp << endl;

				// ���⸦ �����ϰ� ���� ��� ���ݷ¿� ���� ���ݷ��� �߰��Ͽ� ����Ѵ�.
				if (player.bEquip[EQ_WEAPON] == true) {
					cout << "���ݷ� : " << player.attackMin << " + " << player.iEquip[EQ_WEAPON].min
						<< " - " << player.attackMax << " + " << player.iEquip[EQ_WEAPON].max << endl;
				}
				else {
					cout << "���ݷ� : " << player.attackMin << " - " << player.attackMax << endl;
				}

				// ���⸦ �����ϰ� ���� ��� ���ݷ¿� ���� ���ݷ��� �߰��Ͽ� ����Ѵ�.
				if (player.bEquip[EQ_ARMOR] == true) {
					cout << "���� : " << player.armorMin << " + " << player.iEquip[EQ_ARMOR].min
						<< " - " << player.armorMax << " + " << player.iEquip[EQ_ARMOR].max << endl;
				}
				else {
					cout << "���� : " << player.armorMin << " - " << player.armorMax << endl;
				}

				cout << "ü�� : " << player.HP << " / " <<
					player.HPMax << "\t���� : " << player.MP << " / " << player.MPMax << endl;

				if (player.bEquip[EQ_WEAPON] == true) {
					cout << "��������: " << player.iEquip[EQ_WEAPON].name;
				}
				else {
					cout << "��������: ����";
				}

				if (player.bEquip[EQ_ARMOR] == true) {
					cout << "\t������: " << player.iEquip[EQ_ARMOR].name << endl;
				}
				else {
					cout << "\t������: ����" << endl;
				}

				cout << "������� : " << player.inventory.gold << " Gold" << endl;

				cout << endl;

				for (int i = 0; i < player.inventory.itemCount; i++) {
					cout << i + 1 << ". �̸� : " << player.inventory.items[i].name << endl;
					cout << "���� : " << player.inventory.items[i].typeName << endl;
					cout << "���ݷ� : " << player.inventory.items[i].min << " - " << player.inventory.items[i].max << endl;
					cout << "���Ű��� : " << player.inventory.items[i].price << endl;
					cout << "�ǸŰ��� : " << player.inventory.items[i].sell << endl;
					cout << "���� : " << player.inventory.items[i].desc << endl << endl;
				}

				cout << player.inventory.itemCount + 1 << ". �ڷΰ���" << endl;
				cout << "������ �������� �����ϼ���" << endl;
				cin >> menu;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				else if (menu == player.inventory.itemCount + 1)
					break;

				else if (menu < 1 || menu > player.inventory.itemCount + 1) {
					cout << "�߸� �����Ͽ����ϴ�" << endl;
					system("pause");
					continue;
				}

				int idx = menu - 1;

				EQUIP eq;

				switch (player.inventory.items[idx].type) {
				case IT_WEAPON:
					eq = EQ_WEAPON;
					break;
				case IT_ARMOR:
					eq = EQ_ARMOR;
					break;
				}

				// �������� �����Ǿ� �ִ� ���
				if (player.bEquip[eq] == true) {
					Item swap = player.iEquip[eq];
					player.iEquip[eq] = player.inventory.items[idx];
					player.inventory.items[idx] = swap;
					cout << "������ �����Ǿ� ������" << endl;
				}
				// �������� �����Ǿ� ���� ���� ���
				else {
					player.iEquip[eq] = player.inventory.items[idx];
					for (int i = idx; i < player.inventory.itemCount-1; i++) {
						player.inventory.items[i] = player.inventory.items[i + 1];
					}
					player.inventory.itemCount -= 1;
					player.bEquip[eq] = true;
				}

				cout << player.iEquip[eq].name << " �������� �����߽��ϴ�." << endl;

				system("pause");
			}
			break;
		default:
			cout << "�߸� �����Ͽ����ϴ�" << endl;
			break;
		}
	
		
	}
	return 0;
}