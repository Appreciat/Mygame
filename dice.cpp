#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct dice{
	int point;
};

struct dice *dice_create(int point){
	struct dice *dice = NULL;
	dice = (struct dice *)malloc(sizeof(struct dice));
	if(dice == NULL) return NULL;
	
	dice->point = point;
	return dice;
}
void dice_destroy(struct dice *dice){
	if(dice == NULL) return ;
	
	free(dice);
}

void dice_roll(struct dice *dice,int max){
	srand((unsigned int)time(NULL));
	dice->point = rand() % max + 1;	
}


int dice_get_point(struct dice *dice){
	return dice->point;
}
