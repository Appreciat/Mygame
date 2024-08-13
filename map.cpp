#include <stdio.h>
#include <stdlib.h>

const int SPACE = 1;
const int PIONT_10 = 2;
const int PIONT_30 = 3;
const int PIONT_50 = 4;
const int SHOP = 5;
const int LOTTERY = 6;
const int NEWS = 7;
const int HOSPITAL = 8;
const int PARK = 9;
const int BANK = 10;
const int PRISON = 11;
const int NULL_SET = 0;

struct map{
	int row;
	int col;
	int **data;
};

struct map *map_create(){
	struct map *map = NULL;
	map = (struct map *)malloc(sizeof(struct map));
	if(map == NULL) return NULL;
	
	map->row = 8;
	map->col = 13;
	
	map->data = (int **)malloc(sizeof(int *)*map->row);
	for(int i = 0;i < map->row;i++){
		map->data[i] = (int *)malloc(sizeof(int )*map->col);
	}
	return map;
}

void map_destroy(struct map *map){	
	
	for(int i = 0;i < map->row;i++){
		free(map->data[i]);
	}
	free(map);
	return ;
}

void map_init(struct map *map){
	int data[8][13] = {
            // 模仿大富翁其中一个地图设置
            {BANK, SPACE, NEWS, SPACE, NEWS, SPACE, NEWS, PRISON, SPACE, SPACE, NEWS, SPACE, NEWS},
            {PARK, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, PIONT_30},
            {PARK, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, PIONT_50},
            {PIONT_10, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, PIONT_10},
            {PIONT_50, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, PIONT_50},
            {BANK, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, SHOP},
            {PIONT_50, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, NULL_SET, PIONT_50},
            {BANK, NEWS, SPACE, NEWS, SPACE, NEWS, SPACE, NEWS, HOSPITAL, NEWS, SPACE,SPACE, SPACE}
		};
		
	for(int i = 0;i < 8;i++){
		for(int j = 0;j < 13;j++){
			if(data[i][j] != 0) map->data[i][j] = data[i][j];
			else map->data[i][j] = 0;
		}
	}
	
	return ;
}

int map_get_landtype(struct map *map,int x,int y){
	int row = y / 60;
	int col = x / 60;
	
	return map->data[row][col];
}

int **map_get_data(struct map *map){
	return map->data;
}

int map_get_row(struct map *map){
	return map->row;
}

int map_get_col(struct map *map){
	return map->col;
}
