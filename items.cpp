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