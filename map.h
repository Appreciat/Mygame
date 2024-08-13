#ifndef __MAP_H__
#define __MAP_H__
struct map;

struct map *map_create();
void map_destroy(struct map *map);

void map_init(struct map *map);
int map_get_landtype(struct map *map,int x,int y);

int **map_get_data(struct map *map);
int map_get_row(struct map *map);
int map_get_col(struct map *map);
#endif
