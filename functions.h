#include <stdio.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

enum enum_keys {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

typedef struct {
	float x, y;
	int center_x, center_y;
	ALLEGRO_BITMAP *img;
} PlayerStruct;

typedef struct {
	float x, y;
	int center_x, center_y;
	double diff_x, diff_y;
	double angle;
	ALLEGRO_BITMAP *img;
} BulletStruct;

void initAllegro(ALLEGRO_TIMER **timer, ALLEGRO_DISPLAY **display, ALLEGRO_BITMAP **img, ALLEGRO_EVENT_QUEUE **event_queue);
void endAllegro(ALLEGRO_TIMER **timer, ALLEGRO_DISPLAY **display, ALLEGRO_BITMAP **img, ALLEGRO_EVENT_QUEUE **event_queue);
void handleEvents(bool *doexit, bool *redraw, bool *shoot, bool keys[], ALLEGRO_EVENT_QUEUE **event_queue, PlayerStruct *player, int *mouse_x, int *mouse_y);
