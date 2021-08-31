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

	// 레벨업에 필요한 경험치 목록
	const int levelUpExp[LEVEL_MAX] = {4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000};

	levelUpStatus levelUpTable[JOB_END - 1] = {};

	levelUpSet(levelUpTable, JOB_KNIGHT, 4, 10, 8, 16, 150, 20);
	levelUpSet(levelUpTable, JOB_ARCHER, 10, 15, 5, 10, 80, 40);
	levelUpSet(levelUpTable, JOB_WIZARD, 15, 20, 3, 7, 50, 60);

	Player player = {};

	cout << "이름 : ";
	cin.getline(player.name, NAME_SIZE - 1);

	int job = JOB_NONE;
	while (job == JOB_NONE) 
	{
		system("cls");
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요 : ";

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
		jobAbilitySet(player, "기사", 5, 10, 15, 20, 500, 500, 100, 100);
		break;
	case JOB_ARCHER:
		jobAbilitySet(player, "궁수", 10, 15, 10, 15, 400, 400, 200, 200);
		break;
	case JOB_WIZARD:
		jobAbilitySet(player, "마법사", 15, 20, 5, 10, 300, 300, 300, 300);
		break;
	}

	// 몬스터 생성
	Monster monsterArray[MT_BACK - 1] = {};

	// 고블린 생성
	monsterAbilitySet(monsterArray[0], "고블린", 20, 30, 2, 5, 100, 100, 10, 10, 1, 1000, 500, 1500);

	// 트롤 생성
	monsterAbilitySet(monsterArray[1], "트롤", 80, 130, 60, 90, 2000, 2000, 100, 100, 5, 7000, 6000, 8000);

	// 트롤 생성
	monsterAbilitySet(monsterArray[2], "드래곤", 250, 500, 200, 400, 30000, 30000, 20000, 20000, 10, 30000, 20000, 50000);


	// 상점에서 판매할 아이템 목록 생성
	Item storeWeapon[STORE_WEAPON_MAX] = {};
	Item storeArmor[STORE_ARMOR_MAX] = {};

	// 각 아이템 정보들을 설정
	itemSet(storeWeapon[0], "막대기", "무기", IT_WEAPON, 10, 20, 1000, 500, "한라산에서 주운 막대기");
	itemSet(storeWeapon[1], "한라봉 활", "무기", IT_WEAPON, 20, 30, 3000, 1500, "서귀포에서 한라봉을 재배하는 노인이 만든 활");
	itemSet(storeWeapon[2], "제주 지팡이", "무기", IT_WEAPON, 100, 150, 10000, 5000, "이 지팡이로 제주도가 만들어졌다는 전설이 있다");
	itemSet(storeArmor[0], "천갑옷", "방어구", IT_ARMOR, 2, 10, 1000, 500, "천으로 만든 값옷");
	itemSet(storeArmor[1], "가죽갑옷", "방어구", IT_ARMOR, 15, 30, 3000, 1500, "가죽으로 만든 갑옷");
	itemSet(storeArmor[2], "현무암 갑옷", "방어구", IT_ARMOR, 50, 150, 10000, 5000, "성산일출봉에 있는 현무암으로 만든 갑옷");


	while (true)
	{
		system("cls");
		cout << "**************************** 로비 ****************************" << endl;
		cout << "1. 맵" << endl;
		cout << "2. 상점" << endl;
		cout << "3. 가방" << endl;
		cout << "4. 종료" << endl;

		cout << "메뉴를 선택하세요 : ";

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
				cout << "**************************** 맵 ****************************" << endl;
				cout << "1. 쉬움" << endl;
				cout << "2. 보통" << endl;
				cout << "3. 어려움" << endl;
				cout << "4. 뒤로가기" << endl;
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
						cout << "**************************** 쉬움 ****************************" << endl;
						break;
					case MT_NORMAL:
						cout << "**************************** 보통 ****************************" << endl;
						break;
					case MT_HARD:
						cout << "**************************** 어려움 ****************************" << endl;
						break;
					}
					// 플레이어 정보 출력
					cout << "============================= Player =============================" << endl;
					playerInfoPrint(player, levelUpExp);

					//몬스터 정보 출력
					cout << "============================= Monster =============================" << endl;
					monsterInfoPrint(monster);

					cout << "1. 공격" << endl;
					cout << "2. 도망가기" << endl;
					cout << "메뉴를 선택하세요 : ";
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

						cout << player.name << "가 " << monster.name <<
							"에게 " << damage << " 피해를 입혔습니다." << endl;

						// 몬스터 죽었을 경우
						if (monster.HP <= 0) {
							cout << monster.name << " 몬스터가 사망하였습니다." << endl;

							player.exp += monster.exp;
							int gold = random(monster.goldMax, monster.goldMin);
							player.inventory.gold += gold;

							cout << monster.exp << " 경험치를 획득하였습니다." << endl;
							cout << gold << " 골드를 획득하였습니다." << endl;

							monster.HP = monster.HPMax;
							monster.MP = monster.MPMax;

							if (player.exp >= levelUpExp[player.level - 1]) {
								player.exp -= levelUpExp[player.level - 1];
								player.level += 1;
								cout << "레벨업 하셨습니다." << endl;
							
								// 능력치 상승
								int jobIndex = player.job - 1;

								player.attackMin += levelUpTable[jobIndex].attackMin;
								player.attackMax += levelUpTable[jobIndex].attackMax;
								player.armorMin += levelUpTable[jobIndex].armorMin;
								player.armorMax += levelUpTable[jobIndex].armorMax;
								player.HPMax += levelUpTable[jobIndex].HPMax;
								player.MPMax += levelUpTable[jobIndex].MPMax;
								
								// 체력 회복
								player.HP = player.HPMax;
								player.MP = player.MPMax;
							}

							system("pause");
							break;
						}

						// 몬스터가 살아있다면 플레이어를 공격한다.
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

						cout << monster.name << "가 " << player.name <<
							"에게 " << damage << " 피해를 입혔습니다." << endl;

						if (player.HP <= 0) {
							cout << player.name << " 플레이어가 사망하였습니다." << endl;

							int exp = player.exp * 0.1f;
							int gold = player.inventory.gold * 0.1f;

							player.exp -= exp;
							player.inventory.gold -= gold;

							cout << exp << " 경험치를 잃었습니다." << endl;
							cout << gold << " 골드를 잃었습니다." << endl;

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
				cout << "**************************** 상점 ****************************" << endl;
				cout << "1. 무기상점" << endl;
				cout << "2. 방어구상점" << endl;
				cout << "3. 뒤로가기" << endl;
				cout << "상점을 선택하세요 : ";
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
						cout << "**************************** 무기상점 ****************************" << endl;
						// 판매 목록을 보여준다.
						ItemPrint(storeWeapon, player, STORE_WEAPON_MAX, "공격력");
						cout << "보유금액 : " << player.inventory.gold << " Gold" << endl;
						cout << "남은공간 : " << INVENTORY_MAX - player.inventory.itemCount << endl;
						cout << "구입할 아이템을 선택하세요 : ";

						menu = inputInt();
						
						if (menu == INT_MAX)
							continue;

						else if (menu == STORE_WEAPON_MAX + 1)
							break;

						else if (menu < 1 || menu > STORE_WEAPON_MAX + 1) {
							cout << "잘못 선택하였습니다." << endl;
							system("pause");
							continue;
						}

						int weaponIndex = menu - 1;

						if (player.inventory.itemCount == INVENTORY_MAX) {
							cout << "가방이 꽉 찼습니다." << endl;
							system("pause");
							continue;
						}
						else if (player.inventory.gold < storeWeapon[weaponIndex].price) {
							cout << "보유금액이 부족합니다." << endl;
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
						cout << "**************************** 방어구상점 ****************************" << endl;
						// 판매 목록을 보여준다.
						ItemPrint(storeArmor, player, STORE_ARMOR_MAX, "방어력");
						cout << "보유금액 : " << player.inventory.gold << " Gold" << endl;
						cout << "남은공간 : " << INVENTORY_MAX - player.inventory.itemCount << endl;
						cout << "구입할 아이템을 선택하세요 : ";
						
						menu = inputInt();
						if (menu == INT_MAX) {
							continue;
						}

						else if (menu == STORE_ARMOR_MAX + 1)
							break;

						else if (menu < 1 || menu > STORE_ARMOR_MAX + 1) {
							cout << "잘못 선택하였습니다." << endl;
							system("pause");
							continue;
						}

						int armorIndex = menu - 1;

						if (player.inventory.itemCount == INVENTORY_MAX) {
							cout << "가방이 꽉 찼습니다." << endl;
							system("pause");
							continue;
						}
						else if (player.inventory.gold < storeArmor[armorIndex].price) {
							cout << "보유금액이 부족합니다." << endl;
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
				cout << "**************************** 가방 ****************************" << endl;

				playerInfoPrint(player, levelUpExp);

				cout << endl;

				ItemPrint(player.inventory.items, player, player.inventory.itemCount, "능력치");
				cout << "장착할 아이템을 선택하세요" << endl;

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
					cout << "잘못 선택하였습니다" << endl;
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

				// 아이템이 장착되어 있는 경우
				if (player.bEquip[eq] == true) {
					Item swap = player.iEquip[eq];
					player.iEquip[eq] = player.inventory.items[idx];
					player.inventory.items[idx] = swap;
				}
				// 아이템이 장착되어 있지 않은 경우
				else {
					player.iEquip[eq] = player.inventory.items[idx];
					for (int i = idx; i < player.inventory.itemCount-1; i++) {
						player.inventory.items[i] = player.inventory.items[i + 1];
					}
					player.inventory.itemCount -= 1;
					player.bEquip[eq] = true;
				}

				cout << player.iEquip[eq].name << " 아이템을 장착했습니다." << endl;

				system("pause");
			}
			break;
		default:
			cout << "잘못 선택하였습니다" << endl;
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
	std::cout << "이름 : " << player.name << "\t직업 : " <<
		player.jobName << endl;
	std::cout << "레벨 : " << player.level << "\t경험치 : " <<
		player.exp << "/" << levelUpExp[player.level - 1] << std::endl;

	// 무기를 장착하고 있을 경우 공격력에 무기 공격력을 추가하여 출력한다.
	if (player.bEquip[EQ_WEAPON] == true) {
		std::cout << "공격력 : " << player.attackMin << " + " << player.iEquip[EQ_WEAPON].min
			<< " - " << player.attackMax << " + " << player.iEquip[EQ_WEAPON].max << std::endl;
	}
	else {
		std::cout << "공격력 : " << player.attackMin << " - " << player.attackMax << std::endl;
	}

	// 방어구를 장착하고 있을 경우 방어력에 방어구 방어력을 추가하여 출력한다.
	if (player.bEquip[EQ_ARMOR] == true) {
		std::cout << "방어력 : " << player.armorMin << " + " << player.iEquip[EQ_ARMOR].min
			<< " - " << player.armorMax << " + " << player.iEquip[EQ_ARMOR].max << std::endl;
	}
	else {
		std::cout << "방어력 : " << player.armorMin << " - " << player.armorMax << std::endl;
	}

	std::cout << "체력 : " << player.HP << " / " <<
		player.HPMax << "\t마나 : " << player.MP << " / " << player.MPMax << std::endl;

	if (player.bEquip[EQ_WEAPON] == true) {
		std::cout << "장착무기: " << player.iEquip[EQ_WEAPON].name;
	}
	else {
		std::cout << "장착무기: 없음";
	}

	if (player.bEquip[EQ_ARMOR] == true) {
		std::cout << "\t장착방어구: " << player.iEquip[EQ_ARMOR].name << std::endl;
	}
	else {
		std::cout << "\t장착방어구: 없음" << std::endl;
	}

	std::cout << "보유골드 : " << player.inventory.gold << " Gold" << std::endl;
}

void monsterInfoPrint(Monster &monster) {
	std::cout << "이름 : " << monster.name << "\t레벨 : " <<
		monster.level << std::endl;
	std::cout << "공격력 : " << monster.attackMin << " - " <<
		monster.attackMax << "\t방어력 : " << monster.armorMin <<
		" - " << monster.armorMax << std::endl;
	std::cout << "체력 : " << monster.HP << " / " <<
		monster.HPMax << " \t마나 : " << monster.MP << " / " << monster.MPMax << std::endl;
	std::cout << "획득경험치 : " << monster.exp << "\t획득골드 : " <<
		monster.goldMin << " - " << monster.goldMax << std::endl;
}

int random(int a, int b) {
	return rand() % (a - b + 1) + b;
}

void ItemPrint(Item *types, Player &player, int max, const char *ability) {
	for (int i = 0; i < max; i++) {
		std::cout << i + 1 << ". 이름 : " << types[i].name << std::endl;
		std::cout << "종류 : " << types[i].typeName << std::endl;
		std::cout << ability << " : " << types[i].min << " - " << types[i].max << std::endl;
		std::cout << "구매가격 : " << types[i].price << std::endl;
		std::cout << "판매가격 : " << types[i].sell << std::endl;
		std::cout << "설명 : " << types[i].desc << std::endl << std::endl;
	}
	std::cout << max + 1 << ". 뒤로가기" << std::endl;
}

void storeCalc(int index, Item *types, Player &player) {
	player.inventory.gold -= types[index].price;
	player.inventory.items[player.inventory.itemCount] = types[index];
	player.inventory.itemCount += 1;

	std::cout << types[index].name << " 아이템을 구매하였습니다." << std::endl;
}

int inputInt() {
	int input;
	cin >> input;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX; // INT_MAX가 리턴되면 입력이 잘못됐다는 의미
	}
	return input;
}