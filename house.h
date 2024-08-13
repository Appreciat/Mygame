#ifndef __HOUSE_H__
#define __HOUSE_H__

struct house;

struct house *house_create();
struct house *house_create(struct player *player,int price,int level,int x,int y);

void house_destroy(struct house *house);

int house_get_x(struct house *house);
int house_get_y(struct house *house);
int house_get_level(struct house *house);
struct house *house_get_next(struct house *house);
struct player *house_get_player(struct house *house);

void house_add(struct house *head,struct house *house);
void house_set_level(struct house *house,int level);
void house_set_player(struct house *house,struct player *player);
#endif
