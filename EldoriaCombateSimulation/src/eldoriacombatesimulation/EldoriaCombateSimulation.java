package eldoriacombatesimulation;

import java.util.Scanner;

public class EldoriaCombateSimulation {

    public static void main(String[] args) {
        // 创建地图
        char[][] map = new char[10][10];

        // 初始化地图，填充为空地
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                map[i][j] = ' '; // 空地
            }
        }

        // 固定位置放置元素
        // 玩家初始位置
        int playerX = 1, playerY = 1;
        map[playerX][playerY] = 'O';

        // 宝箱及其周围敌人
        //map[1][3] = 'c';
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

        // 墙体布局
        for (int i = 0; i < 10; i++) {
            map[0][i] = 'T'; // 上边界
            map[9][i] = 'T'; // 下边界
            map[i][0] = 'T'; // 左边界
            map[i][9] = 'T'; // 右边界
        }

        Scanner scanner = new Scanner(System.in);
        boolean gameRunning = true;

        System.out.println("Choose your class:");
        System.out.println("1. Guard (战斗技能: 守卫, 治疗, 攻击速度, 战斗策略)");
        System.out.println("2. Scholar (学者: 治疗, 奥术视野)");
        System.out.println("3. Blackthorn (黑刺: 小偷, 毒爆, 生命吸取)");
        int playerClass = scanner.nextInt();
        scanner.nextLine(); // Consume newline

        int playerHP = 100;
        int playerAttack = 10;
        int playerSpeed = 5;
        int playerHealingPercentage = 0;
        int enemyPoisonedRounds = 0;
        boolean playerPoisonAttack = false;
        boolean playerLifeSteal = false;
        boolean playerGuardAttackSpeed = false;

        // 设置职业技能
        switch (playerClass) {
            case 1: // 守卫
                playerHealingPercentage = 20;
                playerGuardAttackSpeed = true;
                break;
            case 2: // 学者
                playerHealingPercentage = 40;
                System.out.println("奥术视野：你看到了敌人的战利品：金子、宝石、魔法药水。");
                break;
            case 3: // 黑刺
                playerPoisonAttack = true;
                playerLifeSteal = true;
                break;
            default:
                System.out.println("Invalid class choice.");
                return;
        }

        while (gameRunning) {
            // 打印地图
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    System.out.print("[" + map[i][j] + "]");
                }
                System.out.println();
            }

            System.out.println("Use W (up), A (left), S (down), D (right) to move. Type Q to quit.");
            char move = scanner.next().toUpperCase().charAt(0);

            // 玩家移动逻辑
            int newX = playerX;
            int newY = playerY;

            switch (move) {
                case 'W':
                    newX--;
                    break;
                case 'A':
                    newY--;
                    break;
                case 'S':
                    newX++;
                    break;
                case 'D':
                    newY++;
                    break;
                case 'Q':
                    gameRunning = false;
                    continue;
                default:
                    System.out.println("Invalid input. Use W, A, S, D, or Q.");
                    continue;
            }

            // 检查新位置是否合法
            if (newX < 0 || newX >= 10 || newY < 0 || newY >= 10 || map[newX][newY] == 'T') {
                System.out.println("You can't move there! Try a different direction.");
                continue;
            }

            // 检查是否遇到敌人
            if (map[newX][newY] == 'X') {
                System.out.println("Encountered an enemy! Do you want to fight? (1: Yes, 2: No)");
                int fightChoice = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                if (fightChoice == 1) {
                    System.out.println("Enemy Stats: HP: 80, Resistencia Física: 5, Resistencia Mágica: 15, Ataque: 15");
                    int enemyHP = 80;
                    int enemyAttack = 15;

                    int turnCount = 0;

                   // 战斗逻辑
int healCooldown = 4; // 初始冷却设置为-4，这样玩家开始时就可以使用技能
int attackSpeedCooldown = 4; // 初始冷却设置为-4
int poisonCooldown = 4; // 初始冷却设置为-4
int lifeStealCooldown = 4; // 初始冷却设置为-4

while (playerHP > 0 && enemyHP > 0) {
    turnCount++;
    healCooldown++;
    attackSpeedCooldown++;
    poisonCooldown++;
    lifeStealCooldown++;
    System.out.println("Turn " + turnCount);
    System.out.println("Battle in progress...");
    System.out.println("Player HP: " + playerHP);
    System.out.println("Enemy HP: " + enemyHP);

    // 玩家选择技能
    System.out.println("Choose your skill to use (0 to skip):");
    switch (playerClass) {
        case 1: // 守卫
            if (healCooldown >= 4) {
                System.out.println("1. Heal(20%)");
            }
            if (attackSpeedCooldown >= 4) {
                System.out.println("2. Increase attack");
            }
            break;
        case 2: // 学者
            if (healCooldown >= 4) {
                System.out.println("1. Heal(40%)");
            }
            break;
        case 3: // 黑刺
            if (poisonCooldown >= 4) {
                System.out.println("1. Poison");
            }
            if (lifeStealCooldown >= 4) {
                System.out.println("2. Life Steal");
            }
            break;
    }
    int skillChoice = scanner.nextInt();
    scanner.nextLine(); // Consume newline

    switch (skillChoice) {
        case 1: // Skill 1
            switch (playerClass) {
                case 1: // 守卫 Heal
                    if (healCooldown >= 4) {
                        int healAmount = playerHP * playerHealingPercentage / 100;
                        playerHP += healAmount;
                        System.out.println("You healed for " + healAmount + " HP.");
                        healCooldown = 0; // 重置治疗技能冷却时间
                    } else {
                        System.out.println("Heal is still on cooldown.");
                    }
                    break;
                case 2: // 学者 Heal
                    if (healCooldown >= 4) {
                        int healAmount = playerHP * playerHealingPercentage / 100;
                        playerHP += healAmount;
                        System.out.println("You healed for " + healAmount + " HP.");
                        healCooldown = 0; // 重置治疗技能冷却时间
                    } else {
                        System.out.println("Heal is still on cooldown.");
                    }
                    break;
                case 3: // 黑刺 Poison
                    if (poisonCooldown >= 4) {
                        enemyPoisonedRounds = 3; // 毒爆攻击
                        System.out.println("You poisoned the enemy for 10% damage each turn for 3 turns.");
                        poisonCooldown = 0; // 重置毒爆技能冷却时间
                    } else {
                        System.out.println("Poison is still on cooldown.");
                    }
                    break;
            }
            break;
        case 2: // Skill 2
            switch (playerClass) {
                case 1: // 守卫 Attack Speed
                    if (attackSpeedCooldown >= 4) {
                        playerAttack += 5;
                        System.out.println("Your attack speed increased, dealing more damage.");
                        attackSpeedCooldown = 0; // 重置攻击速度技能冷却时间
                    } else {
                        System.out.println("Increase attack is still on cooldown.");
                    }
                    break;
                case 3: // 黑刺 Life Steal
                    if (lifeStealCooldown >= 4) {
                        playerLifeSteal = true;
                        System.out.println("You will now steal 3% of the damage dealt as health.");
                        lifeStealCooldown = 0; // 重置生命吸取技能冷却时间
                    } else {
                        System.out.println("Life Steal is still on cooldown.");
                    }
                    break;
            }
            break;
        case 0:
            System.out.println("No skill used this turn.");
            break;
        default:
            System.out.println("Invalid skill choice.");
            continue;
    }

    // 敌人攻击
    playerHP -= enemyAttack;
    if (playerHP <= 0) {
        System.out.println("You have been defeated. Game Over.");
        System.out.println("Player HP: " + playerHP);
        System.out.println("Enemy HP: " + enemyHP);
        gameRunning = false;
        break;
    }

    // 玩家攻击
    enemyHP -= playerAttack;
    if (playerPoisonAttack) {
        enemyPoisonedRounds = 3; // 毒爆攻击
    }
    if (playerLifeSteal) {
        playerHP += playerAttack * 0.03; // 生命吸取
    }

    // 处理敌人中毒回合
    if (enemyPoisonedRounds > 0) {
        enemyHP -= enemyHP * 0.1; // 每回合毒敌人10%的血量
        enemyPoisonedRounds--;
    }

    if (enemyHP <= 0) {
        System.out.println("You defeated the enemy!");
        System.out.println("Player HP: " + playerHP);
        System.out.println("Enemy HP: " + enemyHP);
        if (playerClass == 3) {
            System.out.println("黑刺技能生效：你获得了双倍战利品！");
        }
        map[newX][newY] = ' '; // 敌人消失
        map[playerX][playerY] = ' '; // 清除旧位置
        playerX = newX;
        playerY = newY;
        map[playerX][playerY] = 'O'; // 设置新位置
        break;
    }

    try {
        Thread.sleep(1000); // 1秒等待
    } catch (InterruptedException e) {
        Thread.currentThread().interrupt();
    }
}
                } else {
                    System.out.println("Retreating to previous position.");
                    continue; // 回到原位置
                }
            }else if(map[newX][newY] == 'c'){
                    
                    System.out.println("Has obtenido 2 x gemas, 3 x moneda");
                }

            // 更新玩家位置
            map[playerX][playerY] = ' '; // 清除旧位置
            playerX = newX;
            playerY = newY;
            map[playerX][playerY] = 'O'; // 设置新位置
        }

        System.out.println("Game Over.");
        scanner.close();
    }
}
