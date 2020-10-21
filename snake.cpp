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
