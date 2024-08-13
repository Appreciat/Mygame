#include <stdio.h> 
#include <stdlib.h>

#include "map.h"
#include "dice.h"
#include "player.h"
#include "house.h"
#include "game.h"

static void game_use_exchange_card(struct game *game);
static void game_use_rob_card(struct game *game);
static void game_use_average_card(struct game *game);
static void game_use_upgrade_card(struct game *game);

struct game{
	struct map *map;
	struct dice *dice;
	struct player *player1;
	struct player *player2;
	struct player *nowplayer;
	struct house *houses;
};

struct game *game_create(){
	struct game *game = (struct game *)malloc(sizeof(struct game));
	if(game == NULL) return NULL;
	
	struct map *map = map_create();
	map_init(map);
	
	struct dice *dice = dice_create(1);
	struct player *player1 = player_create("Alice",2,10000,100,0,0);
	struct player *player2 = player_create("Bob",1,10000,100,0,0);
	struct house *head = house_create(); //虚拟头结点; 
	
	game->player1 = player1;
	game->player2 = player2;
	game->dice = dice;
	game->map = map;
	game->nowplayer = player1;
	game->houses = head;
	
	return game;
}

void game_destroy(struct game *game){
	if(game == NULL) return ;
	
	free(game);	
}

struct map *game_get_map(struct game *game){
	return game->map;
}

struct dice *game_get_dice(struct game *game){
	return game->dice;
}

struct player *game_get_player1(struct game *game){
	return game->player1;
}

struct player *game_get_player2(struct game *game){
	return game->player2;
}

struct player *game_get_nowplayer(struct game *game){
	return game->nowplayer;
}

struct house *game_get_houses(struct game *game){
	return game->houses;
}


void game_pay_cash(struct game *game){
	struct house *head = game->houses;
	struct player *player = game->nowplayer;
	struct player *player1 = game->player1;
	struct player *player2 = game->player2;
	
	struct house *p = house_get_next(head); //虚拟的头结点不计入;
	 
	while(p != NULL){
		if(house_get_x(p) == player_get_x(player) && house_get_y(p) == player_get_y(player)){ 
			if(game_get_player1(game) == player){
				int level = house_get_level(p);
				player_set_cash(player1 , player_get_cash(player1) - level*300);
				player_set_cash(player2 , player_get_cash(player2) + level*300);
			} else {
				int level = house_get_level(p);
				player_set_cash(player1 , player_get_cash(player1) + level*300);
				player_set_cash(player2 , player_get_cash(player2) - level*300);
			}
		}
		p = house_get_next(p);
	}
	return ;
}

void game_walk(struct game *game){
	struct player *player = NULL;
	struct map *map = NULL;
	struct dice *dice = NULL;
	int point = -1;
	
	player = game_get_nowplayer(game);
	map = game_get_map(game);
	dice = game_get_dice(game);
	dice_roll(dice, 6);
	
	point = dice_get_point(dice);
	
	int map_row = map_get_row(map) - 1; //地图的行数 
	int map_col = map_get_col(map) - 1; //地图的列数 
	
	int player_row = player_get_y(player) / 60;
	int player_col = player_get_x(player) / 60;
	
		if(player_row == 0) { //当人物在地图的最上侧 
				player_col += point;
				int d = map_col - player_col; //说明人物此时超出了map的范围 
				
				if(d < 0){
					player_col = map_col;
					player_row -= d;	
				}
				player_set_x(player , player_col * 60);
				player_set_y(player , player_row * 60);
				return ;
			}
			
		if(player_col == map_col){ //说明人物在地图的右侧 
			player_row += point;
			int d = map_row - player_row;
			
			if(d < 0){
				player_row = map_row;
				player_col += d;
			}
			player_set_x(player , player_col * 60);
			player_set_y(player , player_row * 60);
			return ;
		} 

		if(player_row == map_row){ //说明人物在地图的底侧了 
			player_col -= point;
			int d = 0 - player_col;
			
			if(d > 0){
				player_col = 0;
				player_row -= d; 
			}
			
			player_set_x(player , player_col * 60);
			player_set_y(player , player_row * 60);
			return ;
		} 
		
		if(player_col == 0){ //说明人物在地图的左侧了 
			player_row -= point;
			int d = 0 - player_row;
			if(d > 0){
				player_row = 0;
				player_col += d;
			}
			player_set_x(player , player_col * 60);
			player_set_y(player , player_row * 60);
			return ;
		}
		
		return ; 
}

int game_get_blocktype(struct game *game){
	struct player *player = game->nowplayer;
	struct map *map = game->map;
	
	return map_get_landtype(map , player_get_x(player) , player_get_y(player));
}

void game_turn_round(struct game *game){
	struct player *player = NULL;
	player = game->nowplayer;
	
	player == game->player1 ? game->nowplayer = game->player2 : game->nowplayer = game->player1;
}

void game_put_point(struct game *game,int state){
	struct  player *player = NULL;
	player = game->nowplayer;
	
	switch(state){
		case 1: 
			player_set_coin(player , player_get_coin(player) + 10);
			break;
		case 2:
			player_set_coin(player , player_get_coin(player) + 30);
			break;
		case 3:
			player_set_coin(player , player_get_coin(player) + 50);
			break;
	}
	return ;
}

int game_put_space(struct game *game){ //这里特殊 
	struct house *head = game->houses;
	struct player *player = game->nowplayer;
	
	struct house *p = house_get_next(head); //虚拟的头结点不计入;
	 
	while(p != NULL){
		if(house_get_x(p) == player_get_x(player) && house_get_y(p) == player_get_y(player)){ //说明空地上面有房屋 
			if(house_get_player(p) == player){
				return 1; // 1代表房屋是自己的 
			} else {
				return 2; // 2 代表房屋是别人的; 
			}
		}
		p = house_get_next(p);
	}
	
	return 3; // 3代表可以购买房屋 
}

void game_buy_house(struct game *game){
	struct player *player = game->nowplayer;
	if(player_get_cash(player) < 500) return ;
	
	struct house *house  = house_create(game_get_nowplayer(game) , 500 , 1 , player_get_x(player) , player_get_y(player));
	house_add(game->houses , house);
	player_set_cash(player , player_get_cash(player) - 500);
	player_set_count(player , player_get_count(player) + 1);
	return ;
}

void game_upgrade_house(struct game *game){
	struct player *player = game->nowplayer;
	if(player_get_cash(player) < 300) return ;
	
	struct house *head = game->houses;
	struct house *p = house_get_next(head);
	
	while(p){
		if(house_get_x(p) == player_get_x(player) && house_get_y(p)  == player_get_y(player)){
			if(house_get_level(p) > 5) return ;
			
			house_set_level(p , house_get_level(p) + 1);
			player_set_cash(player , player_get_cash(player) - 300); 
			return ;
		}
		p = house_get_next(p);	
	}
	return ;
}

void game_buy_lottery(struct game *game){
	struct player *player = NULL;
	struct dice *dice = NULL;
	int cash = 0;
	
	player = game->nowplayer;
	dice = dice_create(0);
	dice_roll(dice , 100);
	int point = dice_get_point(dice);
	
	cash = player_get_cash(player);
 	player_set_cash(player , cash - 200);
 	
 	if(point == 50){
 		player_set_cash(player , cash + 10000);	
	}
	return ;
} 

void game_put_news(struct game *game,int newsRandom){
	struct player *player = NULL;
	player = game->nowplayer;
	
	switch(newsRandom){
		case 1:{
			int coin = player_get_coin(player);
			if(coin >= 40)
			player_set_coin(player , player_get_coin(player) - 40);
			else player_set_coin(player , 0);
			break;
		}
		
		case 2:
		player_set_cash(player , player_get_cash(player) - 300);
		break;
			
		case 3:
		player_set_cash(player , player_get_cash(player) - 300);
		break;	
			
		case 4:
		player_set_cash(player , player_get_cash(player) - 400);
		break;
			
		case 5:
		player_set_cash(player , player_get_cash(player) - 500);
		break;
			
		case 6:
		player_set_cash(player , player_get_cash(player) - 10000);
		break;
			
		case 7:
		player_set_cash(player , player_get_cash(player) - 1000);
		break;
			
		case 8:
		player_set_cash(player , player_get_cash(player) - 1500);
		break;
			
		case 9:
		player_set_cash(player , player_get_cash(player) - 2000);
		break;
			
		case 10:
		player_set_cash(player , player_get_cash(player) - 3000);
		break;	
			
		case 11: 
		player_set_coin(player , player_get_coin(player) + 300);
		break;
			
		case 12:
		player_set_cash(player , player_get_cash(player) + 1000);
		break;
			
		case 13:
		player_set_cash(player , player_get_cash(player) + 2000);
		break;
			
		case 14:
		player_set_cash(player , player_get_cash(player) + 2000);
		break;
			
		case 15:
		player_set_cash(player , player_get_cash(player) + 3999);
		player_set_coin(player , player_get_coin(player) + 100);
		break;
	}
}

void game_put_park(struct game *game,int parkRandom){
	struct player *player = NULL;
	player = game->nowplayer;
	
	switch(parkRandom){
		case 1: 
		player_set_cash(player , player_get_cash(player) - 1);
		break;
		
		case 2:
		player_set_cash(player , player_get_cash(player) + 1);
		break;
		
		case 3:
		player_set_cash(player , player_get_cash(player) - 200);
		break;
		
		case 4:
		player_set_cash(player , player_get_cash(player) + 200);
		break;
	}
	return ;
}

void game_put_bank(struct game *game){
	struct player *player = NULL;
	player = game->nowplayer;
	
	player_set_cash(player , player_get_cash(player) + 1000);
	return ;
}

void game_put_prison(struct game *game){
	struct player *player = NULL;
	player = game->nowplayer;
	
	player_set_prison(player , player_get_prison(player) + 3);
	return ; 
}

void game_put_hospital(struct game *game){
	struct player *player = NULL;
	player = game->nowplayer;
	
	player_set_hospital(player , player_get_hospital(player) + 3);
	return ; 
} 

void game_reduce_prisonday(struct game *game){
	struct player *player = NULL;
	player = game->nowplayer;
	
	player_set_prison(player , player_get_prison(player) - 1);
	return ;
}

void game_reduce_hospitalday(struct game *game){
	struct player *player = NULL;
	player = game->nowplayer;
	
	player_set_hospital(player , player_get_hospital(player) - 1);
}

bool game_is_prison(struct game *game){
	struct player *player = NULL;
	player = game->nowplayer;
	
	return player_get_prison(player) > 0;
}

bool game_is_hospital(struct game *game){
	struct player *player = NULL;
	player = game->nowplayer;
	
	return player_get_hospital(player) > 0;
}

bool game_is_over(struct game *game){
	struct player *player = NULL;
	player = game->nowplayer;
	
	return player_get_cash(player) < 0;
}

bool game_is_card(struct game *game){
	struct player *player = NULL;
	player = game->nowplayer;
	
	return player_get_card(player) != NULL;
}

bool game_is_coin(struct game *game){
	struct player *player = NULL;
	player = game->nowplayer;
	
	return player_get_coin(player) >= 50;
}

/*	 四张卡片	
1、换位卡：使用此卡，双方的位置进行互换。 
2、抢夺卡：使用此卡，抢夺对方的所有房屋。 
3、均贫卡：使用此卡，双方金钱进行平分。 
4、政策卡：使用此卡，自己名下的房屋全部提升一级。 
*/

void game_use_card(struct game *game){
	struct player *player = NULL;
	struct card *card = NULL;
	player = game->nowplayer;
	card = player_get_card(player);
	
	int number = card_get_number(card);
	
	switch(number){
		case 1: game_use_exchange_card(game); break;
		case 2: game_use_rob_card(game); break;
		case 3: game_use_average_card(game); break;
		case 4: game_use_upgrade_card(game); break;
	}
	
	player_set_card(player, NULL);
	card_destroy(card);
	
	return ;
}

static void game_use_exchange_card(struct game *game){
	struct player *player1 = game->player1;
	struct player *player2 = game->player2;
	
	int x1 = player_get_x(player1),y1 = player_get_y(player1);
	int x2 = player_get_x(player2),y2 = player_get_y(player2);
	
	player_set_x(player1 , x2), player_set_y(player1 , y2);
	player_set_x(player2 , x1), player_set_y(player2 , y1);
	return ;
}

static void game_use_rob_card(struct game *game){
	struct house *houses = game->houses;
	struct house *p = house_get_next(houses);
	struct player *player = game->nowplayer;
	
	while(p != NULL){
		if(house_get_player(p) != player){
			house_set_player(p , player);
		}
		p = house_get_next(p);
	}
	
	if(player == game->player1){
		player_set_count(game->player2 , 0);
	} else {
		player_set_count(game->player1 , 0); 
	}
	
	return ;
}

static void game_use_average_card(struct game *game){
	struct player *player1 = game->player1;
	struct player *player2 = game->player2;
	
	int sum = player_get_cash(player1) + player_get_cash(player2);
	player_set_cash(player1 , sum / 2); 
	player_set_cash(player2 , sum / 2);
	return ;
}

static void game_use_upgrade_card(struct game *game){
	struct player *player = game->nowplayer;
	struct house *houses = game->houses;
	
	struct house *p = house_get_next(houses);
	
	while(p != NULL){
		if(house_get_player(p) == player){
			int level = house_get_level(p);
			if(level < 5){
				house_set_level(p , level + 1);
			}
		}
		p = house_get_next(p);
	}
	return ;
}

void game_put_shop(struct game *game,int cardRandom){
	struct player *player = NULL;
	player = game->nowplayer;
	player_set_coin(player , player_get_coin(player) - 50);

	switch(cardRandom){
		case 1: {
			struct card *card = card_create("换位卡", 1);
			player_set_card(player,card);
			break;
		}
		case 2:{
			struct card *card = card_create("征地卡", 2);
			player_set_card(player,card);
			break;
		}
		case 3:{
			struct card *card = card_create("均贫卡", 3);
			player_set_card(player,card);
			break;
		}
		case 4:{
			struct card *card = card_create("红利卡", 4);
			player_set_card(player,card);
			break;
		} 
	}
	return ;
}


