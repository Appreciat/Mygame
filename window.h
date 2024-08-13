#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <graphics.h>
#include <windows.h>
#include <easyx.h>

#include "game.h"
#include "controller.h"
#include "window.h"

struct window;
struct window *window_create(int width,int height);
void window_destroy(struct window *window);

struct controller *window_get_controller(struct window *window);
struct game *window_get_game(struct window *window);

void window_set_controller(struct window *window,struct controller *controller);
void window_set_game(struct window *window,struct game *game);

void window_show(struct window *winow);
void window_fresh(struct window *window);
void window_show_over(struct window *window);
	void window_show_news(struct window *window,int newsRandom);
	void window_show_park(struct window *window,int parkRandom);
	void window_show_hospital(struct window *window,int hospitalRandom);
	void window_show_hospitalday(struct window *window);
	void window_show_prison(struct window *window,int prisonRandom); 
	void window_show_prisonday(struct window *window);
	void window_show_bank(struct window *window);
	void window_show_point(struct window *window,int state);
	
bool window_isDiceButtonClicked(struct window *window,int x,int y);
	bool window_show_isUpgradeHouseMessage(struct window *window); 
	bool window_show_isBuyHouseMessage(struct window *window); 
	bool window_show_isBuyLotteryMessage(struct window *window);
	bool window_show_isBuyCardMessage(struct window *window);
	bool window_show_isUseCardMessage(struct window *window); 
#endif
