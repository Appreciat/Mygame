#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "game.h"
#include "controller.h"
#include "window.h"
#include "app.h"

struct app{
	game *game;
	controller *controller;
	window *window;
};

struct app *app_create(){
	struct app *app = (struct app *)malloc(sizeof(struct app));
	if(app == NULL) return NULL;
	
	app->game = game_create();
	app->window = window_create(1300,550);
	app->controller = controller_create();
	
	controller_set_game(app->controller , app->game);
	controller_set_window(app->controller , app->window);
	
	window_set_controller(app->window , app->controller);
	window_set_game(app->window , app->game);
	
	return app;
}

void app_destroy(app *app){
	if(app == NULL) return ;
	
	game_destroy(app->game);
	controller_destroy(app->controller);
	window_destroy(app->window);
	
	free(app);
}

void app_run(app *app){
	window_show(app->window);
	while (true) { 
        if (!MouseHit()) {
        	if (_kbhit()) break;
        	continue;
		} 
        MOUSEMSG msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {            	
            if (window_isDiceButtonClicked(app->window, msg.x , msg.y)) {
            	click_dice_event(app->controller);
			}
		}      
    }
}
