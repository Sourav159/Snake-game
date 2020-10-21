#ifndef SNAKE_GAME_SNAKE
#define SNAKE_GAME_SNAKE

#include "splashkit.h"
#include <vector>

using namespace std;
using std::vector;


#define SNAKE_ROTATE 90 
#define SCREEN_BORDER 50


/**
 * The snake data keeps track of all of the information related to the snake.
 * 
 * @field   snake_sprite   The snake's sprite - used to track position and movement
 * @field   score          Used to store current score for the player
 * @field   right          Used to check the right posiion of the snake
 * @field   left           Used to check the left posiion of the snake
 * @field   up             Used to check the up posiion of the snake
 * @field   down           Used to check the down posiion of the snake
 * @field   health_pct     Used to track the health percentage of the snake
 * @field   snake_Speed    Used to track the speed of the snake
 **/
struct snake_data
{
    sprite            snake_sprite;
    int               score;
    bool              right;
    bool              left;
    bool              up;
    bool              down;
    double            health_pct;
    double            snake_speed;
};

/**
 * Creates a new snake in the centre of the screen with the default values.
 * 
 * @returns     The new snake data
 */
snake_data new_snake();

/**
 * Draws the snake to the screen. 
 * 
 * @param snake_to_draw    The snake to draw to the screen
 */
void draw_snake(const snake_data &snake_to_draw);

/**
 * Actions a step update of the snake - moving the snake.
 * 
 * @param snake_to_update      The snake being updated
 */
void update_snake(snake_data &snake_to_update);

/**
 * Read user input and update the snake based on this interaction.
 * 
 * @param snake    The snake to update
 */
void handle_input(snake_data &snake);


#endif 