#ifndef CASTLE_H
#define CASTLE_H

#include "player.h"

// Door A (non-linear route with side quest)
void doorA_Door1A(Player& player);
void doorA_Door1B(Player& player);
void doorA_Door1(Player& player);
void doorA_Door2A(Player& player);
void doorA_Door2B(Player& player);
void doorA_Door2(Player& player);
void doorARoute(Player& player);

// Door B (linear route with mini bosses)
void doorBRoute(Player& player);

// main hub of the castle, acts also as a checkpoint if the player dies or wants to return
void castleMap(Player& player);


//this was probably the most fun part to work on since we both did it together. It's looks lengthy just because of the outputs.

#endif