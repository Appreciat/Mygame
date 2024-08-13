#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*	 四张卡片	
1、换位卡：使用此卡，双方的位置进行互换。 
2、抢夺卡：使用此卡，抢夺对方的所有房屋。 
3、均贫卡：使用此卡，双方金钱进行平分。 
4、政策卡：使用此卡，自己名下的房屋全部提升一级。 
*/

struct card{
	char name[50];
	int number;
	char instruction[200];
};
struct card *card_create(const char *name,int number){
	struct card *card = (struct card *)malloc(sizeof(struct card));
	if(card == NULL) return NULL;
	
	strcpy(card->name , name);
	card->number = number;
	
	switch(number){
		case 1: sprintf(card->instruction , "双方的位置进行互换"); break; 
		case 2: sprintf(card->instruction , "抢夺对方的所有房屋"); break;
		case 3: sprintf(card->instruction , "对双方的金钱进行平分"); break;
		case 4: sprintf(card->instruction , "自己名下的所有房屋提升一级"); break;
	}
	
	return card;
};

void card_destroy(struct card *card){
	free(card);
}

char *card_get_name(struct card *card){
	return card->name;
}

int card_get_number(struct card *card){
	return card->number;
}

char *card_get_instruction(struct card *card){
	return card->instruction;
}
