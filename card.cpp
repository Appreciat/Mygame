#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*	 ���ſ�Ƭ	
1����λ����ʹ�ô˿���˫����λ�ý��л����� 
2�����Ῠ��ʹ�ô˿�������Է������з��ݡ� 
3����ƶ����ʹ�ô˿���˫����Ǯ����ƽ�֡� 
4�����߿���ʹ�ô˿����Լ����µķ���ȫ������һ���� 
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
		case 1: sprintf(card->instruction , "˫����λ�ý��л���"); break; 
		case 2: sprintf(card->instruction , "����Է������з���"); break;
		case 3: sprintf(card->instruction , "��˫���Ľ�Ǯ����ƽ��"); break;
		case 4: sprintf(card->instruction , "�Լ����µ����з�������һ��"); break;
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
