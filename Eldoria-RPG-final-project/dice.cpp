#include <iostream>
#include <cstdlib>
#include "dice.h"

using namespace std;

//dnd styled dice roll mechanic that accounts for critical hits on enemies and trying to escape/persuade them.
//the success rate is based on the charisma and intelligence stat (so jester has most probability and warrior the lowest)
int diceRoll(int stat100, int difficulty) {
    int modifier = (stat100 / 10) - 5;
    int roll = (rand() % 20) + 1;
    int total = roll + modifier;

    cout << "\n[Roll: " << roll << " | Modifier: " << modifier << " | Total: " << total << "]" << endl;

    if (roll == 20) {
        cout << "CRITICAL SUCCESS!\n";
        return 1;
    }
    if (roll == 1) {
        cout << "CRITICAL FAILURE!\n";
        return 0;
    }

    if (total >= difficulty) {
        cout << "SUCCESS!\n";
        return 1;
    } else {
        cout << "FAILED!\n";
        return 0;
    }
}