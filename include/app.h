#ifndef MONOPOLY_APP_H
#define MONOPOLY_APP_H

struct app;

struct app *app_create();
void app_destroy(app *app);
void app_run(app *app);

#endif
