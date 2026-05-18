#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Player {
public:
    string name;
    string classType;
    string attackMessage;
    vector<string> inventory; 

    // Stats scaled 1-100
    int hp;
    int maxHp;
    int attack;
    int critChance; 
    int intelligence; 
    int stealth;      
    int charisma;     

    // Progression mechanics
    int level;
    int exp;
    int expNeeded;

    // Game States
    bool clearedPlains;
    bool clearedCastle;
    bool hasShadowKey;
    bool hasRampartKey;
    bool npcAllied;
    bool npcDefeated;
    
    // Aldric specific trackers
    bool failedAldricPersuasion;
    int aldricDeaths; //if the player kinda sucks, there's a mercy mechanic

    Player(string pName, int classChoice);
    
    void showInventory();
    void addExp(int amount);
    void levelUp();
    void displayStats();
    void heal(int amount);
    void respawn(int checkpointHp);
};

#endif