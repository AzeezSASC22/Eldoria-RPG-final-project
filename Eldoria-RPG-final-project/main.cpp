#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "player.h"
#include "plains.h" 
#include "castle.h"
#include "dungeon.h"

using namespace std;

// this handles the intro story so it doesn't clutter the main function. not worth putting something so small in a separate file
void prologue(Player& player) {
    cout << "\nDo you want to skip the intro story? (1 for Yes, 2 for No)\nChoice: ";
    string skipChoice;
    cin >> skipChoice;

    if (skipChoice == "2") {
        cout << "\n[PROLOGUE]\n";
        usleep(1000000);
        cout << "For centuries, the kingdom of Eldoria knew peace, protected by the magic of the Black Seal.\n";
        usleep(1000000);
        cout << "But legends speak of an ancient darkness trapped deep beneath the earth.\n";
        usleep(1000000);
        
        cout << "\nNow, the Black Seal is weakening, and the earth has cracked open.\n";
        usleep(1000000);
        cout << "A Massive Dragon has risen from the depths and seized Castle Darkmore.\n";
        usleep(1000000);
        
        cout << "\nIt has unleashed a horde of corrupted creatures across the land.\n";
        usleep(1000000);
        cout << "The King's army was decimated. The surviving villagers have fled.\n";
        usleep(1000000);
        cout << "You, a lone warrior, step forward to enter the castle and slay the beast.\n";
        usleep(1000000);
    }
}

int main() {
    // seed the random number generator
    srand(time(0));
    string menuSelect;

    while (true) {
        cout << "\n======================================\n";
        cout << "         WELCOME TO ELDORIA\n";
        cout << "======================================\n";
        cout << "1. Play\n2. Exit\nSelection: ";
        cin >> menuSelect;

        if (menuSelect == "1") {
            
            cout << "\nEnter your character's name: ";
            string pName; 
            cin >> pName;

            cout << "\nChoose a class:\n1. Warrior (High HP/Damage)\n2. Mage (High Intelligence, Balanced)\n3. Jester (High Stealth/Charisma)\nSelection: ";
            string choice; 
            cin >> choice;
            
            // basic class assignment
            int classNum = 1; 
            if (choice == "2") {
                classNum = 2;
            } else if (choice == "3") {
                classNum = 3;
            }

            Player player(pName, classNum);
            
            prologue(player);
            
            player.displayStats();
            
            cout << "\nStarting the journey...\n";
            usleep(1000000);

            // start the game routes
            plainsMap(player);
            castleMap(player);
            dungeonMap(player);
            break;
            
        } else {
            cout << "\nFarewell, traveler.\n";
            usleep(1000000);
            break;
        }
    }
    return 0;
}
// g++ main.cpp player.cpp enemy.cpp dice.cpp plains.cpp castle.cpp dungeon.cpp -o main ; if ($?) { .\main } to run it (saving you time from compiling all those files :) )


/*-----------------------------
CITATIONS:
Use of & operator: https://www.youtube.com/watch?v=mS9755gF66w (Tutorial by The Chemo)
Use of 'static' keyword: Google search - 'How do I make a variable only be remember in one specific file in OOP C++'
Gemini was also used with the prompt: How would I store the memory of variables like the player and make sure things like the damage taken is remembered? It suggested the & operator

Gemini was used with the prompt: How do i break the main function after the game is done? It suggested exit(0); command
Gemini was also used in various and multiple instances to error check, and make sure all the files run together.
Gemini was used to clean up, visually structurize the code better (simplifying the variable names) for better readability with the prompt: 
'The files are cluttered and have a lot of temporary/messy variable names, suggest which variables could be changed for better readability'. 
The logic and flow of the code was still made entirely by us manually.

When the above prompt was given alongside the files, Gemini also suggested to get rid of multiple instances of the same code in the 'enemy.cpp' file 
and suggested the 'virtual' keyword and how it works to avoid clutter and 'spaghetti code'. ( learned a lot of new things :] )

The idea of the story and what would happen in certain areas was made by us. Gemini was used for wording/fleshing it out and add ASCII arts at the ending
with the prompt: 'Replace the placeholders of the story in all the files with a fleshed out version'
, 'add an ascii art for the dragonreveal' , and 'add crown ascii arts for the ruler endings'.

Gemini was also used to help in 'Merging' the two versions of our code with the prompt: 'Here are the files for my part and my partner's, to 'combine' and merge them, what variables need to be changed/redeclared?'. To which
it suggested where changes should be made and what variables might need changing or cause errors. The merging was done manually at the end.

Inspiration of combat system: Dungeons and Dragons
Accessed May 2026
------------------------------------*/


//Arham - Plains, Enemy Class, Dungeon/Endings, Half of Castle
//Azeez - Player Class, Dice, Combat System, Other half of castle, Story ideas/Prologue
