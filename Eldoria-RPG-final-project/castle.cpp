#include <iostream>
#include <string>
#include <unistd.h>
#include "castle.h"
#include "enemy.h"
#include "plains.h" 
#include "dice.h"

using namespace std;

static bool npcResolved   = false;
static bool door1Cleared  = false;
static bool door1AVisited = false;
static bool door1BMet     = false;
static bool door2Cleared  = false;
static bool door2ACleared = false;
static bool door2BCleared = false;
static bool codeFound     = false;

void doorA_Door1A(Player& player) {
    bool inRoom = true;
    cout << "\n--- Door 1A: The Inscription Room ---" << endl;
    usleep(1000000);

    while (inRoom) {
        if (door1AVisited) {
            cout << "The inscription: 3 - 2 - 3 - 5" << endl;
            usleep(1000000);
        } else {
            cout << "Something is carved into the far wall..." << endl;
            usleep(1000000);
            cout << "\n    +-----------------------+" << endl;
            cout << "    |    3  -  2  -  3  -  5   |" << endl;
            cout << "    +-----------------------+" << endl;
            usleep(1000000);
            cout << "\nA number pattern. You commit it to memory." << endl;
            codeFound = true;
            door1AVisited = true;
            usleep(1000000);
        }

        cout << "\n1. Go back to Door 1  2. Stay" << endl;
        cout << "Choice: ";
        string nav; 
        cin >> nav;
        if (nav == "1") {
            inRoom = false;
        }
    }
}

void doorA_Door1B(Player& player) {
    bool inRoom = true;
    cout << "\n--- Door 1B: The Torchlit Chamber ---" << endl;
    usleep(1000000);
    cout << "A figure sits against the far wall." << endl;
    usleep(1000000);

    while (inRoom) {
        if (player.npcAllied) {
            cout << "\nAldric nods at you." << endl;
            usleep(1000000);
            cout << "\"I'll be ready when you face the dragon. Count on it.\"" << endl;
            cout << "\n1. Leave" << endl;
            string nav; cin >> nav;
            inRoom = false;
            continue;
        }

        if (player.npcDefeated) {
            cout << "\nThe room is empty. Aldric is gone." << endl;
            usleep(1000000);
            cout << "\n1. Leave" << endl;
            string nav; cin >> nav;
            inRoom = false;
            continue;
        }

        if (door1BMet == false) {
            NPC tempAldric;
            tempAldric.introduce();
            door1BMet = true;

            cout << "\n1. Approach and talk to him" << endl;
            cout << "2. Ignore him and leave" << endl;
            cout << "Choice: ";
            string approachChoice; 
            cin >> approachChoice;

            if (approachChoice == "2") { 
                inRoom = false; 
                continue; 
            }

            cout << "\nAldric: \"The dragon. Either incredibly brave or incredibly stupid.\"" << endl;
            usleep(1000000);
            cout << "\"Prove yourself and I'll back you up.\"" << endl;
            usleep(1000000);
        }

        if (npcResolved == false) {
            bool autoDuel = false;
            
            if (player.failedAldricPersuasion && player.aldricDeaths < 2) {
                cout << "\nAldric draws his blade. \"Words won't work anymore. Defend yourself!\"\n";
                usleep(1000000);
                autoDuel = true;
            } else {
                if (player.aldricDeaths >= 2) {
                    cout << "\nAldric rests his sword on his shoulder. \"You've got grit, I'll admit.\"\n";
                    usleep(1000000);
                    cout << "\"Are you ready to talk reason, or do we go another round?\"\n";
                } else {
                    cout << "\nAldric stands with his arms crossed.\n";
                }
                usleep(1000000);
                
                cout << "1. Duel Him\n2. Persuade with Logic (Int Check DC 14)\n3. Persuade with Emotion (Cha Check DC 14)\n4. Leave for now\nChoice: ";
                string mainChoice; 
                cin >> mainChoice;

                if (mainChoice == "4") { 
                    inRoom = false; 
                    continue; 
                }

                if (mainChoice == "2" || mainChoice == "3") {
                    int statUsed = 0;
                    if (mainChoice == "2") {
                        statUsed = player.intelligence;
                    } else {
                        statUsed = player.charisma;
                    }
                    
                    cout << "\nYou attempt to reason with him...\n";
                    usleep(1000000);
                    
                    if (diceRoll(statUsed, 14) == 1) {
                        cout << "\n\"...Alright. You've talked me into it.\"\n";
                        usleep(1000000);
                        player.npcAllied = true;
                        npcResolved = true;
                        continue;
                    } else {
                        cout << "\n\"Words are cheap. Show me you can fight.\"\n";
                        usleep(1000000);
                        player.failedAldricPersuasion = true;
                        player.aldricDeaths = 0; 
                        autoDuel = true;
                    }
                } else if (mainChoice == "1") {
                    cout << "\n\"Finally. Let's see what you've got.\"\n";
                    usleep(1000000);
                    autoDuel = true;
                }
            }

            if (autoDuel) {
                NPC aldric;
                bool survived = runCombat(player, aldric, false);
                
                if (survived) {
                    cout << "\nAldric drops to one knee. \"...You're the real deal.\"\n";
                    usleep(1000000);
                    cout << "1. Spare him  2. Finish him off\nChoice: ";
                    string outcomeChoice; 
                    cin >> outcomeChoice;

                    if (outcomeChoice == "1") {
                        cout << "\n\"Mercy and strength. Alright. I'm with you.\"\n";
                        player.npcAllied = true;
                    } else {
                        cout << "\nAldric falls. You found: Aldric's Blade! (Attack +8)\n";
                        player.attack += 8;
                        player.npcDefeated = true;
                    }
                    npcResolved = true;
                } else {
                    cout << "\n\"Not good enough. Come back when you're stronger.\"\n";
                    usleep(1000000);
                    player.aldricDeaths++;
                    player.respawn(player.maxHp);
                    inRoom = false;
                    continue;
                }
            }
        }

        cout << "\n1. Leave the room  2. Stay" << endl;
        cout << "Choice: ";
        string navChoice; cin >> navChoice;
        if (navChoice == "1") inRoom = false;
    }
}

void doorA_Door1(Player& player) {
    bool inRoom = true;
    cout << "\n--- Door 1: The Guard Room ---" << endl;
    usleep(1000000);

    while (inRoom) {
        if (door1Cleared == false) {
            cout << "3 Knights stand in formation, blocking the way." << endl;
            usleep(1000000);

            CastleEnemy knight1; 
            cout << "\nKnight 1 of 3!" << endl;
            usleep(1000000);
            runCombat(player, knight1, true);
            if (player.hp <= 0) { inRoom = false; player.respawn(player.maxHp); continue; }
            if (knight1.isAlive() == true) { cout << "\nYou fled the room!\n"; usleep(1000000); inRoom = false; continue; } // The fix!

            CastleEnemy knight2; 
            cout << "\nKnight 2 of 3!" << endl;
            usleep(1000000);
            runCombat(player, knight2, true);
            if (player.hp <= 0) { inRoom = false; player.respawn(player.maxHp); continue; }
            if (knight2.isAlive() == true) { cout << "\nYou fled the room!\n"; usleep(1000000); inRoom = false; continue; } // The fix!

            CastleEnemy knight3; 
            cout << "\nKnight 3 of 3!" << endl;
            usleep(1000000);
            runCombat(player, knight3, true);
            if (player.hp <= 0) { inRoom = false; player.respawn(player.maxHp); continue; }
            if (knight3.isAlive() == true) { cout << "\nYou fled the room!\n"; usleep(1000000); inRoom = false; continue; } // The fix!

            cout << "\nAll 3 knights down!" << endl;
            usleep(1000000);
            cout << "You open the battle chest..." << endl;
            usleep(1000000);
            player.inventory.push_back("Healing Potion");
            player.inventory.push_back("Healing Potion");
            player.inventory.push_back("Bomb");
            cout << "You found: 2 Healing Potions, Bomb, and a Whetstone (+5 Attack)!" << endl;
            player.attack += 5;
            door1Cleared = true;
            usleep(1000000);
        }

        if (door1Cleared == true) {
            cout << "\nSilence behind Door 1A." << endl;
            cout << "Behind Door 1B, the sound of someone moving." << endl;
            cout << "\n1. Door 1A" << (door1AVisited ? " [Visited]" : "") << endl;
            cout << "2. Door 1B" << (door1BMet ? " [Visited]" : "") << endl;
            cout << "3. Back to Entrance" << endl;
            cout << "0. Check Inventory" << endl;
            cout << "Choice: ";
            string choice; cin >> choice;

            if (choice == "0") player.showInventory();
            else if (choice == "1") doorA_Door1A(player);
            else if (choice == "2") doorA_Door1B(player);
            else if (choice == "3") inRoom = false;
            else cout << "Invalid choice." << endl;
        }
    }
}

void doorA_Door2A(Player& player) {
    bool inRoom = true;
    cout << "\n--- Door 2A: The Broken Hall ---" << endl;
    usleep(1000000);

    while (inRoom) {
        if (door2ACleared) {
            cout << "The Ogre's body lies where it fell." << endl;
            usleep(1000000);
        } else {
            cout << "The thudding you heard... it was footsteps. Very large ones." << endl;
            usleep(1000000);
            
            OgreEnemy ogre;
            runCombat(player, ogre, false); 
            
            if (ogre.isAlive() == false) {
                door2ACleared = true;
                cout << "The Ogre dropped a Weapon Upgrade! (Attack +5)\n";
                player.attack += 5;
                usleep(1000000);
            } else {
                player.respawn(player.maxHp);
                inRoom = false;
                continue;
            }
        }

        cout << "\n1. Go back to Door 2  2. Stay" << endl;
        cout << "Choice: ";
        string nav; cin >> nav;
        if (nav == "1") inRoom = false;
    }
}

void doorA_Door2B(Player& player) {
    bool inRoom = true;
    cout << "\n--- Door 2B: The Vault ---" << endl;
    usleep(1000000);

    while (inRoom) {
        if (door2BCleared) {
            cout << "The open chest sits empty. Shadow Key is in your inventory." << endl;
            usleep(1000000);
        } else {
            cout << "A single chest with a 4-digit combination lock." << endl;
            usleep(1000000);

            if (codeFound == false) {
                cout << "You don't know the combination yet." << endl;
                cout << "There must be a clue somewhere in the castle..." << endl;
                usleep(1000000);
            } else {
                cout << "You remember the inscription: 3 - 2 - 3 - 5" << endl;
                cout << "\nEnter the 4-digit code: ";
                string code; 
                cin >> code;

                if (code == "3235") {
                    cout << "\nClick. The lock opens." << endl;
                    usleep(1000000);
                    cout << "You found: Shadow Key!" << endl;
                    player.hasShadowKey = true;
                    door2BCleared = true;
                    usleep(1000000);
                } else {
                    cout << "\nWrong code. The chest stays locked." << endl;
                    usleep(1000000);
                }
            }
        }

        cout << "\n1. Go back to Door 2  2. Stay" << endl;
        cout << "Choice: ";
        string nav; cin >> nav;
        if (nav == "1") inRoom = false;
    }
}

void doorA_Door2(Player& player) {
    bool inRoom = true;
    cout << "\n--- Door 2: The Antechamber ---" << endl;
    usleep(1000000);

    while (inRoom) {
        if (door2Cleared == false) {
            cout << "2 Demonic Cats drop from the ceiling." << endl;
            usleep(1000000);
            cout << "A Knight steps out from behind a pillar." << endl;
            usleep(1000000);

            PlainsEnemy cat1; 
            cout << "\nCat 1 of 2!" << endl;
            usleep(1000000);
            runCombat(player, cat1, true);
            if (player.hp <= 0) { inRoom = false; player.respawn(player.maxHp); continue; }
            if (cat1.isAlive() == true) { cout << "\nYou fled the room!\n"; usleep(1000000); inRoom = false; continue; } // The fix!

            PlainsEnemy cat2; 
            cout << "\nCat 2 of 2!" << endl;
            usleep(1000000);
            runCombat(player, cat2, true);
            if (player.hp <= 0) { inRoom = false; player.respawn(player.maxHp); continue; }
            if (cat2.isAlive() == true) { cout << "\nYou fled the room!\n"; usleep(1000000); inRoom = false; continue; } // The fix!

            CastleEnemy knight; 
            cout << "\nThe Knight charges!" << endl;
            usleep(1000000);
            runCombat(player, knight, true);
            if (player.hp <= 0) { inRoom = false; player.respawn(player.maxHp); continue; }
            if (knight.isAlive() == true) { cout << "\nYou fled the room!\n"; usleep(1000000); inRoom = false; continue; } // The fix!

            cout << "\nAll enemies cleared!" << endl;
            usleep(1000000);
            cout << "You find a Healing Potion among the wreckage." << endl;
            player.inventory.push_back("Healing Potion");
            door2Cleared = true;
            usleep(1000000);
        }

        if (door2Cleared == true) {
            cout << "\nBehind Door 2A: a deep rhythmic thudding." << endl;
            cout << "Behind Door 2B: complete silence." << endl;
            cout << "\n1. Door 2A" << (door2ACleared ? " [Cleared]" : "") << endl;
            cout << "2. Door 2B" << (door2BCleared ? " [Cleared]" : "") << endl;
            cout << "3. Back to Entrance" << endl;
            cout << "0. Check Inventory" << endl;
            cout << "Choice: ";
            string choice; cin >> choice;

            if (choice == "0") player.showInventory();
            else if (choice == "1") doorA_Door2A(player);
            else if (choice == "2") doorA_Door2B(player);
            else if (choice == "3") inRoom = false;
            else cout << "Invalid choice." << endl;
        }
    }
}

void doorARoute(Player& player) {
    bool inDoorA = true;

    cout << "\n--- DOOR A: THE VAULT PATH ---" << endl;
    usleep(1000000);
    cout << "Two doors stand before you." << endl;
    usleep(1000000);
    cout << "Behind Door 1: the clinking of armour. Lots of footsteps." << endl;
    usleep(1000000);
    cout << "Behind Door 2: hissing. Something heavy pacing." << endl;
    usleep(1000000);

    while (inDoorA) {
        if (player.hasShadowKey) {
            cout << "\n(You have the Shadow Key. You can return to the castle hub.)" << endl;
        }

        cout << "\n1. Door 1" << (door1Cleared ? " [Cleared]" : "") << endl;
        cout << "2. Door 2" << (door2Cleared ? " [Cleared]" : "") << endl;
        cout << "3. Return to Castle Hub" << endl;
        cout << "0. Check Inventory" << endl;
        cout << "Choice: ";
        string choice; cin >> choice;

        if (choice == "0") player.showInventory();
        else if (choice == "1") doorA_Door1(player);
        else if (choice == "2") doorA_Door2(player);
        else if (choice == "3") inDoorA = false;
        else cout << "Invalid choice." << endl;
    }
}

void doorBRoute(Player& player) {
    cout << "\n--- DOOR B: THE HIGH SILENT RAMPARTS ---" << endl;
    usleep(1000000);
    cout << " You pull yourself up the rope netting onto the open battlements. Ash drifts across the stone.\n";
    usleep(1000000);

    // ROOM 1: THE HUSK
    cout << "\n[ROOM 1: THE LOWER PARAPET WALKWAY]\n";
    cout << " A figure clad in empty, soot-venting plate mail blocks your path.\n";
    usleep(1000000);
    cout << "\nChoose approach:\n1. Use Stealth to sneak past (Stealth DC 13)\n2. Attack directly\nChoice: ";
    string flowInput; 
    cin >> flowInput;

    bool skipFight1 = false;
    if (flowInput == "1") {
        if (diceRoll(player.stealth, 13) == 1) {
            cout << "\n>> SUCCESS! You pass without triggering a fight.\n";
            usleep(1000000);
            skipFight1 = true;
        } else {
            cout << "\n>> FAILURE! Your pack clangs against an iron ring. The suit pivots to strike!\n";
            usleep(1000000);
        }
    }

    if (skipFight1 == false) {
        CastleEnemy husk("Possessed Husk Guard", 60, 16, 45, "None", "The hollow frame levels a corroded partisan at your throat.");
        if (runCombat(player, husk, false) == false) { 
            player.respawn(player.maxHp); 
            return; 
        }
        openChest(player);
    }

    // ROOM 2: THE ARCHER
    cout << "\n--- ROOM 2: THE NORTH ELEVATED WATCHTOWER ---\n";
    usleep(1000000);
    cout << " A hollowed carcass loads a heavy siege crossbow, aiming straight down your narrow lane.\n";
    usleep(1000000);
    cout << "\nChoose approach:\n1. Sprint past the firing line (Stealth DC 14)\n2. Attack directly\nChoice: ";
    cin >> flowInput;

    bool skipFight2 = false;
    if (flowInput == "1") {
        if (diceRoll(player.stealth, 14) == 1) {
            cout << "\n>> SUCCESS! You safely dive past the bolt target lines.\n";
            usleep(1000000);
            skipFight2 = true;
        } else {
            cout << "\n>> FAILURE! An iron bolt grazes your ribs for 15 damage!\n";
            player.hp -= 15;
            usleep(1000000);
        }
    }

    if (player.hp <= 0) {
        cout << "\n[DEATH] THE ARROW PINNED YOU TO THE MASONRY.\n";
        player.respawn(player.maxHp); 
        return;
    }

    if (skipFight2 == false) {
        CastleEnemy archer("Hollow Archer", 55, 17, 45, "None", "The dead marksman winches back another heavy spike bolt.");
        if (runCombat(player, archer, false) == false) { 
            player.respawn(player.maxHp); 
            return; 
        }
        openChest(player);
    }

    // ROOM 3: CAELEN THE ARCHIVIST
    cout << "\n--- ROOM 3: THE HIGH ARCHIVE BALCONY ---\n";
    usleep(1000000);
    cout << " You reach a balcony where a scholar is chained to an altar block next to a clicking box.\n";
    usleep(1000000);
    cout << " 'I am Caelen,' he gasps. 'They are draining our memories to break the Black Seal!'\n";
    usleep(1000000);

    cout << "\nAttempt to disarm the lockbox:\n1. Calm him down to guide you (Charisma DC 12)\n2. Solve it yourself (Intelligence DC 13)\nChoice: ";
    cin >> flowInput;

    if (flowInput == "1") {
        if (diceRoll(player.charisma, 12) == 1) {
            cout << "\n>> SUCCESS! You disarm it together and find a Whetstone! (Attack +5)\n";
            player.attack += 5;
            usleep(1000000);
        } else {
            cout << "\n>> FAILURE! He panics, tripping a wire. You take 15 shock damage!\n";
            player.hp -= 15;
            usleep(1000000);
        }
    } else {
        if (diceRoll(player.intelligence, 13) == 1) {
            cout << "\n>> SUCCESS! The runes shift open, yielding a Healing Potion!\n";
            player.inventory.push_back("Healing Potion");
            usleep(1000000);
        } else {
            cout << "\n>> FAILURE! An explosion of defensive backlash hits you for 20 damage!\n";
            player.hp -= 20;
            usleep(1000000);
        }
    }

    if (player.hp <= 0) {
        cout << "\n[DEATH] THE TRAP SURGE WAS LETHAL.\n";
        player.respawn(player.maxHp); 
        return;
    }

    cout << "\nCaelen points to the watchtower before turning entirely to soot. 'Take the key from Garrick...'\n";
    usleep(1000000);

    // ROOM 4: THE FORGE REMNANT
    cout << "\n--- ROOM 4: THE WEAPON FORGE PASS ZONE ---\n";
    usleep(1000000);
    cout << " An animated forge remnant stokes a blazing basin, blocking the exit cage gate.\n";
    usleep(1000000);
    cout << "\nChoose approach:\n1. Climb the rafters silently (Stealth DC 13)\n2. Drop down and fight\nChoice: ";
    cin >> flowInput;

    bool skipFight4 = false;
    if (flowInput == "1") {
        if (diceRoll(player.stealth, 13) == 1) {
            cout << "\n>> SUCCESS! You safely drop down past the iron cage grate on the other side.\n";
            usleep(1000000);
            skipFight4 = true;
        } else {
            cout << "\n>> FAILURE! A rafter snaps, dropping you onto the iron anvil for 15 damage!\n";
            player.hp -= 15;
            usleep(1000000);
        }
    }

    if (player.hp <= 0) {
        cout << "\n[DEATH] THE FALL DAMAGE WAS FATAL.\n";
        player.respawn(player.maxHp); 
        return;
    }

    if (skipFight4 == false) {
        CastleEnemy forge("Forge Remnant", 70, 18, 50, "None", "The giant phantom hammers a plate, emitting a cold metallic hiss.");
        if (runCombat(player, forge, false) == false) { 
            player.respawn(player.maxHp); 
            return; 
        }
        openChest(player);
    }

    // ROOM 5: CAPTAIN GARRICK
    cout << "\n--- ROOM 5: THE APEX WATCHTOWER COMMANDS — MINIBOSS CLIMAX ---\n";
    usleep(1000000);
    cout << " Captain Garrick steps forward, his broadsword wrapped in an unholy purple flame.\n";
    usleep(1000000);
    cout << " 'The Seal chose your path,' he notes hollowly. 'Your mind belongs to Blackthorne!'\n";
    usleep(1000000);

    CastleEnemy garrick("Garrick the Oathbreaker", 120, 22, 150, "None", "Garrick steps forward, ready to strike.");
    if (runCombat(player, garrick, false) == false) { 
        player.respawn(player.maxHp); 
        return; 
    }

    cout << "\n'Please...' Garrick weeps as his plate harness collapses into embers.\n";
    usleep(1000000);
    cout << "\nGarrick falls. You found the Rampart Crest Key!\n";
    usleep(1000000);
    player.hasRampartKey = true; 
}

void castleMap(Player& player) {
    cout << "\n=== CASTLE DARKMORE ===\n";
    usleep(1000000);
    cout << "The castle is cold and silent." << endl;
    usleep(1000000);
    cout << "Two massive doors stand at the far end of the entrance hall." << endl;
    usleep(1000000);
    cout << "Beyond both lies the dungeon -- and the dragon." << endl;
    usleep(1000000);
    cout << "The Black Seal requires two keys to open the descent.\n";
    usleep(1000000);
    
    while (player.clearedCastle == false) {
        cout << "\nWhich door do you approach?\n";
        cout << "1. Door A (Vault)\n2. Door B (Ramparts)\n3. Descend to the Dungeon\n0. Check Inventory\nChoice: ";
        string choice; 
        cin >> choice;
        
        if (choice == "0") {
            player.showInventory();
        }
        else if (choice == "1") {
            doorARoute(player);
        }
        else if (choice == "2") {
            doorBRoute(player);
        }
        else if (choice == "3") {
            if (player.hasShadowKey && player.hasRampartKey) {
                cout << "\nBoth keys turn. The path to the Dungeon opens.\n";
                usleep(1000000);
                player.clearedCastle = true;
            } else {
                cout << "\nLocked. You need the Shadow Key AND the Rampart Crest Key.\n";
                usleep(1000000);
            }
        } else {
            cout << "Invalid choice.\n";
        }
    }
}