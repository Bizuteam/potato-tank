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

void initAllegro(ALLEGRO_TIMER **timer, ALLEGRO_DISPLAY **display, ALLEGRO_BITMAP **player, ALLEGRO_EVENT_QUEUE **event_queue);
void handleEvents(bool *doexit, bool *redraw, bool keys[], ALLEGRO_EVENT_QUEUE **event_queue, PlayerStruct *player, int *mouse_x, int *mouse_y);
