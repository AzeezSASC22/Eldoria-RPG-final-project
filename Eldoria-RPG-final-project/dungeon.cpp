#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "dungeon.h"
#include "enemy.h"

using namespace std;


void dungeonMap(Player& player) {
    cout << "\n========================================" << endl;
    cout << "            THE DUNGEON                 " << endl;
    cout << "========================================" << endl;
    usleep(1000000);
    cout << "\nYou descend into the dungeon beneath Castle Darkmore." << endl;
    usleep(1000000);
    cout << "The air is heavy. The walls are scorched." << endl;
    usleep(1000000);
    cout << "A Statue of Grace glows faintly at the entrance." << endl;
    usleep(1000000);
    cout << "Beyond it, a dark corridor stretches into nothing." << endl;
    usleep(1000000);
    cout << "Deep in the shadows, something is chained to the wall." << endl;
    usleep(1000000);
    cout << "Large. Very large." << endl;
    usleep(1000000);
    
    while (true) {
        cout << "\n1. Interact with the Statue of Grace\n2. Approach the figure in the dark\nChoice: ";
        string choice; 
        cin >> choice;
        
        if (choice == "1") {
            cout << "\nYou approach the Statue of Grace." << endl;
            usleep(1000000);
            cout << "A warm light washes over you." << endl;
            usleep(1000000);
            cout << "Your wounds close. Your strength returns." << endl;
            usleep(1000000);
            player.heal(999);
            cout << "You have been healed to full HP!" << endl;
            usleep(1000000);
        } else if (choice == "2") {
            
            cout << "\nYou step into the dark corridor." << endl;
            usleep(1000000);
            cout << "The air is thick and hot." << endl;
            usleep(1000000);
            cout << "The chains begin to rattle. Slowly. Then faster." << endl;
            usleep(1000000);
            cout << "\n...\n......\n.........\n" << endl;
            usleep(1000000);
            cout << "A massive claw tears through the darkness and SMASHES the statue beside you." << endl;
            usleep(1000000);
            cout << "The chains SNAP." << endl;
            usleep(1000000);
            cout << "Two enormous wings unfold from the shadows." << endl;
            usleep(1000000);
            cout << "Two eyes -- burning like coals -- fix on you." << endl;
            usleep(1000000);
            
            cout << "\n                             __________\n";
            cout << "                     _,-.---'          `---.\n";
            cout << "                  ,-'                       `.\n";
            cout << "               ,-'   _                       `.\n";
            cout << "              /    ,'  `,                     \\\n";
            cout << "             /   ,'  ,--`--------._            \\\n";
            cout << "            /  ,'  ,'              `-.          \\\n";
            cout << "           /  /  ,'                  `-.         \\\n";
            cout << "          /  /  /     THE DRAGON        `-.       \\\n";
            cout << "         /  /  /                           `-.     \\\n";
            cout << "        `--'  `-------------------------------`-----'\n\n";
            usleep(1000000);
            
            cout << "\nThe Massive Dragon lets out a roar that shakes the dungeon walls." << endl;
            usleep(1000000);
            cout << "This is it." << endl;
            usleep(1000000);
            
            BossEnemy dragon;
            if (player.npcAllied == true) {
                cout << "\nA figure lands beside you. Aldric. Blade drawn. Eyes forward." << endl;
                usleep(1000000);
                cout << "\"I'm here. Let's finish this together.\"" << endl;
                usleep(1000000);
            }
            
            if (runCombat(player, dragon, false, player.npcAllied) == true) {
                cout << "\nThe Massive Dragon lies at your feet. It still breathes. Barely." << endl;
                usleep(1000000);
                cout << "\n1. Finish it\n2. Spare it\nChoice: ";
                string endChoice; 
                cin >> endChoice;
                
                // ENDING 1
                if (player.npcAllied == true && endChoice == "1") {
                    cout << "\n========================================" << endl;
                    cout << "             ENDING 1                   " << endl;
                    cout << "========================================" << endl;
                    usleep(1000000);
                    cout << "\nThe dragon falls. The dungeon goes silent." << endl;
                    usleep(1000000);
                    cout << "A Magic Crystal rolls across the floor." << endl;
                    usleep(1000000);
                    cout << "You pick it up. Power surges through you." << endl;
                    usleep(1000000);
                    cout << "\nThe kingdom is free. You are crowned ruler of Eldoria." << endl;
                    usleep(1000000);
                    
                    cout << "\n        .       .       .\n";
                    cout << "       /|\\     /|\\     /|\\\n";
                    cout << "      / | \\   / | \\   / | \\\n";
                    cout << "     /  |  \\_/  |  \\_/  |  \\\n";
                    cout << "    |_____________________________|\n";
                    cout << "    |       THE RULER OF          |\n";
                    cout << "    |          ELDORIA            |\n";
                    cout << "    |_____________________________|\n\n";
                    usleep(1000000);
                    
                    cout << "\nYou offer Aldric the position of your right hand man." << endl;
                    usleep(1000000);
                    cout << "He smiles and accepts." << endl;
                    usleep(1000000);
                    cout << "\nBut as you turn to leave, you catch Aldric staring" << endl;
                    usleep(1000000);
                    cout << "at the Magic Crystal in your hand." << endl;
                    usleep(1000000);
                    cout << "His eyes linger a moment too long." << endl;
                    usleep(1000000);
                    cout << "A hunger in them you haven't seen before." << endl;
                    usleep(1000000);
                    cout << "\nHe says nothing. But you notice." << endl;
                    usleep(1000000);
                    cout << "\n-- THE END --  (But is it really?)" << endl; 
                    usleep(1000000);
                } 
                // ENDING 2
                else if (player.npcAllied == true && endChoice == "2") {
                    cout << "\n========================================" << endl;
                    cout << "             ENDING 2                   " << endl;
                    cout << "========================================" << endl;
                    usleep(1000000);
                    cout << "\nThe dragon kneels, beaten but breathing." << endl;
                    usleep(1000000);
                    cout << "You lower your weapon. \"Go. Leave and never return.\"" << endl;
                    usleep(1000000);
                    cout << "\nYou turn to leave. Aldric is not beside you." << endl;
                    usleep(1000000);
                    cout << "You look back. He is still standing where you left him." << endl;
                    usleep(1000000);
                    cout << "\nThen he follows the dragon into the shadows." << endl;
                    usleep(1000000);
                    cout << "A scream echoes through the dungeon. Then silence." << endl;
                    usleep(1000000);
                    cout << "\nAldric emerges. Magic Crystal in hand." << endl;
                    usleep(1000000);
                    cout << "\"You are kind.\" he says." << endl;
                    usleep(1000000);
                    cout << "\"Kindness is a weakness I cannot afford.\"" << endl;
                    usleep(1000000);
                    cout << "\nHe walks past you. Toward the castle. Toward the throne." << endl;
                    usleep(1000000);
                    cout << "\n-- THE END --  (The wrong person won today.)" << endl; //worst ending but the true ending in my head because it leaves room for maybe another game? Aldric the villain?
                    usleep(1000000);
                } 
                // ENDING 3
                else if (player.npcAllied == false && endChoice == "1") {
                    cout << "\n========================================" << endl;
                    cout << "             ENDING 3                   " << endl;
                    cout << "========================================" << endl;
                    usleep(1000000);
                    cout << "\nThe dragon falls. Alone, you stand in the silence." << endl;
                    usleep(1000000);
                    cout << "The Magic Crystal rolls to your feet." << endl;
                    usleep(1000000);
                    cout << "You pick it up. Raw power floods through you." << endl;
                    usleep(1000000);
                    cout << "\nYou did it. Alone. No allies. No help. Just will." << endl;
                    usleep(1000000);
                    cout << "\nThe kingdom is freed. You are crowned its ruler." << endl;
                    usleep(1000000);
                    
                    cout << "\n        .       .       .\n";
                    cout << "       /|\\     /|\\     /|\\\n";
                    cout << "      / | \\   / | \\   / | \\\n";
                    cout << "     /  |  \\_/  |  \\_/  |  \\\n";
                    cout << "    |_____________________________|\n";
                    cout << "    |       THE RULER OF          |\n";
                    cout << "    |          ELDORIA            |\n";
                    cout << "    |_____________________________|\n\n";
                    usleep(1000000);
                    
                    cout << "\nThe legend of the lone warrior lives forever." << endl;
                    usleep(1000000);
                    cout << "\n-- THE END --" << endl;
                    usleep(1000000);
                } 
                // ENDING 4
                else {
                    cout << "\n========================================" << endl;
                    cout << "             ENDING 4                   " << endl;
                    cout << "========================================" << endl;
                    usleep(1000000);
                    cout << "\nThe dragon kneels before you, broken." << endl;
                    usleep(1000000);
                    cout << "You lower your weapon and turn to walk away." << endl;
                    usleep(1000000);
                    cout << "\nA low rumble echoes behind you. Not a roar. Something else." << endl;
                    usleep(1000000);
                    cout << "You turn back." << endl;
                    usleep(1000000);
                    cout << "The dragon extends its claw toward you." << endl;
                    usleep(1000000);
                    cout << "Resting in its palm: the Magic Crystal. A gift." << endl;
                    usleep(1000000);
                    cout << "\nYou take it. Power moves through you like a current." << endl;
                    usleep(1000000);
                    cout << "The dragon rises and stands at your side." << endl;
                    usleep(1000000);
                    cout << "\nYou return to Eldoria. As a ruler. With a dragon at your back." << endl;
                    usleep(1000000);
                    cout << "No one dares question your reign." << endl;
                    usleep(1000000);
                    cout << "\n-- THE END --  (The best power is the kind others fear to challenge.)" << endl; //best ending :)
                    usleep(1000000);
                }
                exit(0); //stopping the entire function
                
            } else {
                cout << "\nThe Dragon's power overwhelms you..." << endl;
                usleep(1000000);
                cout << "\nYou wake up at the dungeon entrance." << endl;
                usleep(1000000);
                cout << "The Statue of Grace still glows faintly beside you." << endl;
                usleep(1000000);
                player.respawn(player.maxHp);
            }
        }
    }
}