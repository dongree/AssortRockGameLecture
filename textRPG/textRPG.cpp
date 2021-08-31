#include <iostream>
#include <time.h>

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

void levelUpSet(levelUpStatus *levelUpTable, int job, int attackMin, int attackMax, int armorMin, int armorMax, int HPMax, int MPMax);
void jobAbilitySet(Player &player, const char *jobName, int attackMin, int attackMax, int armorMin, int armorMax, int HP, int HPMax, int MP, int MPMax);
void monsterAbilitySet(Monster &monster, const char* monsterName, int attackMin, int attackMax, int armorMin, int armorMax, int HP, int HPMax, int MP, int MPMax, int level, int exp, int goldMin, int goldMax);
void itemSet(Item &item, const char* name, const char* typeName, ITEM_TYPE type, int min, int max, int price, int sell, const char* desc);
void playerInfoPrint(Player& player, const int* levelUpExp);
void monsterInfoPrint(Monster& monster);
int random(int a, int b);
void ItemPrint(Item* types, Player& player, int max, const char* ability);
void storeCalc(int index, Item* types, Player &player);
int inputInt();


int main() 
{
	srand((unsigned int)time(0));

	// �������� �ʿ��� ����ġ ���
	const int levelUpExp[LEVEL_MAX] = {4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000};

	levelUpStatus levelUpTable[JOB_END - 1] = {};

	levelUpSet(levelUpTable, JOB_KNIGHT, 4, 10, 8, 16, 150, 20);
	levelUpSet(levelUpTable, JOB_ARCHER, 10, 15, 5, 10, 80, 40);
	levelUpSet(levelUpTable, JOB_WIZARD, 15, 20, 3, 7, 50, 60);

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

		job = inputInt();
		
		if (job == INT_MAX || job <= JOB_NONE || job >= JOB_END)
			job = JOB_NONE;
	}

	player.level = 1;
	player.exp = 0;
	player.job = (JOB)job;
	player.inventory.gold = 10000;

	switch (player.job) 
	{
	case JOB_KNIGHT:
		jobAbilitySet(player, "���", 5, 10, 15, 20, 500, 500, 100, 100);
		break;
	case JOB_ARCHER:
		jobAbilitySet(player, "�ü�", 10, 15, 10, 15, 400, 400, 200, 200);
		break;
	case JOB_WIZARD:
		jobAbilitySet(player, "������", 15, 20, 5, 10, 300, 300, 300, 300);
		break;
	}

	// ���� ����
	Monster monsterArray[MT_BACK - 1] = {};

	// ��� ����
	monsterAbilitySet(monsterArray[0], "���", 20, 30, 2, 5, 100, 100, 10, 10, 1, 1000, 500, 1500);

	// Ʈ�� ����
	monsterAbilitySet(monsterArray[1], "Ʈ��", 80, 130, 60, 90, 2000, 2000, 100, 100, 5, 7000, 6000, 8000);

	// Ʈ�� ����
	monsterAbilitySet(monsterArray[2], "�巡��", 250, 500, 200, 400, 30000, 30000, 20000, 20000, 10, 30000, 20000, 50000);


	// �������� �Ǹ��� ������ ��� ����
	Item storeWeapon[STORE_WEAPON_MAX] = {};
	Item storeArmor[STORE_ARMOR_MAX] = {};

	// �� ������ �������� ����
	itemSet(storeWeapon[0], "�����", "����", IT_WEAPON, 10, 20, 1000, 500, "�Ѷ�꿡�� �ֿ� �����");
	itemSet(storeWeapon[1], "�Ѷ�� Ȱ", "����", IT_WEAPON, 20, 30, 3000, 1500, "���������� �Ѷ���� ����ϴ� ������ ���� Ȱ");
	itemSet(storeWeapon[2], "���� ������", "����", IT_WEAPON, 100, 150, 10000, 5000, "�� �����̷� ���ֵ��� ��������ٴ� ������ �ִ�");
	itemSet(storeArmor[0], "õ����", "��", IT_ARMOR, 2, 10, 1000, 500, "õ���� ���� ����");
	itemSet(storeArmor[1], "���װ���", "��", IT_ARMOR, 15, 30, 3000, 1500, "�������� ���� ����");
	itemSet(storeArmor[2], "������ ����", "��", IT_ARMOR, 50, 150, 10000, 5000, "����������� �ִ� ���������� ���� ����");


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
		menu = inputInt();

		if (menu == INT_MAX || menu <= MM_NONE || menu > MM_EXIT)
			continue;

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
				menu = inputInt();

				if (menu == INT_MAX || menu <= MT_NONE || menu > MT_BACK)
					continue;

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
					playerInfoPrint(player, levelUpExp);

					//���� ���� ���
					cout << "============================= Monster =============================" << endl;
					monsterInfoPrint(monster);

					cout << "1. ����" << endl;
					cout << "2. ��������" << endl;
					cout << "�޴��� �����ϼ��� : ";
					menu = inputInt();
					if (menu == INT_MAX)
						continue;

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

						int attack = random(attackMax, attackMin);
						int armor = random(monster.armorMax, monster.armorMin);

						int damage = attack - armor;

						damage = damage < 1 ? 1 : damage;

						monster.HP -= damage;

						cout << player.name << "�� " << monster.name <<
							"���� " << damage << " ���ظ� �������ϴ�." << endl;

						// ���� �׾��� ���
						if (monster.HP <= 0) {
							cout << monster.name << " ���Ͱ� ����Ͽ����ϴ�." << endl;

							player.exp += monster.exp;
							int gold = random(monster.goldMax, monster.goldMin);
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

								player.attackMin += levelUpTable[jobIndex].attackMin;
								player.attackMax += levelUpTable[jobIndex].attackMax;
								player.armorMin += levelUpTable[jobIndex].armorMin;
								player.armorMax += levelUpTable[jobIndex].armorMax;
								player.HPMax += levelUpTable[jobIndex].HPMax;
								player.MPMax += levelUpTable[jobIndex].MPMax;
								
								// ü�� ȸ��
								player.HP = player.HPMax;
								player.MP = player.MPMax;
							}

							system("pause");
							break;
						}

						// ���Ͱ� ����ִٸ� �÷��̾ �����Ѵ�.
						attack = random(monster.attackMax, monster.attackMin);

						int armorMin = player.armorMin;
						int armorMax = player.armorMax;

						if (player.bEquip[EQ_ARMOR] == true) {
							armorMin += player.iEquip[EQ_ARMOR].min;
							armorMax += player.iEquip[EQ_ARMOR].max;
						}

						armor = random(armorMax, armorMin);

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
				menu = inputInt();

				if (menu == INT_MAX || menu <= SM_NONE || menu > SM_BACK)
					continue;

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
						ItemPrint(storeWeapon, player, STORE_WEAPON_MAX, "���ݷ�");
						cout << "�����ݾ� : " << player.inventory.gold << " Gold" << endl;
						cout << "�������� : " << INVENTORY_MAX - player.inventory.itemCount << endl;
						cout << "������ �������� �����ϼ��� : ";

						menu = inputInt();
						
						if (menu == INT_MAX)
							continue;

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

						storeCalc(weaponIndex, storeWeapon, player);
						system("pause");
					}
					break;
				case(SM_ARMOR):
					while (true) 
					{
						system("cls");
						cout << "**************************** ������ ****************************" << endl;
						// �Ǹ� ����� �����ش�.
						ItemPrint(storeArmor, player, STORE_ARMOR_MAX, "����");
						cout << "�����ݾ� : " << player.inventory.gold << " Gold" << endl;
						cout << "�������� : " << INVENTORY_MAX - player.inventory.itemCount << endl;
						cout << "������ �������� �����ϼ��� : ";
						
						menu = inputInt();
						if (menu == INT_MAX) {
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

						storeCalc(armorIndex, storeArmor, player);

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

				playerInfoPrint(player, levelUpExp);

				cout << endl;

				ItemPrint(player.inventory.items, player, player.inventory.itemCount, "�ɷ�ġ");
				cout << "������ �������� �����ϼ���" << endl;

				menu = inputInt();

				if (menu == INT_MAX)
					continue;

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

void levelUpSet(levelUpStatus* levelUpTable, int job, int attackMin, int attackMax, 
	int armorMin, int armorMax, int HPMax, int MPMax) 
{
	levelUpTable[job - 1].attackMin = attackMin;
	levelUpTable[job - 1].attackMax = attackMax;
	levelUpTable[job - 1].armorMin = armorMin;
	levelUpTable[job - 1].armorMax = armorMax;
	levelUpTable[job - 1].HPMax = HPMax;
	levelUpTable[job - 1].MPMax = MPMax;
};

void jobAbilitySet(Player &player, const char *jobName, int attackMin, int attackMax, 
	int armorMin, int armorMax, int HP, int HPMax, int MP, int MPMax)
{
	strcpy_s(player.jobName, jobName);
	player.attackMin = attackMin;
	player.attackMax = attackMax;
	player.armorMin = armorMin;
	player.armorMax = armorMax;
	player.HPMax = HPMax;
	player.HP = HP;
	player.MPMax = MPMax;
	player.MP = MP;
}

void monsterAbilitySet(Monster &monster, const char* monsterName, int attackMin, int attackMax, 
	int armorMin, int armorMax, int HP, int HPMax, int MP, int MPMax, 
	int level, int exp, int goldMin, int goldMax) 
{
	strcpy_s(monster.name, monsterName);
	monster.attackMin = attackMin;
	monster.attackMax = attackMax;
	monster.armorMin = armorMin;
	monster.armorMax = armorMax;
	monster.HPMax = HPMax;
	monster.HP = HP;
	monster.MPMax = MPMax;
	monster.MP = MP;
	monster.level = level;
	monster.exp = exp;
	monster.goldMin = goldMin;
	monster.goldMax = goldMax;
}

void itemSet(Item &item, const char *name, const char *typeName, ITEM_TYPE type, int min, int max, int price, int sell, const char* desc) {
	strcpy_s(item.name, name);
	strcpy_s(item.typeName, typeName);
	item.type = type;
	item.min = min;
	item.max = max;
	item.price = price;
	item.sell = sell;
	strcpy_s(item.desc, desc);
}


void playerInfoPrint(Player &player, const int *levelUpExp) {
	std::cout << "�̸� : " << player.name << "\t���� : " <<
		player.jobName << endl;
	std::cout << "���� : " << player.level << "\t����ġ : " <<
		player.exp << "/" << levelUpExp[player.level - 1] << std::endl;

	// ���⸦ �����ϰ� ���� ��� ���ݷ¿� ���� ���ݷ��� �߰��Ͽ� ����Ѵ�.
	if (player.bEquip[EQ_WEAPON] == true) {
		std::cout << "���ݷ� : " << player.attackMin << " + " << player.iEquip[EQ_WEAPON].min
			<< " - " << player.attackMax << " + " << player.iEquip[EQ_WEAPON].max << std::endl;
	}
	else {
		std::cout << "���ݷ� : " << player.attackMin << " - " << player.attackMax << std::endl;
	}

	// ���� �����ϰ� ���� ��� ���¿� �� ������ �߰��Ͽ� ����Ѵ�.
	if (player.bEquip[EQ_ARMOR] == true) {
		std::cout << "���� : " << player.armorMin << " + " << player.iEquip[EQ_ARMOR].min
			<< " - " << player.armorMax << " + " << player.iEquip[EQ_ARMOR].max << std::endl;
	}
	else {
		std::cout << "���� : " << player.armorMin << " - " << player.armorMax << std::endl;
	}

	std::cout << "ü�� : " << player.HP << " / " <<
		player.HPMax << "\t���� : " << player.MP << " / " << player.MPMax << std::endl;

	if (player.bEquip[EQ_WEAPON] == true) {
		std::cout << "��������: " << player.iEquip[EQ_WEAPON].name;
	}
	else {
		std::cout << "��������: ����";
	}

	if (player.bEquip[EQ_ARMOR] == true) {
		std::cout << "\t������: " << player.iEquip[EQ_ARMOR].name << std::endl;
	}
	else {
		std::cout << "\t������: ����" << std::endl;
	}

	std::cout << "������� : " << player.inventory.gold << " Gold" << std::endl;
}

void monsterInfoPrint(Monster &monster) {
	std::cout << "�̸� : " << monster.name << "\t���� : " <<
		monster.level << std::endl;
	std::cout << "���ݷ� : " << monster.attackMin << " - " <<
		monster.attackMax << "\t���� : " << monster.armorMin <<
		" - " << monster.armorMax << std::endl;
	std::cout << "ü�� : " << monster.HP << " / " <<
		monster.HPMax << " \t���� : " << monster.MP << " / " << monster.MPMax << std::endl;
	std::cout << "ȹ�����ġ : " << monster.exp << "\tȹ���� : " <<
		monster.goldMin << " - " << monster.goldMax << std::endl;
}

int random(int a, int b) {
	return rand() % (a - b + 1) + b;
}

void ItemPrint(Item *types, Player &player, int max, const char *ability) {
	for (int i = 0; i < max; i++) {
		std::cout << i + 1 << ". �̸� : " << types[i].name << std::endl;
		std::cout << "���� : " << types[i].typeName << std::endl;
		std::cout << ability << " : " << types[i].min << " - " << types[i].max << std::endl;
		std::cout << "���Ű��� : " << types[i].price << std::endl;
		std::cout << "�ǸŰ��� : " << types[i].sell << std::endl;
		std::cout << "���� : " << types[i].desc << std::endl << std::endl;
	}
	std::cout << max + 1 << ". �ڷΰ���" << std::endl;
}

void storeCalc(int index, Item *types, Player &player) {
	player.inventory.gold -= types[index].price;
	player.inventory.items[player.inventory.itemCount] = types[index];
	player.inventory.itemCount += 1;

	std::cout << types[index].name << " �������� �����Ͽ����ϴ�." << std::endl;
}

int inputInt() {
	int input;
	cin >> input;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX; // INT_MAX�� ���ϵǸ� �Է��� �߸��ƴٴ� �ǹ�
	}
	return input;
}