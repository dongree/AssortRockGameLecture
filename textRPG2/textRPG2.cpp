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

enum EQUIP {
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};

enum ITEM_TYPE {
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};

enum BATTLE {
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
};

enum STORE_MENU {
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
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

const int levelUpExp[LEVEL_MAX] = { 4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000 };
levelUpStatus levelUpTable[JOB_END - 1] = {};


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


int outputMainMenu() {
	system("cls");
	cout << "**************************** �κ� ****************************" << endl;
	cout << "1. ��" << endl;
	cout << "2. ����" << endl;
	cout << "3. ����" << endl;
	cout << "4. ����" << endl;

	cout << "�޴��� �����ϼ��� : ";

	int menu = inputInt();

	if (menu == INT_MAX || menu <= MM_NONE || menu > MM_EXIT)
		return MM_NONE;

	return menu;
}


int outputMapMenu() {

	system("cls");
	cout << "**************************** �� ****************************" << endl;
	cout << "1. ����" << endl;
	cout << "2. ����" << endl;
	cout << "3. �����" << endl;
	cout << "4. �ڷΰ���" << endl;
	int menu = inputInt();

	if (menu == INT_MAX || menu <= MT_NONE || menu > MT_BACK)
		return MT_NONE;

	return menu;
}


int selectJob() {
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

	return job;
}

void setPlayer(Player* player) {
	cout << "�̸� : ";
	cin.getline(player->name, NAME_SIZE - 1);

	player->job = (JOB)selectJob();
	player->level = 1;
	player->exp = 0;
	player->inventory.gold = 10000;

	switch (player->job)
	{
	case JOB_KNIGHT:
		strcpy_s(player->jobName, "���");
		player->attackMin = 5;
		player->attackMax = 10;
		player->armorMin = 15;
		player->armorMax = 20;
		player->HPMax = 500;
		player->HP = 500;
		player->MPMax = 100;
		player->MP = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(player->jobName, "�ü�");
		player->attackMin = 10;
		player->attackMax = 15;
		player->armorMin = 10;
		player->armorMax = 15;
		player->HPMax = 400;
		player->HP = 400;
		player->MPMax = 200;
		player->MP = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(player->jobName, "������");
		player->attackMin = 15;
		player->attackMax = 20;
		player->armorMin = 5;
		player->armorMax = 10;
		player->HPMax = 300;
		player->HP = 300;
		player->MPMax = 300;
		player->MP = 300;
		break;
	}
}

Monster createMonster(const char* monsterName, int attackMin, int attackMax,
	int armorMin, int armorMax, int HP,  int MP, 
	int level, int exp, int goldMin, int goldMax) {
	Monster monster = {};
	strcpy_s(monster.name, monsterName);
	monster.attackMin = attackMin;
	monster.attackMax = attackMax;
	monster.armorMin = armorMin;
	monster.armorMax = armorMax;
	monster.HPMax = HP;
	monster.HP = HP;
	monster.MPMax = MP;
	monster.MP = MP;
	monster.level = level;
	monster.exp = exp;
	monster.goldMin = goldMin;
	monster.goldMax = goldMax;

	return monster;
}

void setMonster(Monster* monsterArr) {
	monsterArr[0] = createMonster("���", 20, 30, 2, 5, 100, 10, 1, 1000, 500, 1500);
	monsterArr[1] = createMonster("Ʈ��", 80, 130, 60, 90, 2000, 100, 5, 7000, 6000, 8000);
	monsterArr[2] = createMonster("�巡��", 250, 500, 200, 400, 30000, 20000, 10, 30000, 20000, 50000);
}

void outputBattleTag(int menu) {
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
}

void outputPlayer(Player *player) {
	// �÷��̾� ���� ���
	cout << "============================= Player =============================" << endl;
	cout << "�̸� : " << player->name << "\t���� : " <<
		player->jobName << endl;
	cout << "���� : " << player->level << "\t����ġ : " <<
		player->exp << "/" << levelUpExp[player->level - 1] << endl;

	// ���⸦ �����ϰ� ���� ��� ���ݷ¿� ���� ���ݷ��� �߰��Ͽ� ����Ѵ�.
	if (player->bEquip[EQ_WEAPON] == true) {
		cout << "���ݷ� : " << player->attackMin << " + " << player->iEquip[EQ_WEAPON].min
			<< " - " << player->attackMax << " + " << player->iEquip[EQ_WEAPON].max << endl;
	}
	else {
		cout << "���ݷ� : " << player->attackMin << " - " << player->attackMax << endl;
	}

	// ���⸦ �����ϰ� ���� ��� ���ݷ¿� ���� ���ݷ��� �߰��Ͽ� ����Ѵ�.
	if (player->bEquip[EQ_ARMOR] == true) {
		cout << "���� : " << player->armorMin << " + " << player->iEquip[EQ_ARMOR].min
			<< " - " << player->armorMax << " + " << player->iEquip[EQ_ARMOR].max << endl;
	}
	else {
		cout << "���� : " << player->armorMin << " - " << player->armorMax << endl;
	}

	cout << "ü�� : " << player->HP << " / " <<
		player->HPMax << "\t���� : " << player->MP << " / " << player->MPMax << endl;

	if (player->bEquip[EQ_WEAPON] == true) {
		cout << "��������: " << player->iEquip[EQ_WEAPON].name;
	}
	else {
		cout << "��������: ����";
	}

	if (player->bEquip[EQ_ARMOR] == true) {
		cout << "\t������: " << player->iEquip[EQ_ARMOR].name << endl;
	}
	else {
		cout << "\t������: ����" << endl;
	}

	cout << "������� : " << player->inventory.gold << " Gold" << endl << endl;
}

void outputMonster(Monster* monster) {
	cout << "============================= Monster =============================" << endl;
	cout << "�̸� : " << monster->name << "\t���� : " <<
		monster->level << endl;

	cout << "���ݷ� : " << monster->attackMin << " - " <<
		monster->attackMax << "\t���� : " << monster->armorMin <<
		" - " << monster->armorMax << endl;
	cout << "ü�� : " << monster->HP << " / " <<
		monster->HPMax << "\t���� : " << monster->MP << " / " << monster->MPMax << endl;
	cout << "ȹ�����ġ : " << monster->exp << "\tȹ���� : " <<
		monster->goldMin << " - " << monster->goldMax << endl;
}

int outputBattleMenu() {
	cout << "1. ����" << endl;
	cout << "2. ��������" << endl;
	cout << "�޴��� �����ϼ��� : ";
	int menu = inputInt();

	if (menu == INT_MAX || menu <= BATTLE_NONE || menu > BATTLE_BACK)
		return BATTLE_NONE;

	return menu;
}

void battle(Player* player, Monster* monster) {
	int attackMin = player->attackMin;
	int attackMax = player->attackMax;

	if (player->bEquip[EQ_WEAPON] == true) {
		attackMin += player->iEquip[EQ_WEAPON].min;
		attackMax += player->iEquip[EQ_WEAPON].max;
	}

	int attack = rand() % (attackMax - attackMin + 1) + attackMin;
	int armor = rand() % (monster->armorMax - monster->armorMin + 1) + monster->armorMin;

	int damage = attack - armor;

	damage = damage < 1 ? 1 : damage;

	monster->HP -= damage;

	cout << player->name << "�� " << monster->name <<
		"���� " << damage << " ���ظ� �������ϴ�." << endl;

	// ���� �׾��� ���
	if (monster->HP <= 0) {
		cout << monster->name << " ���Ͱ� ����Ͽ����ϴ�." << endl;

		player->exp += monster->exp;
		int gold = (rand() % (monster->goldMax - monster->goldMin + 1) + monster->goldMin);
		player->inventory.gold += gold;

		cout << monster->exp << " ����ġ�� ȹ���Ͽ����ϴ�." << endl;
		cout << gold << " ��带 ȹ���Ͽ����ϴ�." << endl;

		monster->HP = monster->HPMax;
		monster->MP = monster->MPMax;

		if (player->exp >= levelUpExp[player->level - 1]) {
			player->exp -= levelUpExp[player->level - 1];
			player->level += 1;
			cout << "������ �ϼ̽��ϴ�." << endl;

			// �ɷ�ġ ���
			int jobIndex = player->job - 1;

			player->attackMin += levelUpTable[jobIndex].attackMin;
			player->attackMax += levelUpTable[jobIndex].attackMax;
			player->armorMin += levelUpTable[jobIndex].armorMin;
			player->armorMax += levelUpTable[jobIndex].armorMax;
			player->HPMax += levelUpTable[jobIndex].HPMax;
			player->MPMax += levelUpTable[jobIndex].MPMax;

			// ü�� ȸ��
			player->HP = player->HPMax;
			player->MP = player->MPMax;
		}

		return;
	}

	// ���Ͱ� ����ִٸ� �÷��̾ �����Ѵ�.
	attack = rand() % (monster->attackMax - monster->attackMin + 1) + monster->attackMin;

	int armorMin = player->armorMin;
	int armorMax = player->armorMax;

	if (player->bEquip[EQ_ARMOR] == true) {
		armorMin += player->iEquip[EQ_ARMOR].min;
		armorMax += player->iEquip[EQ_ARMOR].max;
	}

	armor = rand() % (armorMax - armorMin + 1) + armorMin;

	damage = attack - armor;

	damage = damage < 1 ? 1 : damage;

	player->HP -= damage;

	cout << monster->name << "�� " << player->name <<
		"���� " << damage << " ���ظ� �������ϴ�." << endl;

	if (player->HP <= 0) {
		cout << player->name << " �÷��̾ ����Ͽ����ϴ�." << endl;

		int exp = player->exp * 0.1f;
		int gold = player->inventory.gold * 0.1f;

		player->exp -= exp;
		player->inventory.gold -= gold;

		cout << exp << " ����ġ�� �Ҿ����ϴ�." << endl;
		cout << gold << " ��带 �Ҿ����ϴ�." << endl;

		player->HP = player->HPMax;
		player->MP = player->MPMax;

	}
}


void runBattle(Player* player, Monster* monsterArr, int menu) {
	Monster monster = monsterArr[menu - 1];

	while (true) {
		system("cls");
		outputBattleTag(menu);

		outputPlayer(player);
		outputMonster(&monster);

		switch (outputBattleMenu()) {
		case BATTLE_ATTACK:
			battle(player, &monster);
			system("pause");
			break;
		case BATTLE_BACK:
			return;
		}
	}
}

void runMap(Player* player, Monster* monsterArr) {
	bool loop = true;
	while (loop) {
		int menu = outputMapMenu();

		if (MT_BACK == menu)
			return;

		// ���� ����
		runBattle(player, monsterArr, menu);
	}
}

levelUpStatus createlvUPStatus(int attackMin, int attackMax,
	int armorMin, int armorMax,  int HPMax, int MPMax) 
{
	levelUpStatus status = {};

	status.attackMin = attackMin;
	status.attackMax = attackMax;
	status.armorMin = armorMin;
	status.armorMax = armorMax;
	status.HPMax = HPMax;
	status.MPMax = MPMax;

	return status;
}

int outputStoreMenu() {
	system("cls");
	cout << "**************************** ���� ****************************" << endl;
	cout << "1. �������" << endl;
	cout << "2. ������" << endl;
	cout << "3. �ڷΰ���" << endl;
	cout << "������ �����ϼ��� : ";
	int menu = inputInt();

	if (menu == INT_MAX || menu <= SM_NONE || menu > SM_BACK)
		return SM_NONE;

	return menu;
}

int outputStoreItemList(Inventory *inventory, Item *store, int itemCount, int storeType) {
	for (int i = 0; i < itemCount; i++) {
		cout << i + 1 << ". �̸� : " << store[i].name << endl;
		cout << "���� : " << store[i].typeName << endl;
		if (storeType == SM_WEAPON)
			cout << "���ݷ� : ";
		else
			cout << "���� : ";
		cout << store[i].min << " - " << store[i].max << endl;
		cout << "���Ű��� : " << store[i].price << endl;
		cout << "�ǸŰ��� : " << store[i].sell << endl;
		cout << "���� : " << store[i].desc << endl << endl;
	}

	cout << STORE_WEAPON_MAX + 1 << ". �ڷΰ���" << endl;
	cout << "�����ݾ� : " << inventory->gold << " Gold" << endl;
	cout << "�������� : " << INVENTORY_MAX - inventory->itemCount << endl;
	cout << "������ �������� �����ϼ��� : ";
	
	int menu = inputInt();

	if (menu == INT_MAX || menu  < 1 || menu > itemCount + 1)
		return INT_MAX;

	return menu;
}

void buyItem(Inventory* inventory, Item* store, int itemCount, int storeType) {
	while (true) {
		system("cls");
		switch (storeType) {
		case SM_WEAPON:
			cout << "**************************** ������� ****************************" << endl;
			break;
		case SM_ARMOR:
			cout << "**************************** ������ ****************************" << endl;
			break;
		}
		int input = outputStoreItemList(inventory, store, itemCount, storeType);

		if (input == INT_MAX)
		{
			cout << "�߸� �Է��Ͽ����ϴ�" << endl;
			system("pause");
			continue;
		}

		else if (input == itemCount + 1) {
			break;
		}

		int index = input - 1;

		if (inventory->itemCount == INVENTORY_MAX) {
			cout << "������ �� á���ϴ�." << endl;
			system("pause");
			continue;
		}
		else if (inventory->gold < store[index].price) {
			cout << "�����ݾ��� �����մϴ�." << endl;
			system("pause");
			continue;
		}

		inventory->gold -= store[index].price;
		inventory->items[inventory->itemCount] = store[index];
		inventory->itemCount += 1;

		cout << store[index].name << " �������� �����Ͽ����ϴ�." << endl;
		system("pause");
	}
}

void runStore(Inventory *inventory, Item *weapon, Item *armor) {
	while (true) {
		switch (outputStoreMenu()) {
		case SM_WEAPON:
			buyItem(inventory, weapon, STORE_WEAPON_MAX, SM_WEAPON);
			break;
		case SM_ARMOR:
			buyItem(inventory, armor, STORE_ARMOR_MAX, SM_ARMOR);
			break;
		case SM_BACK:
			return;
		}
	}
}

Item createItem(const char* name, ITEM_TYPE type, int min, int max, int price, int sell, const char* desc) {
	Item item = {};

	strcpy_s(item.name, name);
	item.type = type;

	switch (type) {
	case IT_WEAPON:
		strcpy_s(item.typeName, "����");
		break;
	case IT_ARMOR:
		strcpy_s(item.typeName, "��");
		break;
	}

	item.min = min;
	item.max = max;
	item.price = price;
	item.sell = sell;
	strcpy_s(item.desc, desc);

	return item;
}


int outputInventory(Player* player) {
	system("cls");
	cout << "**************************** ���� ****************************" << endl;

	outputPlayer(player);

	for (int i = 0; i < player->inventory.itemCount; i++) {
		cout << i + 1 << ". �̸� : " << player->inventory.items[i].name << endl;
		cout << "���� : " << player->inventory.items[i].typeName << endl;
		cout << "�ɷ�ġ : " << player->inventory.items[i].min << " - " << player->inventory.items[i].max << endl;
		cout << "���Ű��� : " << player->inventory.items[i].price << endl;
		cout << "�ǸŰ��� : " << player->inventory.items[i].sell << endl;
		cout << "���� : " << player->inventory.items[i].desc << endl << endl;
	}

	cout << player->inventory.itemCount + 1 << ". �ڷΰ���" << endl;
	cout << "������ �������� �����ϼ���" << endl;
	int menu = inputInt();

	 if (menu < 1 || menu > player->inventory.itemCount + 1) 
		return INT_MAX;
	
	 return menu;
}

EQUIP computeEquipType(ITEM_TYPE type) {
	EQUIP eq;
	switch (type) {
	case IT_WEAPON:
		eq = EQ_WEAPON;
		break;
	case IT_ARMOR:
		eq = EQ_ARMOR;
		break;
	}

	return eq;
}

void runInventory(Player *player) {
	while (true) {
		int input = outputInventory(player);

		if (input == INT_MAX)
			continue;

		else if (input == player->inventory.itemCount + 1)
			break;

		int idx = input - 1;

		EQUIP eq = computeEquipType(player->inventory.items[idx].type);

		// �������� �����Ǿ� �ִ� ���
		if (player->bEquip[eq] == true) {
			Item swap = player->iEquip[eq];
			player->iEquip[eq] = player->inventory.items[idx];
			player->inventory.items[idx] = swap;
		}
		// �������� �����Ǿ� ���� ���� ���
		else {
			player->iEquip[eq] = player->inventory.items[idx];
			for (int i = idx; i < player->inventory.itemCount - 1; i++) {
				player->inventory.items[i] = player->inventory.items[i + 1];
			}
			player->inventory.itemCount -= 1;
			player->bEquip[eq] = true;
		}

		cout << player->iEquip[eq].name << " �������� �����߽��ϴ�." << endl;

		system("pause");
	}

}

int main() {
	srand((unsigned int)time(0));

	Player player = {};

	// �÷��̾� ���� ����
	setPlayer(&player);

	// ���� ����
	Monster monsterArr[MT_BACK - 1] = {};

	setMonster(monsterArr);

	levelUpTable[JOB_KNIGHT - 1] = createlvUPStatus(4, 10, 8, 16, 150, 20);
	levelUpTable[JOB_ARCHER - 1] = createlvUPStatus(10, 15, 5, 10, 80, 40);
	levelUpTable[JOB_WIZARD - 1] = createlvUPStatus(15, 20, 3, 7, 50, 60);

	Item storeWeapon[STORE_WEAPON_MAX] = {};
	Item storeArmor[STORE_ARMOR_MAX] = {};

	storeWeapon[0] = createItem( "�����", IT_WEAPON, 10, 20, 1000, 500, "�Ѷ�꿡�� �ֿ� �����");
	storeWeapon[1] = createItem("�Ѷ�� Ȱ", IT_WEAPON, 20, 30, 3000, 1500, "���������� �Ѷ���� ����ϴ� ������ ���� Ȱ");
	storeWeapon[2] = createItem("���� ������", IT_WEAPON, 100, 150, 10000, 5000, "�� �����̷� ���ֵ��� ��������ٴ� ������ �ִ�");
	storeArmor[0] = createItem("õ����", IT_ARMOR, 2, 10, 1000, 500, "õ���� ���� ����");
	storeArmor[1] = createItem("���װ���", IT_ARMOR, 15, 30, 3000, 1500, "�������� ���� ����");
	storeArmor[2] = createItem("������ ����", IT_ARMOR, 50, 150, 10000, 5000, "����������� �ִ� ���������� ���� ����");


	bool loop = true;

	while (loop) {
		switch (outputMainMenu()) {
		case MM_MAP:
			runMap(&player, monsterArr);
			break;
		case MM_STORE:
			runStore(&player.inventory, storeWeapon, storeArmor);
			break;
		case MM_INVENTORY:
			runInventory(&player);
			break;
		case MM_EXIT:
			loop = false;
			break;
		}
	}

	return 0;
}