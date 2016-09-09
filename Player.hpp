#ifndef DEF_PLAYER
#define DEF_PLAYER

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Player {
public:
	int x, y;
	int center_x, center_y;
	ALLEGRO_BITMAP *img;

	Player(int x, int y, int center_x, int center_y, std::string imgPath);
};

#endif
