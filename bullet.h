#ifndef BULLET_H
#define BULLET_H

#include <stdio.h>
#include <allegro5/allegro.h>

typedef struct {
	float x, y;
	int center_x, center_y;
	double diff_x, diff_y;
	double angle;
	ALLEGRO_BITMAP *img;
} BulletStruct;

typedef struct nodeBullet {
	BulletStruct bullet;
	int id;
	struct nodeBullet *next;
} ListBullet;

typedef struct {
	BulletStruct *array;
	size_t used, size;
} BulletArray;

void list_add(ListBullet *head, BulletStruct b, int i);
int list_remove_head(ListBullet **head);
int list_remove_id(ListBullet **head, int id);
void list_draw(ListBullet *head, int screenWidth, int screenHeight, int bulletSpeed, int bulletWidth, int bulletHeight);

#endif
