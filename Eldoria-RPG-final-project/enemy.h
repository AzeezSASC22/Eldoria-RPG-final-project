#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <string>
#include "player.h" // Included so the combat engine knows what the Player is

using namespace std;

class Enemy {
    private:
        string name;
        int hp;
        int maxHp;
        int attack;
        int expReward;
        string lootDrop;
        int turnCount;
        string introText; //for the custom enemy descriptions in route b
    
    public:
        Enemy(string n, int h, int atk, int exp, string loot, string intro = "");

        // Getters
        string getName();
        int    getHp();
        int    getMaxHp();
        int    getAttack();
        int    getExpReward();
        string getLootDrop();
        bool   isAlive();
        int    getTurnCount();

        // Setters
        void setHp(int h);
        void setAttack(int a);
        void incrementTurn();

        void takeDamage(int dmg);
        int  rollAttack();
        void displayStatus();
        
        // 'virtual' tells the compiler to use the subclass version if it exists. so that I don't have to keep copy pasting same lines of code
        //more in citations
        virtual void battleIntro();
        virtual void specialAbility();
        virtual void takeTurn();
        virtual void aldricAssist(); // Put here so the combat loop can trigger it
};


// ===========================================================================
//   GLOBAL COMBAT ENGINE
// ============================================================================
bool runCombat(Player& player, Enemy& mob, bool allowEscape, bool aldricHelps = false);


/*-----------------------------------------------
 SUBCLASS 1 — Demonic Cat  (plains)
-----------------------------------------------*/
class PlainsEnemy : public Enemy {
    public:
        PlainsEnemy();
        void battleIntro();
        void specialAbility();
        void takeTurn();
};


/*--------------------------------------------------------
  SUBCLASS 2 — Knight & Castle Guards  (castle)
----------------------------------------------------------*/
class CastleEnemy : public Enemy {
    private:
        bool raging;
    
    public:
        // Dual constructors to bridge both of your coding styles!
        CastleEnemy(); // 1. Uses your default standard Knight for Door A
        CastleEnemy(string n, int h, int atk, int exp, string loot, string intro); // 2. Uses your partner's custom named enemies for Door B
        
        void battleIntro();
        void specialAbility();
        void takeTurn();
        bool isRaging();
};


/*--------------------------------------------------------
  SUBCLASS 3 — Cave Ogre  (castle miniboss)
  Stronger than a knight but weaker than the dragon.
  Ground slam deals bonus damage every 3rd turn.
----------------------------------------------------------*/
class OgreEnemy : public Enemy {
    public:
        OgreEnemy();
        void battleIntro();
        void specialAbility();
        void takeTurn();
};


/* --------------------------------------------------------
  SUBCLASS 4 — Massive Dragon  (dungeon final boss)
----------------------------------------------------------*/
class BossEnemy : public Enemy {
    private:
        bool phaseTwo;
        int rageDamage;
    
    public:
        BossEnemy();
        void takeDamage(int dmg);
        void battleIntro();
        void specialAbility();
        void takeTurn();
        void aldricAssist(); //boss will take damage after every turn if aldric is there
        bool isInPhaseTwo();
};


/*--------------------------------------------------------
  NPC — Aldric the Adventurer
  Subclass of Enemy so he shares all the battle mechanics.
  Extras: allied bool, isAllied(), setAllied(), introduce().
  If allied, he assists in the final dragon fight.
----------------------------------------------------------*/
class NPC : public Enemy {
    private:
        bool allied;

    public:
        NPC();
        bool isAllied();
        void setAllied(bool a);
        void introduce();
        void battleIntro();
        void specialAbility();
        void takeTurn();
};

#endif