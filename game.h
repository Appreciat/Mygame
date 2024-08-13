#ifndef __GAME_H__
#define __GAME_H__

#include "map.h"
#include "dice.h"
#include "player.h"
#include "house.h"
#include "game.h"

struct game;

struct game *game_create();
void game_destroy(struct game *game);

struct map *game_get_map(struct game *game);
struct dice *game_get_dice(struct game *game);
struct player *game_get_player1(struct game *game);
struct player *game_get_player2(struct game *game); 
struct player *game_get_nowplayer(struct game *game);
struct house *game_get_houses(struct game *game);

void game_walk(struct game *game);
void game_turn_round(struct game *game);
void game_pay_cash(struct game *game);
void game_buy_house(struct game *game);
void game_upgrade_house(struct game *game);
void game_buy_lottery(struct game *game);
void game_use_card(struct game *game);
void game_reduce_prisonday(struct game *game); 
void game_reduce_hospitalday(struct game *game); 

bool game_is_prison(struct game *game); 
bool game_is_hospital(struct game *game); 
bool game_is_over(struct game *game);
bool game_is_card(struct game *game);
bool game_is_coin(struct game *game);

int game_get_blocktype(struct game *game);

int  game_put_space(struct game *game);
void game_put_point(struct game *game,int state);
void game_put_news(struct game *game,int newsRandom);
void game_put_park(struct game *game,int parkRandom);
void game_put_bank(struct game *game);
void game_put_prison(struct game *game);
void game_put_hospital(struct game *game); 
void game_put_shop(struct game *game,int cardRandom);
#endif 
