#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "window.h"
#include "controller.h"

static void space_event(struct controller *controller);
static void point_event(struct controller *controller,int state);
static void shop_event(struct controller *controller);
static void lottery_event(struct controller *controller);
static void news_event(struct controller *controller);
static void hospital_event(struct controller *controller);
static void park_event(struct controller *controller);
static void bank_event(struct controller *controller);
static void prison_event(struct controller *controller);

struct controller{
	struct game *game;
	struct window *window;
};

struct controller *controller_create(){
	struct controller *controller = (struct controller *)malloc(sizeof(struct controller));
	if(controller == NULL) return NULL;
	
	controller->game = NULL;
	controller->window = NULL;
	return controller;
}

void controller_destroy(struct controller *controller){
	if(controller == NULL) return ;
	
	free(controller);
	return ;
}

struct game *controller_get_game(controller *controller){
	return controller->game;
}

struct window *controller_get_window(controller *controller){
	return controller->window;
}

void controller_set_game(controller *controller, game *game){
	controller->game = game;
	
	return ;
}
void controller_set_window(controller *controller, window *window){
	controller->window = window;
	
	return ;
}

void click_dice_event(controller *controller){
	struct game *game = controller->game;
	struct player *player = game_get_nowplayer(game);
	
	// 阶段1 ： 准备 
	if(game_is_prison(controller->game)){
		window_show_prisonday(controller->window);
		game_reduce_prisonday(game);
		
		game_turn_round(game);
		window_fresh(controller->window);
		return ;
	}
	
	if(game_is_hospital(controller->game)){ 
		window_show_hospitalday(controller->window);
		game_reduce_hospitalday(game);
	
		game_turn_round(game);
		window_fresh(controller->window);
		return ;
	}
	
	game_walk(game);
	window_fresh(controller->window);
	
	int state = game_get_blocktype(game);
	
	switch(state){
		case 1:
			space_event(controller);
			break;
		
		case 2:
			point_event(controller, 1); 
			break;
			
		case 3:
			point_event(controller, 2);
			break;
			
		case 4:
			point_event(controller, 3);
			break;
			
		case 5:
			shop_event(controller);
			break;
			
		case 6:
			lottery_event(controller);
			break;
		
		case 7:
			news_event(controller);
			break;
		
		case 8:
			hospital_event(controller);
			break;
		
		case 9:
			park_event(controller);
			break;
		
		case 10:
			bank_event(controller);
			break;
		case 11:
			prison_event(controller);
			break;
	}
	game_turn_round(game);
	window_fresh(controller->window);
	
	// 使用卡片 
	if(game_is_card(controller->game) ){
		if( window_show_isUseCardMessage(controller->window) ){
			game_use_card(controller->game);
		}
		window_fresh(controller->window);
	}
	
	if( game_is_over(game) ){
		window_show_over(controller->window);
		exit(0);
	}
}

static void space_event(struct controller *controller){
	switch(game_put_space(controller->game)){
		/* 说明可以升级房屋 */
		case 1: {
			if(window_show_isUpgradeHouseMessage(controller->window))
			game_upgrade_house(controller->game);
	
			break;
		}
		/* 说明需要支付房屋费用 */ 
		case 2: game_pay_cash(controller->game); break;
		/* 说明可以建造房屋*/
		case 3:{
			if(window_show_isBuyHouseMessage(controller->window))
			game_buy_house(controller->game);
			break;
		}
	}
	
	return ;
}

static void point_event(struct controller *controller,int state){
	 game_put_point(controller->game, state);
	 return ;
}

static void shop_event(struct controller *controller){
	if( !game_is_coin(controller->game) || game_is_card(controller->game)) return ;
	
	if( window_show_isBuyCardMessage(controller->window) ){
		
		struct dice *dice = NULL;
		dice = dice_create(-1);
		dice_roll(dice , 1);
		
		int cardRandom = dice_get_point(dice);
		
		dice_destroy(dice);
		game_put_shop(controller->game,cardRandom);
	}
	return ;
}

static void lottery_event(struct controller *controller){
	if(window_show_isBuyLotteryMessage(controller->window)){
		game_buy_lottery(controller->game);
		return ;
	}
}

static void news_event(struct controller *controller){ //这里有对临时骰子的可见性 
	int newsRandom = 0;
	struct dice *dice = NULL;
	
	dice = dice_create(-1);
	dice_roll(dice , 15);
	newsRandom = dice_get_point(dice);
	dice_destroy(dice);

	game_put_news(controller->game ,newsRandom);
	window_show_news(controller->window , newsRandom);
}

static void hospital_event(struct controller *controller){
	int hospitalRandom = 0;
	struct dice *dice = NULL;
	
	dice = dice_create(-1);
	dice_roll(dice , 2);
	hospitalRandom = dice_get_point(dice);
	dice_destroy(dice);
	
	game_put_hospital(controller->game);
	window_show_hospital(controller->window , hospitalRandom);
}

static void park_event(struct controller *controller){
	int parkRandom = 0;
	struct dice *dice = NULL;
	
	dice = dice_create(-1);
	dice_roll(dice , 4);
	parkRandom = dice_get_point(dice);
	dice_destroy(dice);

	game_put_park(controller->game , parkRandom);
	window_show_park(controller->window , parkRandom);
}

static void bank_event(struct controller *controller){
	game_put_bank(controller->game);
	window_show_bank(controller->window);
	
	return ;
}

static void prison_event(struct controller *controller){
	int prisonRandom = 0;
	struct dice *dice = NULL;
	
	dice = dice_create(-1);
	dice_roll(dice , 3);
	prisonRandom = dice_get_point(dice);
	dice_destroy(dice);
	
	game_put_prison(controller->game);
	window_show_prison(controller->window , prisonRandom);
}
