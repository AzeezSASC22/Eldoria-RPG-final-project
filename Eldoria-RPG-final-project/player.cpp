#include <iostream>
#include <unistd.h>
#include "player.h"

using namespace std;

Player::Player(string pName, int classChoice) {
    name = pName;
    level = 1;
    exp = 0;
    expNeeded = 100;
    
    clearedPlains = false;
    clearedCastle = false;
    hasShadowKey = false;
    hasRampartKey = false;
    npcAllied = false;
    npcDefeated = false;
    
    failedAldricPersuasion = false;
    aldricDeaths = 0;

    // set up the stats based on the class choice
    if (classChoice == 1) {
        classType = "Warrior";
        attackMessage = "You heave your heavy blade in a crushing arc!";
        maxHp = 100; attack = 18; critChance = 3; 
        intelligence = 20; stealth = 20; charisma = 20;
    } else if (classChoice == 2) {
        classType = "Mage";
        attackMessage = "You channel raw mana into a searing blast!";
        maxHp = 60; attack = 12; critChance = 2; 
        intelligence = 80; stealth = 40; charisma = 50;
    } else {
        classType = "Jester";
        attackMessage = "You dart in and slash with your serrated dagger!";
        maxHp = 50; attack = 8; critChance = 5; 
        intelligence = 50; stealth = 80; charisma = 80;
    }
    
    hp = maxHp;
    inventory.push_back("Healing Potion");
}

void Player::showInventory() {
    cout << "\n--- Inventory ---" << endl;
    if (inventory.size() == 0) {
        cout << "Your pack is empty." << endl;
    } else {
        for (int i = 0; i < inventory.size(); i++) {
            cout << i + 1 << ". " << inventory[i] << endl;
        }
    }
    cout << "-----------------" << endl;
    usleep(1000000);
}

void Player::addExp(int amount) {
    cout << "\n[XP] You gained " << amount << " experience points!\n";
    usleep(1000000);
    exp += amount;
    if (exp >= expNeeded) {
        levelUp();
    }
}

void Player::levelUp() {
    exp = exp - expNeeded;
    level++;
    expNeeded = expNeeded + 50; 
    
    maxHp = maxHp + 15;
    hp = maxHp;
    attack = attack + 3;
    intelligence = intelligence + 5;
    stealth = stealth + 5;
    charisma = charisma + 5;

    cout << "\n*** LEVEL UP! You are now Level " << level << " ***\n";
    usleep(1000000);
    cout << "Your max HP and damage have increased. Your wounds are healed!\n";
    usleep(1000000);
}

void Player::displayStats() {
    cout << "\n--- PROFILE ---" << endl;
    cout << "NAME: " << name << " | CLASS: " << classType << " | LEVEL: " << level << endl;
    cout << "HP: " << hp << "/" << maxHp << " | ATK: " << attack << endl;
    cout << "[INT]: " << intelligence << " | [STL]: " << stealth << " | [CHA]: " << charisma << endl;
    cout << "---------------" << endl;
    usleep(1000000);
}

void Player::heal(int amount) {
    hp += amount;
    if (hp > maxHp) {
        hp = maxHp;
    }
    cout << "+ You recovered HP! Current HP: " << hp << "/" << maxHp << endl;
    usleep(1000000);
}

void Player::respawn(int checkpointHp) {
    hp = checkpointHp;
    usleep(1000000);
    cout << "\n>>> Waking back at the checkpoint with a sharp gasp...\n";
    usleep(1000000);
}