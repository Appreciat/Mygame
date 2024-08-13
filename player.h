#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "card.h"

struct player;
struct player *player_create(const char *name,int number,int cash,int coin,int x,int y);
void player_destroy(struct player *player);

char *player_get_name(struct player *player);
int player_get_number(struct player *player);
int player_get_cash(struct player *player);
int player_get_coin(struct player *player);
int player_get_prison(struct player *player);
int player_get_hospital(struct player *player);
int player_get_x(struct player *player);
int player_get_y(struct player *player);
int player_get_count(struct player *player);
int player_get_index(struct player *player);
struct card *player_get_card(struct player *player);

void player_set_cash(struct player *player,int cash);
void player_set_coin(struct player *player,int coin);
void player_set_prison(struct player *player,int prison);
void player_set_hospital(struct player *player,int hospital);
void player_set_x(struct player *player,int x);
void player_set_y(struct player *player,int y);
void player_set_count(struct player *player,int count);
void player_set_card(struct player *player,struct card *card);
#endif 
