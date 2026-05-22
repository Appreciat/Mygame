#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <easyx.h>
#include <windows.h>

#include "game.h"
#include "controller.h"
#include "window.h"

char prisontip[4][200] = {
{""}, 
		{"您因财务问题被要求在监狱中度过3天，以配合审计。希望您在这段时间里能有所反思。"},
		{"行为不当，监狱反省3日。"},
		{"为了您的安全，您需要在监狱中避一避工人的怒火，3天的时间或许能让他们冷静下来"}
};

static void window_center(struct window *window);

static void window_show_map_area(struct window *window,int x,int y);
	static void window_show_player_on_map_area(struct player *player,int dx,int dy);
	static void window_show_nowplayer_on_map_area(struct player *player,int dx,int dy);
	static void window_show_house_on_map_area(struct game *game,int dx,int dy);
static void window_show_dice_area(struct window *window,int x,int y);
static void window_show_playerinfo_area(struct window *window,int x,int y);

static void window_show_winner(struct player *player, int x , int y);
static void window_show_loser(struct player *player, int x, int y);

struct window{
	struct controller *controller;
	struct game *game;
	int width;
	int height;
	HWND hwd;
};

struct window *window_create(int width,int height){
	struct window *window = (struct window *)malloc(sizeof(struct window));
	if(window == NULL) return NULL;
	
	window->controller = NULL;
	window->game = NULL;
	window->height = height;
	window->width = width;
	window->hwd = initgraph(width , height , EX_SHOWCONSOLE);
	
	return window;
}
void window_destroy(struct window *window){
	if(window == NULL) return ;
	
	free(window);
}

struct controller *window_get_controller(struct window *window){
	return window->controller;
}

struct game *window_get_game(struct window *window){
	return window->game;
}

void window_set_controller(struct window *window,struct controller *controller){
	window->controller = controller;
	return ;
}
void window_set_game(struct window *window,struct game *game){
	window->game = game;
	return ;
}

static void window_center(struct window *window){
	HWND hDeskTop = GetDesktopWindow();
	HWND hwnd = GetHWnd(); 
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int width = window->width;
	int height = window->height;
	int x = (screenWidth - width) / 2;
	int y = (screenHeight - height) / 2;
	MoveWindow(hwnd , x, y, width, height, TRUE);
} 
void window_show(struct window *window){
	struct game *game = NULL;
	game = window->game;
	
	window_center(window);
	window_show_map_area(window , 20 , 20);
		window_show_player_on_map_area(game_get_player1(game) , 20, 20);
		window_show_player_on_map_area(game_get_player2(game) , 20, 20);
		window_show_nowplayer_on_map_area(game_get_nowplayer(game) , 20, 20);
	window_show_dice_area(window, 730 + 100 , 320);
	window_show_playerinfo_area(window , 830 , 20);
	return ;
}

void window_fresh(struct window *window){
	struct game *game = NULL;
	game = window->game;
	
	window_show_map_area(window , 20 , 20);
		window_show_house_on_map_area(game , 20, 20);
		window_show_player_on_map_area(game_get_player1(game) , 20, 20);
		window_show_player_on_map_area(game_get_player2(game) , 20, 20);
		window_show_nowplayer_on_map_area(game_get_nowplayer(game) , 20, 20);
	
	window_show_dice_area(window, 730 + 100 , 320);
	window_show_playerinfo_area(window , 830 , 20);
	return ;
}

void window_show_map_area(struct window *window,int x,int y){
	IMAGE img;
	struct game *game = window_get_game(window);
	struct map *map = game_get_map(game);
	int **data = map_get_data(map);
	
	loadimage(&img,"./images/window/land.jpg");
	
	for(int i = 0;i < map_get_row(map);i++){
		for(int j = 0;j < map_get_col(map);j++){
			if(data[i][j] != 0){
				int srcX = (data[i][j] - 1)*60;
				int srcY = 0;
							
				int srcWidth = img.getwidth() / 11;  
				int srcHeight = img.getheight();
							
				//定义要绘画在的图片区域	
				int destX = x + j*srcWidth;
				int destY = y + i*srcHeight;
							
				int destWidth = srcWidth;
				int destHeight = srcHeight;
				putimage(destX, destY,destWidth,destHeight,&img,srcX,srcY);
			}
		}
	}
	
	return ;
}

static void window_show_player_on_map_area(struct player *player,int dx,int dy){
	IMAGE img;
	int number = player_get_number(player);
	char path[50] = "./images/player/";
	int len = strlen(path);
	
	number += 48;
	path[len] = number;
	path[len + 1] = '\0';
	strcat(path,"/mini_01.png");
	
	loadimage(&img, path);
	putimage(player_get_x(player) + dx + 25, player_get_y(player) + dy + 25, &img);
}

static void window_show_nowplayer_on_map_area(struct player *player,int dx,int dy){
	IMAGE img;
	int number = player_get_number(player);
	char path[50] = "./images/player/";
	int len = strlen(path);
	
	number += 48;
	path[len] = number;
	path[len + 1] = '\0';
	strcat(path,"/mini_01_on.png");
	
	loadimage(&img, path);
	putimage(player_get_x(player) + dx + 25, player_get_y(player) + dy + 25, &img);
}

static void window_show_house_on_map_area(struct game *game,int dx,int dy){
	IMAGE img1,img2;
	
	loadimage(&img1,"./images/building/house01.png");
	loadimage(&img2,"./images/building/house02.png");
	
	struct house  *houses = game_get_houses(game);
	struct player *player1 = game_get_player1(game);
	struct player *player2 = game_get_player2(game);
	struct house *p = house_get_next(houses);
	
	while(p != NULL){
		int level = house_get_level(p);
		
		int dstX = house_get_x(p) + dx;
		int dstY = house_get_y(p) + dy;
		
		int dstWidth = 60; 
		int dstHeight = 60;  
		
		int srcX = 60 * (level - 1);
		int srcY = 40;
		
		if(house_get_player(p) == player1){
			putimage(dstX, dstY, dstWidth, dstHeight, &img1, srcX, srcY);
			outtextxy(dstX + 15 , dstY , player_get_name(player1)); 
		} else {
			putimage(dstX, dstY, dstWidth, dstHeight, &img2, srcX, srcY);
			outtextxy(dstX + 15 , dstY, player_get_name(player2)); 
		}
		
		p = house_get_next(p);
	}
	
	return ;
}

static void window_show_dice_area(struct window *window,int x,int y){
	IMAGE img;
	struct game *game = window->game;
	struct dice *dice = game_get_dice(game);
	int point = dice_get_point(dice);
	int len = 0;
	
	clearrectangle(x , y, x + 180 , y + 120);
	
	char path[50] = "images/dice/point/";
	point += 48;
	len = strlen(path);
	path[len + 1] = '\0';
	
	path[len] = point;
	strcat(path,".png");
	

	loadimage(&img,path);	
	putimage(x, y,&img);
	
	outtextxy(x + 120, y + 20, player_get_name(game_get_nowplayer(game)));
	outtextxy(x + 120 , y + 20 + 20,"点击");
	outtextxy(x + 120 , y + 40 + 20,"投掷"); 
	
	rectangle(x , y, x + 180 , y + 120);
	return ;
}

static void window_show_playerinfo_area(struct window *window,int x,int y){
	struct game *game = window->game;
	struct player *player1 = game_get_player1(game);
	struct player *player2 = game_get_player2(game);
	IMAGE img1,img2;
	
	clearrectangle(x , y , x + 180 , y + 210);
	int number = player_get_number(player1);
	char path[50] = "./images/player/";
	int len = strlen(path);
	char text[200];
	
	number += 48;
	path[len] = number;
	path[len + 1] = '\0';
	strcat(path,"/mini_02.png");
	
	loadimage(&img1, path);
	putimage(x + 10, y + 10 , &img1);
	
	sprintf(text,"姓名: %s",player_get_name(player1));
	outtextxy(x + 10 , y + 20 + img1.getheight() , text);
	
	sprintf(text,"现金: %d",player_get_cash(player1));
	outtextxy(x + 10 , y + 50 + img1.getheight() , text);
	
	sprintf(text,"点券: %d",player_get_coin(player1));
	outtextxy(x + 10 , y + 80 + img1.getheight() , text);
	
	sprintf(text,"房屋: %d",player_get_count(player1));
	outtextxy(x + 10 , y + 110 + img1.getheight() , text);
	
	memset(path , 0 , sizeof(path));
	strcpy(path , "./images/player/");
	
	number = player_get_number(player2);
	len = strlen(path);
		
	number += 48;
	path[len] = number;
	path[len + 1] = '\0';
	strcat(path,"/mini_02.png");
	
	loadimage(&img2, path);
	putimage(x + 30 + img1.getwidth(), y + 10 , &img2);
	
	sprintf(text,"姓名: %s",player_get_name(player2));
	outtextxy(x + 30 + img1.getwidth(), y + 20 + img1.getheight() , text);
	
	sprintf(text,"现金: %d",player_get_cash(player2));
	outtextxy(x + 30 + img1.getwidth(), y + 50 + img1.getheight() , text);
	
	sprintf(text,"点券: %d",player_get_coin(player2));
	outtextxy(x + 30 + img1.getwidth(), y + 80 + img1.getheight() , text);
	
	sprintf(text,"房屋: %d",player_get_count(player2));
	outtextxy(x + 30 + img1.getwidth(), y + 110 + img1.getheight() , text);
	
	rectangle(x , y , x + 180 , y + 210);
	return ;
}

bool window_isDiceButtonClicked(struct window *window,int x,int y){
	if(x >= 830 && x <= 830 + 180 && y >= 320 && y <= 320 + 120) //骰子区域的矩形 
	return true;
	
	return false;
}

void window_show_news(struct window *window,int newsRandom){
	char path[100];
    snprintf(path, sizeof(path), "./images/event/news/%d.jpg", newsRandom);

    IMAGE img;
	loadimage(&img, path);
    putimage(1030, 20, &img);

	
	Sleep(1000);
	clearrectangle(1030 , 20 , 1030 + img.getwidth() , 20 + img.getheight());
}

void window_show_park(struct window *window,int parkRandom){
	char path[100];
    snprintf(path, sizeof(path), "./images/event/park/%d.jpg", parkRandom);

    IMAGE img;
	loadimage(&img, path);
    putimage(1030, 20, &img);
	
	Sleep(1000);
	clearrectangle(1030,20,1030 + img.getwidth(),20 + img.getheight());	
	return ;
}

void window_show_bank(struct window *window){
	struct game *game = window->game;
	struct player *player = game_get_nowplayer(game);
	
	MessageBox(window->hwd,"银行发放1000现金，请继续加油！",player_get_name(player),MB_OKCANCEL);
	return ; 
}

void window_show_hospital(struct window *window, int hospitalRandom) {
    char path[100];
    snprintf(path, sizeof(path), "./images/event/hospital/%d.jpg", hospitalRandom);

    IMAGE img;
	loadimage(&img, path);
    putimage(1030, 20, &img);
    
	Sleep(1000);
    clearrectangle(1030, 20, 1030 + img.getwidth(), 20 + img.getheight());
}


void window_show_prison(struct window *window,int prisonRandom){
	struct game *game = NULL;
	struct player *player = NULL;
	
	game = window->game;
	player = game_get_nowplayer(game);
	
	MessageBox(window->hwd, prisontip[prisonRandom] , player_get_name(player), MB_OKCANCEL);
}

void window_show_hospitalday(struct window *window){
	struct game *game = window->game;
	struct player *player = game_get_nowplayer(game);
	char text[200];
	sprintf(text , "还需要在医院待上%d天呢",player_get_hospital(player));
	MessageBox(window->hwd,text ,player_get_name(player), MB_OK);
}

void window_show_prisonday(struct window *window){
	struct game *game = window->game;
	struct player *player = game_get_nowplayer(game);
	char text[200];
	sprintf(text , "还需要在监狱待上%d天呢",player_get_prison(player));
	MessageBox(window->hwd,text ,player_get_name(player), MB_OK);
}

void window_show_point(struct window *window,int state){
	char text[200];
	struct game *game = window->game;
	struct player *player = game_get_nowplayer(game);
	
	switch(state){
		case 1: sprintf(text,"恭喜获得10点券!");
		case 2:	sprintf(text,"恭喜获得20点券!");
		case 3:	sprintf(text,"恭喜获得50点券!");
	}
	MessageBox(window->hwd,text ,player_get_name(player), MB_OK);
}

bool window_show_isUpgradeHouseMessage(struct window *window){
	struct game *game = window->game;
	struct player *player = game_get_nowplayer(game);
	
	int ok = MessageBox(window->hwd,"可以花费300金币升级房屋",player_get_name(player), MB_OKCANCEL);
	
	if(ok == IDOK) return true;
	return false;
}

bool window_show_isBuyHouseMessage(struct window *window){
	struct game *game = window->game;
	struct player *player = game_get_nowplayer(game);
	
	int ok = MessageBox(window->hwd,"可以花费500金币购买房屋",player_get_name(player),MB_OKCANCEL);
	
	if(ok == IDOK) return true;
	return false;
}

bool window_show_isBuyLotteryMessage(struct window *window){
	struct game *game = window->game;
	struct player *player = game_get_nowplayer(game);
	
	int ok = MessageBox(window->hwd,"可以花费200金币购买一张彩票",player_get_name(player),MB_OKCANCEL);
	
	if(ok == IDOK) return true;
	return false;
}


bool window_show_isBuyCardMessage(struct window *window){
	struct game *game = window->game;
	struct player *player = game_get_nowplayer(game);
	
	int ok = MessageBox(window->hwd , "可以花费50点券抽取一张卡片",player_get_name(player),MB_OKCANCEL);
	if(ok == IDOK) return true;
	
	return false;
} 

bool window_show_isUseCardMessage(struct window *window){
	struct game *game = window->game;
	struct player *player = game_get_nowplayer(game);
	
	char text[200];
	struct card *card = player_get_card(player);
	sprintf(text , "是否使用%s,卡片效果为%s",card_get_name(card),card_get_instruction(card));
	
	int ok = MessageBox(window->hwd , text , player_get_name(player),MB_OKCANCEL);
	if(ok == IDOK) return true;
	
	return false;
}

void window_show_over(struct window *window){
	struct game *game = window->game;
	struct player *player1 = game_get_player1(game);
	struct player *player2 = game_get_player2(game);
	
	clearrectangle(0 , 0 , window->width , window->height);
	
	if(player_get_cash(player1) < 0){
		window_show_winner(player2, 200 , 20);
		window_show_loser(player1, 800 , 20);
	} else {
		window_show_winner(player1, 200 , 20);
		window_show_loser(player2, 800 , 20);
	}
	
	getchar();
}

static void window_show_winner(struct player *player, int x , int y){
	IMAGE img;
	IMAGE win;
	
	char path[100];
    snprintf(path, sizeof(path), "./images/player/%d/smile.png", player_get_number(player));

	loadimage(&img, path);	
	loadimage(&win ,"./images/effect/win_/13.png");
	
	putimage(x , y ,&win);
	putimage(x , y + win.getheight() , &img);
}

static void window_show_loser(struct player *player, int x,int y){
	IMAGE img;
	IMAGE loser;
	
	char path[100];
    snprintf(path, sizeof(path), "./images/player/%d/sad.png", player_get_number(player));

	loadimage(&loser ,"./images/effect/lose_/12.png");
	loadimage(&img , path);
	
	putimage(x , y ,&loser);
	putimage(x , y + loser.getheight() , &img);
}




