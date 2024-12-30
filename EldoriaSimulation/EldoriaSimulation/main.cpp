#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <cstring> 
#include <iostream>
#define MAP_SIZE 10

void initializeMap(char map[MAP_SIZE][MAP_SIZE]) {
	// Initialize map with empty spaces
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			map[i][j] = ' ';
		}
	}
}

void setupMap(char map[MAP_SIZE][MAP_SIZE]) {
	// Set up walls
	for (int i = 0; i < MAP_SIZE; i++) {
		map[0][i] = 'T';
		map[MAP_SIZE - 1][i] = 'T';
		map[i][0] = 'T';
		map[i][MAP_SIZE - 1] = 'T';
	}

	// Set up chests and enemies

	map[3][3] = 'c';
	map[2][3] = 'X';
	map[4][3] = 'X';
	map[3][2] = 'T';
	map[3][4] = 'T';

	map[6][6] = 'c';
	map[5][6] = 'X';
	map[7][6] = 'X';
	map[6][5] = 'T';
	map[6][7] = 'T';
}

void printMap(char map[MAP_SIZE][MAP_SIZE]) {
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			printf("[%c]", map[i][j]);
		}
		printf("\n");
	}
}

// 定义一个结构体，用来存储宝物
typedef struct {
    char** treasures;  // 存储宝物名字的指针数组
    int count;         // 存储宝物数量
} TreasureArray;

// 函数：初始化宝物数组
void initTreasureArray(TreasureArray* treasureArray, int maxCount) {
    if (treasureArray != NULL) {
        treasureArray->treasures = (char**)malloc(sizeof(char*) * maxCount);
        if (treasureArray->treasures == NULL) {
            printf("Memory allocation failed!\n");
            return;  // 如果内存分配失败，则返回
        }
        treasureArray->count = 0;
    }
}

// 函数：添加宝物到数组
void addTreasure(TreasureArray* treasureArray, const char* treasure) {
    if (treasureArray == NULL || treasure == NULL) return;

    // 为新宝物分配内存并复制内容
    treasureArray->treasures[treasureArray->count] = (char*)malloc(strlen(treasure) + 1);
    if (treasureArray->treasures[treasureArray->count] == NULL) {
        printf("Memory allocation failed for treasure: %s\n", treasure);
        return;  // 如果内存分配失败，则返回
    }

    strcpy_s(treasureArray->treasures[treasureArray->count], strlen(treasure) + 1, treasure);
    treasureArray->count++;
}

// 函数：获取并打印所有宝物
void printTreasures(TreasureArray* treasureArray) {
	if (treasureArray->count == 0) {
		printf("No item get.\n");
		return;
	}
	printf("You final get:\n");
	for (int i = 0; i < treasureArray->count; i++) {
		printf("%d: %s\n", i + 1, treasureArray->treasures[i]);
	}
}

// 函数：释放宝物数组占用的内存
void freeTreasureArray(TreasureArray* treasureArray) {
    if (treasureArray != NULL) {
        for (int i = 0; i < treasureArray->count; i++) {
            free(treasureArray->treasures[i]);
        }
        free(treasureArray->treasures);
        treasureArray->treasures = NULL;  // 清空指针，防止悬挂指针
    }
}


int main() {
	char map[MAP_SIZE][MAP_SIZE];
	int playerX = 1, playerY = 1;
	bool gameRunning = true;
	char input;
	const char* items[] = { "Monedas", "Gemas", "Armas", "Armaduras" };
	int numItems = sizeof(items) / sizeof(items[0]); // 获取数组大小
	srand(time(NULL));

	TreasureArray myTreasures;

	initTreasureArray(&myTreasures, 10);

	// Player stats
	int playerHP = 100;
	int playerAttack = 10;
	int playerSpeed = 5;
	int playDenfense = 5;
	int playerHealingPercentage = 0;
	int enemyPoisonedRounds = 0;
	bool playerPoisonAttack = false;
	bool playerLifeSteal = false;
	bool playerGuardAttackSpeed = false;
	bool playerReduceEnemyAtack = false;

	initializeMap(map);
	setupMap(map);
	map[playerX][playerY] = 'O';

	printf("Choose your class:\n");
	printf("1. Guardian (Defensa, Curación, Aumento de ataque)\n");
	printf("2. Eruditos (Curación, Reducción de daño)\n");
	printf("3. Espina Negra (Explosión de veneno, Robo de vida)\n");

	int playerClass;
	scanf_s("%d", &playerClass);
	getchar(); // Consume newline

	switch (playerClass) {
	case 1:
		playerHealingPercentage = 20;
		playerReduceEnemyAtack = true;
		break;
	case 2:
		playerHealingPercentage = 40;
		//printf("奥术视野：你看到了敌人的战利品：金子、宝石、魔法药水。\n");
		break;
	case 3:
		playerPoisonAttack = true;
		playerLifeSteal = true;
		break;
	default:
		printf("Invalid class choice.\n");
		return 1;
	}

	while (gameRunning) {
		printMap(map);
		printf("Use W (up), A (left), S (down), D (right) to move. Type Q to quit.\n");

		scanf_s(" %c", &input);
		input = toupper(input);

		int newX = playerX;
		int newY = playerY;

		switch (input) {
		case 'W': newX--; break;
		case 'A': newY--; break;
		case 'S': newX++; break;
		case 'D': newY++; break;
		case 'Q':
			gameRunning = false;
			continue;
		default:
			printf("Invalid input. Use W, A, S, D, or Q.\n");
			continue;
		}

		if (newX < 0 || newX >= MAP_SIZE || newY < 0 || newY >= MAP_SIZE || map[newX][newY] == 'T') {
			printf("You can't move there! Try a different direction.\n");
			continue;
		}

		if (map[newX][newY] == 'X') {
			printf("Encountered an enemy! Do you want to fight? (1: Yes, 2: No)\n");
			int fightChoice;
			scanf_s("%d", &fightChoice);
			getchar();

			if (fightChoice == 1) {
				int enemyHP = 80;
				int enemyAttack = 15;
				int enemyDenfense = 8;
				int turnCount = 0;
				int healCooldown = 4; // Initial cooldown for healing
				int attackSpeedCooldown = 4; // Initial cooldown for attack speed
				int poisonCooldown = 4; // Initial cooldown for poison
				int lifeStealCooldown = 4; // Initial cooldown for life steal
				int enemyAtackReduceCooldown = 4; // Initial cooldown for life steal

				printf("Enemy Stats: HP: 80, Resistencia Física: 5, Resistencia Mágica: 15, Ataque: 15\n");

				while (playerHP > 0 && enemyHP > 0) {
					turnCount++;
					healCooldown++;
					attackSpeedCooldown++;
					poisonCooldown++;
					lifeStealCooldown++;
					enemyAtackReduceCooldown++;


					printf("Turn %d\n", turnCount);
					printf("Battle in progress...\n");
					printf("Player HP: %d\n", playerHP);
					printf("Enemy HP: %d\n", enemyHP);

					// Player chooses skill
					printf("Choose your skill to use (0 to skip):\n");
					if (playerClass == 1) { // Guard
						if (healCooldown >= 4) {
							printf("1. Heal(20%%)\n");
						}
						if (attackSpeedCooldown >= 4) {
							printf("2. Increase attack\n");
						}
					}
					else if (playerClass == 2) { // Scholar
						if (healCooldown >= 4) {
							printf("1. Heal(40%%)\n");
						}
						if (enemyAtackReduceCooldown >= 4) {
							printf("2. decreased enemy attack\n");
						}
					}
					else if (playerClass == 3) { // Blackthorn
						if (poisonCooldown >= 4) {
							printf("1. Poison\n");
						}
						if (lifeStealCooldown >= 4) {
							printf("2. Life Steal\n");
						}
					}

					int skillChoice;
					scanf_s("%d", &skillChoice);
					getchar(); // Consume newline

					switch (skillChoice) {
					case 1: // Skill 1
						if (playerClass == 1 || playerClass == 2) { // Guard or Scholar Heal
							if (healCooldown >= 4) {
								int healAmount = playerHP * playerHealingPercentage / 100;
								playerHP += healAmount;
								printf("You healed for %d HP.\n", healAmount);
								healCooldown = 0; // Reset heal cooldown
							}
							else {
								printf("Heal is still on cooldown.\n");
							}
						}
						else if (playerClass == 3) { // Blackthorn Poison
							if (poisonCooldown >= 4) {
								enemyPoisonedRounds = 3; // Poison attack
								printf("You poisoned the enemy for 10%% damage each turn for 3 turns.\n");
								poisonCooldown = 0; // Reset poison cooldown
							}
							else {
								printf("Poison is still on cooldown.\n");
							}
						}
						break;
					case 2: // Skill 2
						if (playerClass == 1) { // Guard Attack Speed
							if (attackSpeedCooldown >= 4) {
								playerAttack += 5;
								printf("Your attack speed increased, dealing more damage.\n");
								attackSpeedCooldown = 0; // Reset attack speed cooldown
							}
							else {
								printf("Increase attack is still on cooldown.\n");
							}
						}
						else if (playerClass == 2) { // Blackthorn Life Steal
							if (enemyAtackReduceCooldown >= 4) {
								enemyAttack -= 3;
								printf("The enemy's attack power has decreased, and the current attack power of the enemy is: %d\n", enemyAttack);
								enemyAtackReduceCooldown = 0; // Reset life steal cooldown
							}
							else {
								printf("Life Steal is still on cooldown.\n");
							}
						}
						else if (playerClass == 3) { // Blackthorn Life Steal
							if (lifeStealCooldown >= 4) {
								playerLifeSteal = true;
								printf("You will now steal 3%% of the damage dealt as health.\n");
								lifeStealCooldown = 0; // Reset life steal cooldown
							}
							else {
								printf("Life Steal is still on cooldown.\n");
							}
						}
						break;
					case 0:
						printf("No skill used this turn.\n");
						break;
					default:
						printf("Invalid skill choice.\n");
						continue;
					}

					// Enemy attacks
					playerHP -= (enemyAttack-playDenfense);
					if (playerHP <= 0) {
						printf("You have been defeated.\n");
						gameRunning = false;
						break;
					}

					// Player attacks
					enemyHP -= (playerAttack-enemyDenfense);
					if (playerPoisonAttack) {
						enemyPoisonedRounds = 3; // Poison attack
					}
					if (playerLifeSteal) {
						playerHP += playerAttack * 0.03; // Life steal
					}

					// Handle enemy poisoned rounds
					if (enemyPoisonedRounds > 0) {
						enemyHP -= enemyHP * 0.1; // Poison enemy for 10% of their health
						enemyPoisonedRounds--;
					}

					if (enemyHP <= 0) {
						// 随机选择一个掉落物
						int randomIndex = rand() % numItems;
						printf("You defeated the enemy!\n");
						// 打印掉落结果
						printf("You get: %s\n", items[randomIndex]);
						addTreasure(&myTreasures, items[randomIndex]);
						map[newX][newY] = ' '; // Enemy disappears
						map[playerX][playerY] = ' '; // Clear old position
						playerX = newX;
						playerY = newY;
						map[playerX][playerY] = 'O'; // Set new position
						break;
					}


				}
			}
			else {
				printf("Retreating to previous position.\n");
				continue;
			}
		}
		else if (map[newX][newY] == 'c') {
			// 随机选择一个掉落物
			int randomIndex = rand() % numItems;

			// 打印掉落结果
			printf("You get: %s\n", items[randomIndex]);
			addTreasure(&myTreasures, items[randomIndex]);
			//printf("Has obtenido 2 x gemas, 3 x moneda\n");
		}

		// Update player position
		map[playerX][playerY] = ' '; // Clear old position
		playerX = newX;
		playerY = newY;
		map[playerX][playerY] = 'O'; // Set new position
	}
	if (playerHP >= 0) {
		printTreasures(&myTreasures);
	}
	freeTreasureArray(&myTreasures);
	printf("Game Over.\n");
	return 0;
}
