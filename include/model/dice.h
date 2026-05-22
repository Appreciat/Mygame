#ifndef MONOPOLY_MODEL_DICE_H
#define MONOPOLY_MODEL_DICE_H

struct dice;

struct dice *dice_create(int point);
void dice_destroy(struct dice *dice);

void dice_roll(struct dice *dice,int max);
int dice_get_point(struct dice *dice);
#endif
