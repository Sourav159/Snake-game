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