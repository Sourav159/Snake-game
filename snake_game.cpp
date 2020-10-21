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