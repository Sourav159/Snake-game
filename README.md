# Snake Game
Welcome to the Snake Game! This is a simple console-based snake game implemented in C++ using the SplashKit library. Below are the details of the code structure and functionality.

## Overview: 
This Snake Game features a snake that moves around the screen collecting different items while avoiding obstacles. The game includes a scoring system, a health bar, and various items such as fruits, hearts, and stones.

## Dependencies: 
SplashKit: SplashKit is used to handle graphics, input, and sound in the game.

## How to Play: 
Use the arrow keys to control the snake's movement.
Collect fruits to increase your score.
Avoid stones, as they will end the game.
Hearts increase your health.
The game ends if the snake goes out of bounds or runs out of health.
Watch a screencast of the game demonstration here and the code demonstration here.

## Code Structure: 

### program.cpp:
The entry point of the program. It initializes the game window, loads resources, and starts a new game.

### snake_game.h:
Header file containing declarations for the main game functions, structures, and constants.

### snake_game.cpp:
Implementation file containing the main game logic, including functions for starting a new game, updating the game state, handling collisions, and drawing the game.

### items.h:
Header file with declarations for item-related functions, structures, and constants.

### items.cpp:
Implementation file with functions for creating, updating, and drawing items in the game.

### snake.h:
Header file with declarations for snake-related functions, structures, and constants.

### snake.cpp:
Implementation file with functions for creating, updating, and drawing the snake, as well as handling user input.

### Feel free to explore the code files to understand the details of the Snake Game implementation. Enjoy playing!
