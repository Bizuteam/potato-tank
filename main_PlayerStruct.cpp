#include "functions.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include <vector>

#define PI 3.141592653589793238462643383279502884L

using namespace std;
using namespace std::chrono;

const float FPS = 60;
const int SCREEN_W = 1100;
const int SCREEN_H = 900;
const int PLAYER_SIZE = 40;
const int PLAYER_SPEED = 2;
const int BULLET_SPEED = 7;
const double FIRE_RATE = 4;

int main(int argc, char **argv) {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	int x = SCREEN_W / 2.0 - PLAYER_SIZE / 2.0, y = SCREEN_H / 2.0 - PLAYER_SIZE / 2.0;
	int center_x = x + PLAYER_SIZE/2, center_y = y + PLAYER_SIZE/2;

	PlayerStruct player = {(float) x, (float) y, center_x, center_y, NULL};

	int mouse_x = SCREEN_W/2, mouse_y = 0;

	// BulletStruct bullet = {0, 0, 0, 0, 0, 0, 0, NULL};
	// ListBullet list;
	// int bulletId = 0;

	bool keys[5] = { false, false, false, false, false };
	bool doexit = false, redraw = true, shoot = false;
	time_point<system_clock> lastShot = system_clock::now();

	initAllegro(&timer, &display, &(player.img), &event_queue);

	Player *p = new Player(x, y, center_x, center_y, "resources/arrow.png");
	Bullet *bullet = new Bullet(player.center_x, player.center_y, 0, "resources/arrow_green.png");

	vector<Bullet> bulletList;

	al_draw_bitmap(player.img, player.x, player.y, 0);
	al_flip_display();

	al_start_timer(timer);

	while(!doexit) {
		handleEvents(&doexit, &redraw, &shoot, &lastShot, keys, &event_queue, &player, &mouse_x, &mouse_y);

		player.center_x = player.x + PLAYER_SIZE/2;
		player.center_y = player.y + PLAYER_SIZE/2;

		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(200, 200, 200));

			int x_diff = mouse_x - player.center_x;
			int y_diff = mouse_y - player.center_y;
			double angle = PI - atan2(x_diff, y_diff);

			if(shoot) {
				shoot = false;

				bullet->setCenterX(player.center_x);
				bullet->setCenterY(player.center_y);
				bullet->setAngle(angle);

				bulletList.push_back(*bullet);
			}

			al_draw_rotated_bitmap(player.img, PLAYER_SIZE/2, PLAYER_SIZE/2, player.center_x, player.center_y, angle, 0);

			int i = 0;
			vector<int> deletions;
			for(vector<Bullet>::iterator it = bulletList.begin() ; it != bulletList.end() ; ++it) {
				Bullet b = *it;

				if(b.getImg() != NULL && b.getX() <= SCREEN_W && b.getX() + b.getImgWidth()/2 >= 0 && b.getY() <= SCREEN_H && b.getY() + b.getImgHeight()/2 >= 0) {
					b.setCenterX(b.getX() + BULLET_SPEED*b.getDiffX() + b.getImgWidth()/2);
					b.setCenterY(b.getY() + BULLET_SPEED*b.getDiffY() + b.getImgHeight()/2);
					al_draw_rotated_bitmap(b.getImg(), b.getImgWidth()/2, b.getImgHeight()/2, b.getCenterX(), b.getCenterY(), b.getAngle(), 0);
					bulletList.at(i) = b;
				}
				else {
					deletions.push_back(i);
				}

				i ++;
			}

			for(vector<int>::iterator it = deletions.begin() ; it != deletions.end() ; ++it) {
				bulletList.erase(bulletList.begin()+(*it));
			}
			deletions.clear();

			al_flip_display();
		}
	}

	// al_destroy_bitmap(bullet.img);
	// al_destroy_bitmap(bullet->img);
	// delete bullet;
	endAllegro(&timer, &display, &(player.img), &event_queue);

	return 0;
}

void initAllegro(ALLEGRO_TIMER **timer, ALLEGRO_DISPLAY **display, ALLEGRO_BITMAP **img, ALLEGRO_EVENT_QUEUE **event_queue) {
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		exit(-1);
	}

	if(!al_init_image_addon()) {
		fprintf(stderr, "failed to initialize image addon!\n");
		exit(-1);
	}

	if(!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
		exit(-1);
	}

	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		exit(-1);
	}

	*timer = al_create_timer(1.0 / FPS);
	if(!*timer) {
		fprintf(stderr, "failed to create timer!\n");
		exit(-1);
	}

	*display = al_create_display(SCREEN_W, SCREEN_H);
	if(!*display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(*timer);
		exit(-1);
	}
	al_set_window_title(*display, "Potato Tank");

	*img = al_load_bitmap("resources/arrow.png");
	if(!*img) {
		fprintf(stderr, "failed to load player bitmap!\n");
		al_destroy_display(*display);
		al_destroy_timer(*timer);
		exit(-1);
	}

	*event_queue = al_create_event_queue();
	if(!*event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(*img);
		al_destroy_display(*display);
		al_destroy_timer(*timer);
		exit(-1);
	}

	al_register_event_source(*event_queue, al_get_display_event_source(*display));
	al_register_event_source(*event_queue, al_get_timer_event_source(*timer));
	al_register_event_source(*event_queue, al_get_keyboard_event_source());
	al_register_event_source(*event_queue, al_get_mouse_event_source());
}

void endAllegro(ALLEGRO_TIMER **timer, ALLEGRO_DISPLAY **display, ALLEGRO_BITMAP **img, ALLEGRO_EVENT_QUEUE **event_queue) {
	al_destroy_bitmap(*img);
	al_destroy_timer(*timer);
	al_destroy_display(*display);
	al_destroy_event_queue(*event_queue);
}

void handleEvents(bool *doexit, bool *redraw, bool *shoot, time_point<system_clock> *lastShot, bool keys[], ALLEGRO_EVENT_QUEUE **event_queue, PlayerStruct *player, int *mouse_x, int *mouse_y) {
	ALLEGRO_EVENT ev;
	al_wait_for_event(*event_queue, &ev);

	if(ev.type == ALLEGRO_EVENT_TIMER) {
		if(keys[KEY_UP] && player->y >= PLAYER_SPEED) {
			player->y -= PLAYER_SPEED;
			player->center_y = ((int) player->y) + PLAYER_SIZE/2;
		}

		if(keys[KEY_DOWN] && player->y <= SCREEN_H - PLAYER_SIZE - PLAYER_SPEED) {
			player->y += PLAYER_SPEED;
			player->center_y = ((int) player->y) + PLAYER_SIZE/2;
		}

		if(keys[KEY_LEFT] && player->x >= PLAYER_SPEED) {
			player->x -= PLAYER_SPEED;
			player->center_x = ((int) player->x) + PLAYER_SIZE/2;
		}

		if(keys[KEY_RIGHT] && player->x <= SCREEN_W - PLAYER_SIZE - PLAYER_SPEED) {
			player->x += PLAYER_SPEED;
			player->center_x = ((int) player->x) + PLAYER_SIZE/2;
		}

		if(keys[MOUSE_LEFT]) {
			time_point<system_clock> now = system_clock::now();
			duration<double> elapsed = now - *lastShot;
			if(elapsed.count() > 1/FIRE_RATE) {
				*shoot = true;
				*lastShot = now;
			}
			else {
				*shoot = false;
			}
		}
		else {
			*shoot = false;
		}

		*redraw = true;
	}
	else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		*doexit = true;
		return;
	}
	else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
		*mouse_x = ev.mouse.x;
		*mouse_y = ev.mouse.y;
		*redraw = true;
	}
	else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		switch(ev.mouse.button) {
			case 1:
			// *shoot = true;
			// *redraw = true;
			keys[MOUSE_LEFT] = true;
			break;
		}
	}
	else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		switch(ev.mouse.button) {
			case 1:
			// *shoot = true;
			// *redraw = true;
			keys[MOUSE_LEFT] = false;
			break;
		}
	}
	else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch(ev.keyboard.keycode) {
			case ALLEGRO_KEY_Z:
			keys[KEY_UP] = true;
			break;

			case ALLEGRO_KEY_S:
			keys[KEY_DOWN] = true;
			break;

			case ALLEGRO_KEY_Q:
			keys[KEY_LEFT] = true;
			break;

			case ALLEGRO_KEY_D:
			keys[KEY_RIGHT] = true;
			break;
		}
	}
	else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
		switch(ev.keyboard.keycode) {
			case ALLEGRO_KEY_Z:
			keys[KEY_UP] = false;
			break;

			case ALLEGRO_KEY_S:
			keys[KEY_DOWN] = false;
			break;

			case ALLEGRO_KEY_Q:
			keys[KEY_LEFT] = false;
			break;

			case ALLEGRO_KEY_D:
			keys[KEY_RIGHT] = false;
			break;

			case ALLEGRO_KEY_ESCAPE:
			*doexit = true;
			break;
		}
	}
}
