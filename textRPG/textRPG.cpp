#include <iostream>
#include <time.h>

/*
1. 무기상점에서 판매할 아이템 목록을 만들어주고 해당 목록을 출력해준다.
2. 출력할 때 앞에 번호를 부여해주고 번호를 입력받아서 해당 번호의 아이템을 구입하게 해준다. 가장 마지막 번호에 뒤로가기 기능을 만든다.
단, 가방이 꽉찼거나 돈이 부족할 경우 구매하지 못하게 한다.
3. 가방을 선택하면 가방안의 아이템을 보여준다.

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

	// 레벨업에 필요한 경험치 목록
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
		strcpy_s(player.jobName, "기사");
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
		strcpy_s(player.jobName, "궁수");
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
		strcpy_s(player.jobName, "마법사");
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

	// 몬스터 생성
	Monster monsterArray[MT_BACK - 1] = {};

	// 고블린 생성
	strcpy_s(monsterArray[0].name, "고블린");
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


	// 트롤 생성
	strcpy_s(monsterArray[1].name, "트롤");
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

	// 트롤 생성
	strcpy_s(monsterArray[2].name, "드래곤");
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

	// 상점에서 판매할 아이템 목록 생성
	Item storeWeapon[STORE_WEAPON_MAX] = {};
	Item storeArmor[STORE_ARMOR_MAX] = {};

	// 각 아이템 정보들을 설정
	strcpy_s(storeWeapon[0].name, "막대기");
	strcpy_s(storeWeapon[0].typeName, "무기");
	storeWeapon[0].type = IT_WEAPON;
	storeWeapon[0].min = 10;
	storeWeapon[0].max = 20;
	storeWeapon[0].price = 1000;
	storeWeapon[0].sell = 500;
	strcpy_s(storeWeapon[0].desc, "한라산에서 주운 막대기");

	strcpy_s(storeWeapon[1].name, "한라봉 활");
	strcpy_s(storeWeapon[1].typeName, "무기");
	storeWeapon[1].type = IT_WEAPON;
	storeWeapon[1].min = 20;
	storeWeapon[1].max = 30;
	storeWeapon[1].price = 3000;
	storeWeapon[1].sell = 1500;
	strcpy_s(storeWeapon[1].desc, "서귀포에서 한라봉을 재배하는 노인이 만든 활");

	strcpy_s(storeWeapon[2].name, "제주 지팡이");
	strcpy_s(storeWeapon[2].typeName, "무기");
	storeWeapon[2].type = IT_WEAPON;
	storeWeapon[2].min = 100;
	storeWeapon[2].max = 150;
	storeWeapon[2].price = 10000;
	storeWeapon[2].sell = 5000;
	strcpy_s(storeWeapon[2].desc, "이 지팡이로 제주도가 만들어졌다는 전설이 있다");
	
	strcpy_s(storeArmor[0].name, "천갑옷");
	strcpy_s(storeArmor[0].typeName, "방어구");
	storeArmor[0].type = IT_ARMOR;
	storeArmor[0].min = 2;
	storeArmor[0].max = 10;
	storeArmor[0].price = 1000;
	storeArmor[0].sell = 500;
	strcpy_s(storeArmor[0].desc, "천으로 만든 값옷");

	strcpy_s(storeArmor[1].name, "가죽갑옷");
	strcpy_s(storeArmor[1].typeName, "방어구");
	storeArmor[1].type = IT_ARMOR;
	storeArmor[1].min = 15;
	storeArmor[1].max = 30;
	storeArmor[1].price = 3000;
	storeArmor[1].sell = 1500;
	strcpy_s(storeArmor[1].desc, "가죽으로 만든 갑옷");

	strcpy_s(storeArmor[2].name, "현무암 갑옷");
	strcpy_s(storeArmor[2].typeName, "방어구");
	storeArmor[2].type = IT_ARMOR;
	storeArmor[2].min = 50;
	storeArmor[2].max = 150;
	storeArmor[2].price = 10000;
	storeArmor[2].sell = 5000;
	strcpy_s(storeArmor[2].desc, "성산일출봉에 있는 현무암으로 만든 갑옷");

	// 인벤토리

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
				cout << "**************************** 맵 ****************************" << endl;
				cout << "1. 쉬움" << endl;
				cout << "2. 보통" << endl;
				cout << "3. 어려움" << endl;
				cout << "4. 뒤로가기" << endl;
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
					cout << "이름 : " << player.name << "\t직업 : " <<
						player.jobName << endl;
					cout << "레벨 : " << player.level << "\t경험치 : " <<
						player.exp << "/" << levelUpExp[player.level-1] << endl;
					
					// 무기를 장착하고 있을 경우 공격력에 무기 공격력을 추가하여 출력한다.
					if (player.bEquip[EQ_WEAPON] == true) {
						cout << "공격력 : " << player.attackMin << " + " << player.iEquip[EQ_WEAPON].min
							<< " - " << player.attackMax << " + " << player.iEquip[EQ_WEAPON].max << endl;
					}
					else {
						cout << "공격력 : " << player.attackMin << " - " << player.attackMax << endl;
					}

					// 무기를 장착하고 있을 경우 공격력에 무기 공격력을 추가하여 출력한다.
					if (player.bEquip[EQ_ARMOR] == true) {
						cout << "방어력 : " << player.armorMin << " + " << player.iEquip[EQ_ARMOR].min
							<< " - " << player.armorMax << " + " << player.iEquip[EQ_ARMOR].max << endl;
					}
					else {
						cout << "방어력 : " << player.armorMin << " - " << player.armorMax << endl;
					}

					cout << "체력 : " << player.HP << " / " <<
						player.HPMax << "\t마나 : " << player.MP << " / " << player.MPMax << endl;

					if (player.bEquip[EQ_WEAPON] == true) {
						cout << "장착무기: " << player.iEquip[EQ_WEAPON].name;
					}
					else {
						cout << "장착무기: 없음";
					}

					if (player.bEquip[EQ_ARMOR] == true) {
						cout << "\t장착방어구: " << player.iEquip[EQ_ARMOR].name << endl;
					}
					else {
						cout << "\t장착방어구: 없음" << endl;
					}

					cout << "보유골드 : " << player.inventory.gold << " Gold" << endl;

					//몬스터 정보 출력
					cout << "============================= Monster =============================" << endl;
					cout << "이름 : " << monster.name << "\t레벨 : " <<
						monster.level << endl;

					cout << "공격력 : " << monster.attackMin << " - " <<
						monster.attackMax << "\t방어력 : " << monster.armorMin <<
						" - " << monster.armorMax << endl;
					cout << "체력 : " << monster.HP << " / " <<
						monster.HPMax << "\t마나 : " << monster.MP << " / " << monster.MPMax << endl;
					cout << "획득경험치 : " << monster.exp << "\t획득골드 : " <<
						monster.goldMin << " - " << monster.goldMax << endl;

					cout << "1. 공격" << endl;
					cout << "2. 도망가기" << endl;
					cout << "메뉴를 선택하세요 : ";
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

						cout << player.name << "가 " << monster.name <<
							"에게 " << damage << " 피해를 입혔습니다." << endl;

						// 몬스터 죽었을 경우
						if (monster.HP <= 0) {
							cout << monster.name << " 몬스터가 사망하였습니다." << endl;

							player.exp += monster.exp;
							int gold = (rand() % (monster.goldMax - monster.goldMin + 1) + monster.goldMin);
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

								player.attackMin += levelupTable[jobIndex].attackMin;
								player.attackMax += levelupTable[jobIndex].attackMax;
								player.armorMin += levelupTable[jobIndex].armorMin;
								player.attackMax += levelupTable[jobIndex].attackMax;
								player.HPMax += levelupTable[jobIndex].HPMax;
								player.MPMax += levelupTable[jobIndex].MPMax;
								
								// 체력 회복
								player.HP = player.HPMax;
								player.MP = player.MPMax;
							}



							system("pause");
							break;
						}

						// 몬스터가 살아있다면 플레이어를 공격한다.
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
						cout << "**************************** 무기상점 ****************************" << endl;
						// 판매 목록을 보여준다.
						for (int i = 0; i < STORE_WEAPON_MAX; i++) {
							cout << i + 1 << ". 이름 : " << storeWeapon[i].name << endl;
							cout << "종류 : " << storeWeapon[i].typeName << endl;
							cout << "공격력 : " << storeWeapon[i].min << " - " << storeWeapon[i].max << endl;
							cout << "구매가격 : " << storeWeapon[i].price << endl;
							cout << "판매가격 : " << storeWeapon[i].sell << endl;
							cout << "설명 : " << storeWeapon[i].desc << endl << endl;
						}

						cout << STORE_WEAPON_MAX + 1 << ". 뒤로가기" << endl;
						cout << "보유금액 : " << player.inventory.gold << " Gold" << endl;
						cout << "남은공간 : " << INVENTORY_MAX - player.inventory.itemCount << endl;
						cout << "구입할 아이템을 선택하세요 : ";
						cin >> menu;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}

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

						player.inventory.gold -= storeWeapon[weaponIndex].price;
						player.inventory.items[player.inventory.itemCount] = storeWeapon[weaponIndex];
						player.inventory.itemCount += 1;

						cout << storeWeapon[weaponIndex].name << " 아이템을 구매하였습니다." << endl;
						system("pause");
					}
					break;
				case(SM_ARMOR):
					while (true) 
					{
						system("cls");
						cout << "**************************** 방어구상점 ****************************" << endl;
						// 판매 목록을 보여준다.
						for (int i = 0; i < STORE_ARMOR_MAX; i++) {
							cout << i + 1 << ". 이름 : " << storeArmor[i].name << endl;
							cout << "종류 : " << storeArmor[i].typeName << endl;
							cout << "방어력 : " << storeArmor[i].min << " - " << storeArmor[i].max << endl;
							cout << "구매가격 : " << storeArmor[i].price << endl;
							cout << "판매가격 : " << storeArmor[i].sell << endl;
							cout << "설명 : " << storeArmor[i].desc << endl << endl;
						}
						cout << STORE_ARMOR_MAX + 1 << ". 뒤로가기" << endl;
						cout << "보유금액 : " << player.inventory.gold << " Gold" << endl;
						cout << "남은공간 : " << INVENTORY_MAX - player.inventory.itemCount << endl;
						cout << "구입할 아이템을 선택하세요 : ";
						cin >> menu;
						if (cin.fail()) {
							cin.clear();
							cin.ignore(1024, '\n');
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

						player.inventory.gold -= storeArmor[armorIndex].price;
						player.inventory.items[player.inventory.itemCount] = storeArmor[armorIndex];
						player.inventory.itemCount += 1;

						cout << storeArmor[armorIndex].name << " 아이템을 구매하였습니다." << endl;
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

				cout << "이름 : " << player.name << "\t직업 : " <<
					player.jobName << endl;
				cout << "레벨 : " << player.level << "\t경험치 : " <<
					player.exp << endl;

				// 무기를 장착하고 있을 경우 공격력에 무기 공격력을 추가하여 출력한다.
				if (player.bEquip[EQ_WEAPON] == true) {
					cout << "공격력 : " << player.attackMin << " + " << player.iEquip[EQ_WEAPON].min
						<< " - " << player.attackMax << " + " << player.iEquip[EQ_WEAPON].max << endl;
				}
				else {
					cout << "공격력 : " << player.attackMin << " - " << player.attackMax << endl;
				}

				// 무기를 장착하고 있을 경우 공격력에 무기 공격력을 추가하여 출력한다.
				if (player.bEquip[EQ_ARMOR] == true) {
					cout << "방어력 : " << player.armorMin << " + " << player.iEquip[EQ_ARMOR].min
						<< " - " << player.armorMax << " + " << player.iEquip[EQ_ARMOR].max << endl;
				}
				else {
					cout << "방어력 : " << player.armorMin << " - " << player.armorMax << endl;
				}

				cout << "체력 : " << player.HP << " / " <<
					player.HPMax << "\t마나 : " << player.MP << " / " << player.MPMax << endl;

				if (player.bEquip[EQ_WEAPON] == true) {
					cout << "장착무기: " << player.iEquip[EQ_WEAPON].name;
				}
				else {
					cout << "장착무기: 없음";
				}

				if (player.bEquip[EQ_ARMOR] == true) {
					cout << "\t장착방어구: " << player.iEquip[EQ_ARMOR].name << endl;
				}
				else {
					cout << "\t장착방어구: 없음" << endl;
				}

				cout << "보유골드 : " << player.inventory.gold << " Gold" << endl;

				cout << endl;

				for (int i = 0; i < player.inventory.itemCount; i++) {
					cout << i + 1 << ". 이름 : " << player.inventory.items[i].name << endl;
					cout << "종류 : " << player.inventory.items[i].typeName << endl;
					cout << "공격력 : " << player.inventory.items[i].min << " - " << player.inventory.items[i].max << endl;
					cout << "구매가격 : " << player.inventory.items[i].price << endl;
					cout << "판매가격 : " << player.inventory.items[i].sell << endl;
					cout << "설명 : " << player.inventory.items[i].desc << endl << endl;
				}

				cout << player.inventory.itemCount + 1 << ". 뒤로가기" << endl;
				cout << "장착할 아이템을 선택하세요" << endl;
				cin >> menu;

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
					cout << "아이템 장착되어 있지롱" << endl;
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