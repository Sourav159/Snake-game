// program.cpp
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

//sname_game.h
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

//snake_game.cpp
#include "snake_game.h"
#include "splashkit.h"

// Function to return the drawing options of option_part_bmp
drawing_options option_part(double x, double y, double width, double height)
{
    drawing_options options;

    options = option_part_bmp(x, y, width, height, option_to_screen());

    return options;
}

// Procedure to include the elements in the HUD
void draw_hud(const game_data &game)
{
    // Drawing the area of the HUD
    fill_rectangle(COLOR_GREEN, 0, 0, screen_width(), 50, option_part(0, 0, 300, 200));

    // Drawing the score
    draw_text("Score: " + to_string(game.snake.score), COLOR_WHITE, "helvetica", 25, 150, 12, option_to_screen());

    // Drawing the health bar
    draw_text("Health: ", COLOR_WHITE, "helvetica", 25, 430, 12, option_to_screen());
    draw_bitmap("empty", 520, 16, option_part(0, 0, bitmap_width("empty"), bitmap_height("empty")));
    draw_bitmap("red_bar", 520, 16, option_part(0, 0, game.snake.health_pct * bitmap_width("red_bar"), bitmap_height("red_bar")));
}

void new_game()
{
    game_data game;

    // Creating a new snake
    game.snake = new_snake();

    game.game_over = false;

    // Adding 3 items to the game
    for (int i = 0; i < 3; i++)
    {
        add_items(game);
    }

    while (not quit_requested())
    {
        process_events();

        clear_screen();

        // Showing the inital screen with instructions
        draw_bitmap("grass", 0, 0);

        draw_text("Instructions: ", COLOR_RED, "helvetica", 30, 150, 60);
        draw_text("1. Use arrow keys to move the snake", COLOR_RED, "helvetica", 30, 150, 100);
        draw_text("2. Don't touch the screen borders !", COLOR_RED, "helvetica", 30, 150, 140);
        draw_text("3. Beware of the stones !", COLOR_RED, "helvetica", 30, 150, 180);
        draw_bitmap("press_enter", 230, 300);

        // Start the game if entered
        if (key_typed(KEYPAD_ENTER))
            game_start(game);

        refresh_screen(60);
    }
}

void game_start(game_data &game)
{

    while (not quit_requested())
    {

        process_events();

        // Handle input to adjust snake movement
        handle_input(game.snake);

        //Updating the game
        update_game(game);

        // Drawing the game
        draw_game(game);

        // If the game is over then calls the new game to start again
        if (game.game_over)
        {
            delay(100);
            new_game();
        }
    }
}

void apply_items(game_data &game, int index)
{
    // Game is over when a stone is collected
    if (game.items[index].kind == STONE)
    {
        play_sound_effect("game_over_sound");
        play_sound_effect("game_over_voice");
        game.game_over = true;
    }

    else if (game.items[index].kind == HEART)
    {
        if (game.snake.health_pct <= 1)
            game.snake.health_pct += 0.15;

        game.snake.score++;
        play_sound_effect("health_sound");
    }

    // Score is increased when a fruit is collected
    else
    {
        game.snake.score++;

        play_sound_effect("fruit_sound");
    }
}

void remove_items(game_data &game, int index)
{
    int last_idx = game.items.size() - 1;
    game.items[index] = game.items[last_idx];
    game.items.pop_back();
}

void check_collisions(game_data &game)
{

    for (int i = game.items.size() - 1; i >= 0; i--)
    {
        if (sprite_collision(game.snake.snake_sprite, game.items[i].items_sprite))
        {
            apply_items(game, i);
            remove_items(game, i);
            add_items(game); // Adding a new item when previous is removed
        }
    }
}

void add_items(game_data &game)
{
    double x, y;

    // Setting the maximun values
    double max_x = screen_width() - SCREEN_BORDER;
    double max_y = screen_height() - SCREEN_BORDER;

    // Any random position between screen max size and screen border i.e 50
    x = rnd(SCREEN_BORDER, max_x);
    y = rnd(SCREEN_BORDER, max_y);

    // Adding the new item at the synamic arrays of items
    game.items.push_back(new_items(x, y));
}

void check_stone_count(game_data &game)
{
    int count_stone = 0;

    for (int i = 0; i < game.items.size(); i++)
    {
        // Counting the number of stones
        if (game.items[i].kind == STONE)
            count_stone++;

        // Deleting the last stone if there are more than 2 of those
        if (game.items[i].kind == STONE and count_stone > 2)
        {
            remove_items(game, i);

            // Also adding a new item
            add_items(game);
        }
    }
}

void check_snake_position(game_data &game)
{
    // Getting the snake's position
    double snake_x = sprite_x(game.snake.snake_sprite);
    double snake_y = sprite_y(game.snake.snake_sprite);

    // If the snake goes out of the playing area
    if (snake_x >= screen_width() or snake_x <= 0 or snake_y >= screen_height() or snake_y <= 0)
    {
        // Game over
        play_sound_effect("game_over_sound");
        play_sound_effect("game_over_voice");
        game.game_over = true;
    }
}

void update_game(game_data &game)
{

    // Checking collisions
    check_collisions(game);

    // Checking stones count
    check_stone_count(game);

    // Checking snake position
    check_snake_position(game);

    // Updating the snake
    update_snake(game.snake);

    // Updating items
    for (int i = 0; i < game.items.size(); i++)
    {
        update_items(game.items[i]);
    }

    // If snake's health goes below 0
    if (game.snake.health_pct <= 0)
    {
        // Game over
        play_sound_effect("game_over_sound");
        play_sound_effect("game_over_voice");
        game.game_over = true;
    }
}

void draw_game(const game_data &game)
{
    clear_screen();

    draw_bitmap("grass", 0, 0);

    // Displaying the HUD
    draw_hud(game);

    // Drawing the snake
    draw_snake(game.snake);

    // Drawing the items
    for (int i = 0; i < game.items.size(); i++)
        draw_items(game.items[i]);

    refresh_screen(60);
}

//items.h
#ifndef SNAKE_GAME_ITEMS
#define SNAKE_GAME_ITEMS

#include "splashkit.h"
#include <vector>

using namespace std;

/**
 * Different options for the kind of items to be collected.
 */
enum items_kind
{
    APPLE,
    ORANGE,
    STRAWBERRY,
    BANANA,
    HEART,
    STONE,
    CHERRY,
    GRAPES,
    GUAVA
};

/**
 * The items_data keeps track of all of the information related to the items.
 * 
 * @field   items_sprite     The items's sprite - used to track position and movement
 * @field   kind             Current kind of items 
 */
struct items_data
{
    items_kind      kind;
    sprite          items_sprite;
};

/**
 * Creates a new item in the required position of the screen with a random item.
 * 
 * @returns     The new item data
 */
items_data new_items(double x, double y);

/**
 * Draws the item to the screen. 
 * 
 * @param power_to_draw    The item to draw to the screen
 */
void draw_items(const items_data &items_to_draw);

/**
 * Actions a step update of the item - moving the
 * 
 * @param power_to_update      The item being updated
 */
void update_items(items_data &items_to_update);



#endif 

//items.cpp
#include "snake.h"
#include "splashkit.h"
#include "items.h"

/**
 * The items_bitmap function converts a item kind into a 
 * bitmap that can be used.
 * 
 * Not exposed by the header.
 * 
 * @param kind  The kind of item you want the bitmap of
 * @return      The bitmap matching this item kind
 */
bitmap items_bitmap(items_kind kind)
{
    switch (kind)
    {

    case APPLE:
        return bitmap_named("apple");

    case ORANGE:
        return bitmap_named("orange");

    case STRAWBERRY:
        return bitmap_named("strawberry");

    case BANANA:
        return bitmap_named("banana");

    case STONE:
        return bitmap_named("stone");

    case HEART:
        return bitmap_named("heart");

    case CHERRY:
        return bitmap_named("cherry");

    case GRAPES:
        return bitmap_named("grapes");

    case GUAVA:
        return bitmap_named("guava");

    default:
        return bitmap_named("apple");
    }
}

items_data new_items(double x, double y)
{
    items_kind kind;
    items_data result;

    // Assigning a random item kind to the items_kind
    kind = static_cast<items_kind>(rnd(9));

    // Creating the item sprite with a random kind
    result.items_sprite = create_sprite(items_bitmap(kind));

    // Remebering the kind of the item
    result.kind = kind;

    // Setting the postion for the item sprite
    sprite_set_x(result.items_sprite, x);
    sprite_set_y(result.items_sprite, y);

    return result;
}

void draw_items(const items_data &item_draw)
{
    // Drawing the item sprite to the screen
    draw_sprite(item_draw.items_sprite);
}

void update_items(items_data &item_update)
{
    // Updating the item sprite
    update_sprite(item_update.items_sprite);
}

//snake.h
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

//snake.cpp
#include "snake.h"
#include "splashkit.h"

snake_data new_snake()
{
    snake_data result;

    result.score = 0;
    result.right = true;    //The snake is turned right at the start of the game
    result.left = false;
    result.up = false;
    result.down = false;
    result.health_pct = 1;
    result.snake_speed = 5;

    //Creating the snake sprite
    result.snake_sprite = create_sprite("snake");

    // Position in the centre of the initial screen
    int mid_x = (screen_width() - sprite_width(result.snake_sprite)) / 2;
    int mid_y = (screen_height() - sprite_height(result.snake_sprite)) / 2;

    sprite_set_x(result.snake_sprite, mid_x);
    sprite_set_y(result.snake_sprite, mid_y);

    return result;
}

void draw_snake(const snake_data &snake_to_draw)
{

    draw_sprite(snake_to_draw.snake_sprite);
}

void update_snake(snake_data &snake_to_update)
{

    // Apply movement based on rotation and velocity in the sprite
    update_sprite(snake_to_update.snake_sprite);

    // Increasing the snakes's speeed after every 5 points
    if (snake_to_update.score % 5 == 0 and snake_to_update.score != 0)
        snake_to_update.snake_speed += 0.01;

    // Decreasing the snake's health percentage while palying the game
    if (snake_to_update.health_pct > 0)
        snake_to_update.health_pct -= 0.0002;
}

void handle_input(snake_data &snake)
{

    float rotation = sprite_rotation(snake.snake_sprite);

    // Provinding speed to the snake in the x direction only
    sprite_set_dx(snake.snake_sprite, snake.snake_speed);

    // Allow change in direction with left/right/up/down keys
    if (key_down(LEFT_KEY))
    {
        // If snake is moving in up direction
        if (snake.up)
        {
            // Changing the snake's direction to left
            sprite_set_rotation(snake.snake_sprite, rotation - SNAKE_ROTATE);
            sprite_set_dx(snake.snake_sprite, snake.snake_speed);

            snake.up = false;
            snake.left = true;
        }
        // If snake is moving in down direction
        else if (snake.down)
        {
            // Changing the snake's direction to left
            sprite_set_rotation(snake.snake_sprite, rotation + SNAKE_ROTATE);
            sprite_set_dx(snake.snake_sprite, snake.snake_speed);

            snake.down = false;
            snake.left = true;
        }
    }
    else if (key_down(RIGHT_KEY))
    {
        // If snake is moving in up direction
        if (snake.up)
        {
            // Changing the snake's direction to right
            sprite_set_rotation(snake.snake_sprite, rotation + SNAKE_ROTATE);
            sprite_set_dx(snake.snake_sprite, snake.snake_speed);

            snake.right = true;
            snake.up = false;
        }
        // If snake is moving in down direction
        else if (snake.down)
        {
            // Changing the snake's direction to right
            sprite_set_rotation(snake.snake_sprite, rotation - SNAKE_ROTATE);
            sprite_set_dx(snake.snake_sprite, snake.snake_speed);

            snake.right = true;
            snake.down = false;
        }
    }

    else if (key_typed(DOWN_KEY))
    {

        // If snake is moving in right direction
        if (snake.right)
        {
            // Changing the snake's direction to down
            sprite_set_rotation(snake.snake_sprite, rotation + SNAKE_ROTATE);
            sprite_set_dx(snake.snake_sprite, snake.snake_speed);

            snake.right = false;
            snake.down = true;
        }
        // If snake is moving in left direction
        else if (snake.left)
        {
            // Changing the snake's direction to down
            sprite_set_rotation(snake.snake_sprite, rotation - SNAKE_ROTATE);
            sprite_set_dx(snake.snake_sprite, snake.snake_speed);

            snake.left = false;
            snake.down = true;
        }
    }
    else if (key_typed(UP_KEY))
    {
        // If snake is moving in right direction
        if (snake.right)
        {

            // Changing the snake's direction to up
            sprite_set_rotation(snake.snake_sprite, rotation - SNAKE_ROTATE);
            sprite_set_dx(snake.snake_sprite, snake.snake_speed);

            snake.right = false;
            snake.up = true;
        }
        // If snake is moving in left direction
        else if (snake.left)
        {
            // Changing the snake's direction to up
            sprite_set_rotation(snake.snake_sprite, rotation + SNAKE_ROTATE);
            sprite_set_dx(snake.snake_sprite, snake.snake_speed);

            snake.left = false;
            snake.up = true;
        }
    }
}

