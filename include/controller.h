#ifndef MONOPOLY_CONTROLLER_H
#define MONOPOLY_CONTROLLER_H

struct controller;
struct game;
struct window;

struct controller *controller_create();
void controller_destroy(struct controller *controller);

struct game *controller_get_game(struct controller *controller);
struct window *controller_get_window(struct controller *controller);

void controller_set_game(struct controller *controller, struct game *game);
void controller_set_window(struct controller *controller, struct window *window);

void click_dice_event(struct controller *controller);

#endif
