#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Player.hpp"
#include "Bullet.hpp"
#include "Map.hpp"

#define PI 3.141592653589793238462643383279502884L

enum enum_keys {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, MOUSE_LEFT
};

void initAllegro(ALLEGRO_TIMER **timer, ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue);
void endAllegro(ALLEGRO_TIMER **timer, ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue);
void handleEvents(bool *doexit, bool *redraw, bool *shoot, std::chrono::time_point<std::chrono::system_clock> *lastShot, bool keys[], ALLEGRO_EVENT_QUEUE **event_queue, Player *player, int *mouse_x, int *mouse_y);

#endif
