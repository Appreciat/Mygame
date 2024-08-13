#include <stdio.h>
#include <stdlib.h>

struct house{
	struct player *player;
	int price;
	int level;
	int x;
	int y;
	struct house *next;
};

struct house *house_create(){
	struct house *head = NULL;
	head = (struct house *)malloc(sizeof(struct house));
	if(head == NULL) return NULL;
	
	head->player = NULL;
	head->price = 0;
	head->x = -1;
	head->y = -1;
	head->next = NULL;
	
	return head;	
}

struct house *house_create(struct player *player,int price,int level,int x,int y){
	struct house *house = NULL;
	house = (struct house *)malloc(sizeof(struct house));
	if(house == NULL) return NULL;
	
	house->player = player;
	house->price = price;
	house->level = level;
	house->x = x;
	house->y = y;
	house->next = NULL;
	
	return house;
}

void house_destroy(struct house *house){
	if(house == NULL) return ;
	
	free(house);
}

int house_get_x(struct house *house){
	return house->x;
}

int house_get_y(struct house *house){
	return house->y;
}

int house_get_level(struct house *house){
	return house->level;
}

int house_get_price(struct house *house){
	return house->price;
}

struct house *house_get_next(struct house *house){
	return house->next;
}

struct player *house_get_player(struct house *house){
	return house->player;
}

void house_add(struct house *head,struct house *house){
	struct house *p = NULL;
	p = head;
	
	while(p->next != NULL){
		p = p->next;
	}
	p->next = house;	
	return ;
}

void house_set_level(struct house *house,int level){
	house->level = level;
	return ;
}

void house_set_player(struct house *house,struct player *player){
	house->player = player;
}


