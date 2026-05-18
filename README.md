# Eldoria-RPG-final-project

About this project
Eldoria is a short RPG inspired by D&D, played in the terminal, written entirely in C++

Originally thought of as a simple linear game like Colossal Cave Adventure, this project evolved into a fully abstracted, multi-file adventure game. Players must navigate Kingdom of Eldoria, battling monsters, looting chests, and making demanding choices to reach the Massive Dragon beneath Castle Darkmore.

The game mixes both non-linear and linear exploration with a proper, simple narrative, utilizing a custom combat system and dice-roll mechanics to determine the outcome of stealth, charisma, and intelligence checks and critical hits in battles.

⚔️ Key Features:

Class System: Choose between a Warrior, Mage, or Jester, each with unique starting stats (HP, Attack, Stealth, Charisma, and Intelligence) that can drastically affect how you interact with the world.
Dynamic Combat: A turn-based combat loop that handles critical hits, item usage (Healing Potions, Bombs), and escape attempts.
Exploration and Leveling: Explore rooms, fight enemies, loot chests, and level up to get stronger. Recommended to explore, otherwise punished by a harder challenge.
Multiple Endings: Your choices, alliances, and success in side-quests can directly affect battle and the final outcome of the game.
💻 Technical Overview:

Inheritance and OOP: Enemies are generated using a class hierarchy. The base Enemy class branches into specific subclasses (PlainsEnemy, CastleEnemy, BossEnemy, NPC), making use of functions for combat behavior.
Memory Management: Use of & operator to ensure player stats, inventory states, and progression stays consistent across different environment files.
File Abstraction: The code is heavily abstracted, separating the core game loops, environment maps, entity classes, and dice mechanics into 13 header (.h) and source (.cpp) files to prevent clutter/spaghetti code.
🚀 How to Compile and Run:

Open your terminal in the project folder and paste the following command to compile all the files and launch the game:

g++ main.cpp player.cpp enemy.cpp dice.cpp plains.cpp castle.cpp dungeon.cpp -o main ; if ($?) { .\main }
