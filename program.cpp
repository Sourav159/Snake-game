// Link to screencast of game demonstration: https://video.deakin.edu.au/media/t/0_6x3eoke1 
// Link to screencast of code demonstration: https://video.deakin.edu.au/media/t/0_o8ukcybv

#include "splashkit.h"
#include "snake.h"
#include "items.h"
#include "snake_game.h"

/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "snake_game.txt");
}

/**
 * Entry point by creating a new game
 */
int main()
{
    open_window("Snake Game", 800, 600);
    load_resources();

    // Callling the new game function to start the game
    new_game();

    return 0;
}
