#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "plains.h"
#include "enemy.h"

using namespace std;

// random loot generator for chests
void openChest(Player& player) {
    cout << "\nYou pry open the heavy chest...\n";
    usleep(1000000);
    int roll = rand() % 5;
    
    if (roll == 0) {
        cout << "You found a burst of ancient energy! (+40 EXP)\n";
        player.addExp(40);
    } else if (roll == 1) {
        cout << "You found a Healing Potion!\n";
        player.inventory.push_back("Healing Potion");
    } else if (roll == 2) {
        cout << "You found an Armor Plate! (Max HP +20, Heals 20)\n";
        player.maxHp += 20;
        player.heal(20);
    } else if (roll == 3) {
        cout << "You found a Whetstone! (Attack Power +5)\n";
        player.attack += 5;
    } else {
        cout << "You found a Bomb!\n";
        player.inventory.push_back("Bomb");
    }
    usleep(1000000);
}

void plainsMap(Player& player) {
    bool room1Cleared = false; 
    bool room2Cleared = false; 
    bool room3Cleared = false;
    bool room4Visited = false;
    
    usleep(1000000);
    cout << "\nThe kingdom of Eldoria is on the brink of ruin.\n";
    usleep(1000000);
    cout << "A Massive Dragon has seized Castle Darkmore and unleashed corrupted creatures across the land.\n";
    usleep(1000000);
    cout << "Your journey begins at the edge of the plains...\n";
    usleep(1000000);
    
    cout << "\nBefore you take your first step, something hisses.\n";
    usleep(1000000);
    cout << "A Demonic Cat lunges from the bushes!\n";
    usleep(1000000);
    
    PlainsEnemy tutCat;
    if (runCombat(player, tutCat, true) == false) { 
        player.respawn(player.maxHp); 
    }
    
    // Check if the player escaped
    if (tutCat.isAlive() == true) {
        cout << "\nYou narrowly escaped into the grass.\n";
        usleep(1000000);
    }
    
    cout << "\nYou catch your breath. Time to explore the plains.\n";
    usleep(1000000);

    while (player.clearedPlains == false) {
        cout << "\n=== THE PLAINS ===\n";
        cout << "Where do you go?\n";
        cout << "1. Sunlit Meadow\n2. Dark Grove\n3. Ruined Camp\n4. Old Well\n5. Iron Gate\n0. Menu/Stats\nChoice: ";
        string choice; 
        cin >> choice;

        if (choice == "0") { 
            player.displayStats(); 
            player.showInventory(); 
        }
        else if (choice == "1") {
            cout << "\n--- Sunlit Meadow ---\n";
            usleep(1000000);
            if (room1Cleared == true) { 
                cout << "The open chest sits where you left it. Nothing remains.\n"; 
                usleep(1000000); 
            }
            else { 
                cout << "Sunlight cuts through tall grass. Almost peaceful.\n";
                usleep(1000000);
                cout << "You spot a glint in the distance -- a chest!\n";
                usleep(1000000);
                openChest(player); 
                room1Cleared = true; 
            }
        }
        else if (choice == "2") {
            cout << "\n--- Dark Grove ---\n";
            usleep(1000000);
            if (room2Cleared == true) { 
                cout << "The grove is silent. All cats are gone.\n"; 
                usleep(1000000); 
            }
            else {
                cout << "The trees grow thick and dark. Something hisses...\n";
                usleep(1000000);
                cout << "3 Demonic Cats leap from the shadows!\n";
                usleep(1000000);
                
                PlainsEnemy c1; 
                cout << "\nCat 1 of 3!\n";
                usleep(1000000);
                runCombat(player, c1, true);
                if (player.hp <= 0) { player.respawn(player.maxHp); continue; }
                if (c1.isAlive() == true) { cout << "\nYou fled the grove!\n"; usleep(1000000); continue; }

                PlainsEnemy c2; 
                cout << "\nCat 2 of 3!\n";
                usleep(1000000);
                runCombat(player, c2, true);
                if (player.hp <= 0) { player.respawn(player.maxHp); continue; }
                if (c2.isAlive() == true) { cout << "\nYou fled the grove!\n"; usleep(1000000); continue; }

                PlainsEnemy c3; 
                cout << "\nCat 3 of 3!\n";
                usleep(1000000);
                runCombat(player, c3, true);
                if (player.hp <= 0) { player.respawn(player.maxHp); continue; }
                if (c3.isAlive() == true) { cout << "\nYou fled the grove!\n"; usleep(1000000); continue; }

                room2Cleared = true; 
                cout << "\nThe grove falls silent.\n"; 
                usleep(1000000);
            }
        }
        else if (choice == "3") {
            cout << "\n--- Ruined Camp ---\n";
            usleep(1000000);
            if (room3Cleared == true) { 
                cout << "The camp is quiet. The battle chest sits empty.\n"; 
                usleep(1000000); 
            }
            else {
                cout << "Burnt wood and torn cloth scatter the ground.\n";
                usleep(1000000);
                cout << "A heavy battle chest sits at the center.\n";
                usleep(1000000);
                cout << "2 Demonic Cats guard it -- and they are NOT moving.\n";
                usleep(1000000);
                
                PlainsEnemy c1; 
                cout << "\nCat 1 of 2!\n";
                usleep(1000000);
                runCombat(player, c1, true);
                if (player.hp <= 0) { player.respawn(player.maxHp); continue; }
                if (c1.isAlive() == true) { cout << "\nYou fled the camp!\n"; usleep(1000000); continue; } // The fix!
                
                PlainsEnemy c2;
                cout << "\nCat 2 of 2!\n";
                usleep(1000000);
                runCombat(player, c2, true);
                if (player.hp <= 0) { player.respawn(player.maxHp); continue; }
                if (c2.isAlive() == true) { cout << "\nYou fled the camp!\n"; usleep(1000000); continue; } // The fix!
                
                cout << "\nBoth cats down. The battle chest is yours.\n";
                usleep(1000000);
                cout << "You found the Castle Key!\n";
                usleep(1000000);
                player.inventory.push_back("Castle Key");
                room3Cleared = true;
            }
        }
        else if (choice == "4") {
            cout << "\n--- Old Well ---\n";
            usleep(1000000);
            if (room4Visited == false) {
                cout << "You wander off the path and find... an old well.\n";
                usleep(1000000);
                cout << "A crooked wooden sign leans against it:\n";
                usleep(1000000);
                cout << "\n  +--------------------------------------------+\n";
                cout << "  |  Wow. You really ARE exploring everything. |\n";
                cout << "  |  There is nothing here. Go fight something.|\n";
                cout << "  +--------------------------------------------+\n";
                usleep(1000000);
                room4Visited = true;
            } else {
                cout << "The sign stares back at you. Still nothing here.\n";
                usleep(1000000);
            }
        }
        else if (choice == "5") {
            cout << "\n--- Iron Gate ---\n";
            usleep(1000000);
            cout << "A massive iron gate towers before you.\n";
            usleep(1000000);
            cout << "Beyond it looms the dark silhouette of Castle Darkmore.\n";
            usleep(1000000);
            
            bool hasKey = false;
            for (int i = 0; i < player.inventory.size(); i++) {
                if (player.inventory[i] == "Castle Key") { 
                    hasKey = true; 
                    player.inventory.erase(player.inventory.begin() + i); 
                    break; 
                }
            }
            
            if (hasKey == true) {
                cout << "\nYou pull out the Castle Key and slide it into the lock.\n";
                usleep(1000000);
                cout << "The gate groans and slowly swings open...\n";
                usleep(1000000);
                cout << "\n>>> YOU ENTER THE CASTLE. <<<\n";
                usleep(1000000);
                player.clearedPlains = true;
            } else { 
                cout << "\nThe gate is firmly locked.\n";
                usleep(1000000);
                cout << "You need the Castle Key. It must be somewhere in the plains...\n"; 
                usleep(1000000); 
            }
        }
    }
}