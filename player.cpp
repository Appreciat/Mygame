#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "card.h"
struct player{
	char name[50];
	int number;
	int cash;
	int coin;
	int prison;
	int hospital;
	int x;
	int y;
	int count;
	struct card *card; 
};

struct player *player_create(const char *name,int number,int cash,int coin,int x,int y){
	struct player *player = NULL;
	player = (struct player *)malloc(sizeof(struct player));
	if(player == NULL) return NULL;
	
	strcpy(player->name , name);
	player->number = number;
	player->cash = cash;
	player->coin = coin;
	player->x = x;
	player->y = y;
	player->prison = 0;
	player->hospital = 0;
	player->count = 0;	
	player->card = NULL;
	
	return player;
}
void player_destroy(struct player *player){
	if(player == NULL) return ;
	free(player);
	return ;	
}

char *player_get_name(struct player *player){
	return player->name;
}

int player_get_number(struct player *player){
	return player->number;
}

int player_get_cash(struct player *player){
	return player->cash;
}

int player_get_coin(struct player *player){
	return player->coin;
}

int player_get_prison(struct player *player){
	return player->prison;
}

int player_get_hospital(struct player *player){
	return player->hospital;
}

int player_get_x(struct player *player){
	return player->x;
}

int player_get_y(struct player *player){
	return player->y;
}

int player_get_count(struct player *player){
	return player->count;
}

struct card *player_get_card(struct player *player){
	return player->card;
}

void player_set_cash(struct player *player,int cash){
	player->cash = cash;
}

void player_set_coin(struct player *player,int coin){
	player->coin = coin;
}

void player_set_prison(struct player *player,int prison){
	player->prison = prison;
}

void player_set_hospital(struct player *player,int hospital){
	player->hospital = hospital;
}

void player_set_x(struct player *player,int x){
	player->x = x;
}

void player_set_y(struct player *player,int y){
	player->y = y;
}

void player_set_count(struct player *player,int count){
	player->count = count;
}

void player_set_card(struct player *player,struct card *card){
	player->card = card;
}
