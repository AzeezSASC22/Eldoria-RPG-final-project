#include "enemy.h"
#include "dice.h"
#include <cstdlib>
#include <unistd.h>

using namespace std;

// base enemy setup. the parent class of all to come.
Enemy::Enemy(string n, int h, int atk, int exp, string loot, string intro) {
    name = n; hp = h; maxHp = h; attack = atk; expReward = exp; lootDrop = loot; introText = intro; turnCount = 0;
}

string Enemy::getName() { return name; }
int Enemy::getHp() { return hp; }
int Enemy::getMaxHp() { return maxHp; }
int Enemy::getAttack() { return attack; }
int Enemy::getExpReward() { return expReward; }
string Enemy::getLootDrop() { return lootDrop; }
bool Enemy::isAlive() { return hp > 0; }
int Enemy::getTurnCount() { return turnCount; }

void Enemy::setHp(int h) { hp = h; }
void Enemy::setAttack(int a) { attack = a; }
void Enemy::incrementTurn() { turnCount += 1; }

void Enemy::takeDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) {
        hp = 0;
    }
    cout << name << " takes " << dmg << " damage! (" << hp << "/" << maxHp << " HP remaining)\n";
    usleep(1000000);
}

int Enemy::rollAttack() { //a random amount of attack to be more threatening to the player because of unpredictability
    return (rand() % attack) + 1; 
}

void Enemy::displayStatus() { 
    cout << "[ " << name << " | HP: " << hp << "/" << maxHp << " | ATK: " << attack << " ]\n"; 
}

void Enemy::battleIntro() { 
    if (introText != "") { 
        cout << introText << "\n"; 
    } else { 
        cout << "A " << name << " appears!\n"; 
    }
    usleep(1000000);
}

void Enemy::specialAbility() { }
void Enemy::takeTurn() { incrementTurn(); }
void Enemy::aldricAssist() { }

// main combat logic
bool runCombat(Player& player, Enemy& mob, bool allowEscape, bool aldricHelps) {
    mob.battleIntro();

    while (mob.isAlive() && player.hp > 0) {
        mob.specialAbility();
        
        cout << "\n------------------------------------------------------\n";
        cout << " " << player.name << " (YOU): " << player.hp << " / " << player.maxHp << " HP\n";
        cout << " [" << mob.getName() << "]: " << mob.getHp() << " / " << mob.getMaxHp() << " HP\n";
        cout << "------------------------------------------------------\n";
        usleep(1000000);
        
        cout << "1. Attack  2. Attempt Escape  3. Use Item\nChoice: ";
        string combatChoice;
        cin >> combatChoice;

        if (combatChoice == "2") {
            if (allowEscape == false) { // these are for mini bosses and dragon fight and etc. Escape doesn't make sense to the story
                cout << "\n[!] Escape is impossible here!\n";
                usleep(1000000);
            } else {
                cout << "\nYou look for an opening to escape... (Stealth Check vs DC 12)\n";
                usleep(1000000);
                if (diceRoll(player.stealth, 12) == 1) {
                    cout << "[SUCCESS] You backstep and escape the fight.\n";
                    usleep(1000000);
                    return true; 
                } else {
                    cout << "[FAILED] The enemy strikes your exposed stance!\n";
                    usleep(1000000);
                }
            }
        } 
        else if (combatChoice == "3") {
            if (player.inventory.size() == 0) {
                cout << "\nNo items available!\n";
                usleep(1000000);
            } else {
                player.showInventory();
                cout << "0. Cancel | Choose Item Number: ";
                string itemChoiceStr; 
                cin >> itemChoiceStr;
                
                bool itemUsed = false; //after item used, enemy should get a turn as using item counts as a turn.
                
                // checking inventory and using item
                for (int i = 0; i < player.inventory.size(); i++) {
                    string numberString = to_string(i + 1); //number type needs to be converted to check
                    if (itemChoiceStr == numberString) {
                        string item = player.inventory[i];
                        
                        if (item == "Healing Potion") {
                            cout << "\nYou uncap a potion and drink it down!\n";
                            usleep(1000000);
                            player.heal(40);
                            player.inventory.erase(player.inventory.begin() + i);
                            itemUsed = true;
                            break;
                        } else if (item == "Bomb") {
                            cout << "\n[*] You hurl a Bomb! Massive explosion!\n";
                            usleep(1000000);
                            mob.takeDamage(30);
                            player.inventory.erase(player.inventory.begin() + i);
                            itemUsed = true;
                            break;
                        } else {
                            cout << "\nYou can't use that in combat.\n";
                            usleep(1000000);
                            itemUsed = true;
                            break;
                        }
                    }
                }
                
                // if they used an item, skip the attack part of the loop
                if (itemUsed == true) {
                    continue;
                }
            }
        } 
        else { 
            // if they pick 1 or type nonsense, default to attacking
            int combatD20 = (rand() % 20) + 1;
            bool isCrit = false;
            
            if (combatD20 <= player.critChance) {
                isCrit = true;
            }
            
            cout << "\n[CRIT CHECK] Rolled: " << combatD20 << " (Crits on " << player.critChance << " or lower)\n";
            usleep(1000000);

            int dealDmg = player.attack + (rand() % 6);
            if (isCrit == true) {
                dealDmg = dealDmg * 2;
                cout << "*** CRITICAL STRIKE! ***\n";
                usleep(1000000);
            }

            cout << ">>> " << player.attackMessage << " (" << dealDmg << " damage!)\n";
            usleep(1000000);
            mob.takeDamage(dealDmg);

            if (aldricHelps == true && mob.isAlive()) {
                usleep(1000000);
                cout << ">>> Aldric drives his blade into the enemy for 8 damage!\n";
                mob.takeDamage(8);
            }
        }

        // enemy strikes back if still alive
        if (mob.isAlive()) {
            usleep(1000000);
            mob.takeTurn();
            int incomingDmg = (mob.getAttack() / 2) + (rand() % 6);
            cout << "<<< The " << mob.getName() << " strikes! You take " << incomingDmg << " damage.\n";
            usleep(1000000);
            player.hp -= incomingDmg;
        }
    }
    
    if (player.hp > 0) {
        usleep(1000000);
        cout << "\n>> You defeated the " << mob.getName() << "!\n";
        player.addExp(mob.getExpReward());
        return true;
    }
    return false;
}

// Subclasses for enemy types according to specific areas
PlainsEnemy::PlainsEnemy() : Enemy("Demonic Cat", 35, 12, 15, "None", "A Demonic Cat leaps out from the ash!") {}
void PlainsEnemy::battleIntro() { Enemy::battleIntro(); }
void PlainsEnemy::specialAbility() { 
    if (getHp() < 10) { 
        cout << "The Cat hisses violently!\n"; 
        usleep(1000000); 
    } 
}
void PlainsEnemy::takeTurn() { Enemy::takeTurn(); }

CastleEnemy::CastleEnemy() : Enemy("Knight", 65, 18, 40, "None", "A Knight steps forward, blocking the corridor!") { raging = false; }
CastleEnemy::CastleEnemy(string n, int h, int atk, int exp, string loot, string intro) : Enemy(n, h, atk, exp, loot, intro) { raging = false; }
void CastleEnemy::battleIntro() { Enemy::battleIntro(); }
void CastleEnemy::specialAbility() {
    if (raging == false && getHp() <= (getMaxHp() / 2)) {
        raging = true; 
        setAttack(getAttack() + 4);
        cout << "\n[BLOOD RAGE] Soot vents from the armor's seams! Its power increases!\n";
        usleep(1000000);
    }
}
void CastleEnemy::takeTurn() { Enemy::takeTurn(); }
bool CastleEnemy::isRaging() { return raging; }

OgreEnemy::OgreEnemy() : Enemy("Cave Ogre", 110, 25, 80, "None", "A massive Cave Ogre steps out of the shadows!") {}
void OgreEnemy::battleIntro() { Enemy::battleIntro(); }
void OgreEnemy::specialAbility() {
    if (getTurnCount() % 3 == 2) { 
        cout << "The Ogre raises both fists... GROUND SLAM INCOMING!\n"; 
        usleep(1000000); 
    }
}
void OgreEnemy::takeTurn() { Enemy::takeTurn(); }

BossEnemy::BossEnemy() : Enemy("Massive Dragon", 300, 32, 500, "Magic Crystal", "The Massive Dragon rises. This is the final battle.") { phaseTwo = false; }
void BossEnemy::takeDamage(int dmg) {
    Enemy::takeDamage(dmg);
    if (phaseTwo == false && getHp() <= getMaxHp() / 2) {
        phaseTwo = true; 
        setAttack(getAttack() + 15);
        usleep(1000000);
        cout << "\n*** The Dragon ROARS! Its attacks grow MUCH more powerful! ***\n";
        usleep(1000000);
    }
}
void BossEnemy::battleIntro() { Enemy::battleIntro(); }
void BossEnemy::specialAbility() { 
    if (getTurnCount() % 2 == 1) { 
        cout << "FIRE BREATH incoming next turn!\n"; 
        usleep(1000000); 
    } 
}
void BossEnemy::takeTurn() { Enemy::takeTurn(); }
void BossEnemy::aldricAssist() { }
bool BossEnemy::isInPhaseTwo() { return phaseTwo; }

//aldric is an enemy class.

NPC::NPC() : Enemy("Aldric", 80, 18, 80, "Aldric's Blade", "\"Come on then. Show me what you've got.\"") { allied = false; }
bool NPC::isAllied() { return allied; }
void NPC::setAllied(bool a) { allied = a; }

void NPC::introduce() {
    cout << "The figure steps into the torchlight." << endl; usleep(1000000);
    cout << "He is tall, scarred, wearing battered adventurer's armor." << endl; usleep(1000000);
    cout << "\"The name's Aldric. Treasure hunter. Currently... very lost.\"" << endl; usleep(1000000);
    cout << "\"Been stuck in this castle for two weeks. Not my best work.\"" << endl; usleep(1000000);
    cout << "\"So. What brings a warrior to a place like this?\"" << endl; usleep(1000000);
}
void NPC::battleIntro() { Enemy::battleIntro(); }
void NPC::specialAbility() { 
    if (getTurnCount() % 2 == 1) { 
        cout << "Aldric winds up a Precise Strike!\n"; 
        usleep(1000000); 
    } 
}
void NPC::takeTurn() { Enemy::takeTurn(); }