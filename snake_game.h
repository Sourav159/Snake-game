#ifndef SNAKE_GAME
#define SNAKE_GAME

#include "splashkit.h"
#include "snake.h"
#include "items.h"

#include <vector>

using std::vector;
using namespace std;

/**
 * The game_data keeps track of all of the information related to the overall game.
 * 
 * @field   snake           The object of the snaek_data struct to accesss the snake's information
 * @field   items           Dynamic array of items_data to keep track of mutilple items
 * @field   game_over       To check whether the game is over or not
 *  */
struct game_data
{
    snake_data snake;
    vector<items_data> items;
    bool game_over;
};

/*
 * Creates a new game by creating a new snake, adding 3 items
 * and showing the inital screen
 * 
 */
void new_game();

/*
 * Draws the heads up display to the screen by drawing the score and health bar
 * 
 * @param game   The game to be drawn to the screen.
 */
void draw_hud(const game_data &game);

/*
 * Starts the game by drawing and updating the game
 * 
 * @param game   The game to start.
 */
void game_start(game_data &game);

/*
 * Updates the value of the item at index and plays an appropriate sound
 * according to the item.
 * 
 * @param game   The game to be updated
 * @param index  The index of the item to be updated 
 */
void apply_items(game_data &game, int index);

/*
 * Removes the item at the index from the vector of items.
 * 
 * @param game   The game to be updated
 * @param index  The index of the item to be deleted 
 */
void remove_items(game_data &game, int index);

/*
 * Checks the collision between the snake and item to call the respective procedures to
 * apply and remove the item.
 * 
 * @param game   The game to be updated
 */
void check_collisions(game_data &game);

/*
 * Adds an item to the dynamic array of the game's items by calling the new_items function
 * to add at any random position between the screen borders and screen size.
 * 
 * @param game   The game to be updated
 */
void add_items(game_data &game);

/*
 *Counts the stones and do not allow more than 2 stones to appear on the screen.
 * 
 * @param game   The game to be updated
 */
void check_stone_count(game_data &game);

/*
 * Checks the snake's position with the screen borders and ends the game
 * if the snake goes out of the playing area
 * 
 * @param game   The game to be updated
 */
void check_snake_position(game_data &game);

/*
 * Updates the game by updating the snake, items, checking collision between snake
 * and items, checking the stones count and checking teh snake's postion
 * 
 * @param game   The game being updated
 */
void update_game(game_data &game);

/*
 * Draws the game to the screen by displaying the hud, snake and items.
 * 
 * @param game   The game to draw to the screen
 */
void draw_game(const game_data &game);

#endif