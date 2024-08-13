#ifndef __APP_H__
#define __APP_H__

#include "game.h"
#include "controller.h"
#include "window.h"
#include "app.h"

struct app;

struct app *app_create();
void app_destroy(app *app);
void app_run(app *app);

#endif 
