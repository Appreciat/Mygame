#ifndef __CARD_H__
#define __CARD_H__
struct card;
struct card *card_create(const char *name,int number);
void card_destroy(struct card *card);

char *card_get_name(struct card *card);
char *card_get_instruction(struct card *card);
int card_get_number(struct card *card);
#endif
