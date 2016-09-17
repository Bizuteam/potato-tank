#include "functions.hpp"

using namespace std;
using namespace std::chrono;

const float FPS = 60;
const int SCREEN_W = 1120;
const int SCREEN_H = 800;
const int PLAYER_SPEED = 2;
const int BULLET_SPEED = 7;
const double FIRE_RATE = 6;

int main(int argc, char **argv) {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	int mouse_x = SCREEN_W/2, mouse_y = 0;

	bool keys[5] = { false, false, false, false, false };
	bool doexit = false, redraw = true, shoot = false;
	time_point<system_clock> lastShot = system_clock::now();

	initAllegro(&timer, &display, &event_queue);

	Player *player = new Player(SCREEN_W / 2, SCREEN_H / 2, "resources/potato-30x20.png");
	Bullet *bullet = new Bullet(player->getCenterX(), player->getCenterY(), 0, "resources/bullet-15x5.png");
	vector<Bullet> bulletList;

	Map *map = new Map("resources/main.map");
	// map->displayTerm();

	al_draw_bitmap(player->getImg(), player->getX(), player->getY(), 0);
	al_flip_display();

	al_start_timer(timer);

	while(!doexit) {
		handleEvents(&doexit, &redraw, &shoot, &lastShot, keys, &event_queue, player, &mouse_x, &mouse_y);

		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			// map->displayAllegro();
			al_draw_bitmap(map->getMapImg(), 0, 0, 0);
			// al_clear_to_color(al_map_rgb(200, 200, 200));

			int x_diff = mouse_x - player->getCenterX();
			int y_diff = mouse_y - player->getCenterY();
			double angle = PI - atan2(x_diff, y_diff);

			if(shoot) {
				shoot = false;

				bullet->setCenterX(player->getCenterX());
				bullet->setCenterY(player->getCenterY());
				bullet->setAngle(angle);

				bulletList.push_back(*bullet);
			}

			int i = 0;
			vector<int> deletions;
			for(vector<Bullet>::iterator it = bulletList.begin() ; it != bulletList.end() ; ++it) {
				Bullet b = *it;

				if(b.getImg() != NULL && b.getX() <= SCREEN_W && b.getX() + b.getImgWidth()/2 >= 0 && b.getY() <= SCREEN_H && b.getY() + b.getImgHeight()/2 >= 0) {
					b.setCenterX(b.getCenterX() + BULLET_SPEED*b.getDiffX());
					b.setCenterY(b.getCenterY() + BULLET_SPEED*b.getDiffY());
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

			al_draw_rotated_bitmap(player->getImg(), player->getImgWidth()/2, player->getImgHeight()/2, player->getCenterX(), player->getCenterY(), angle, 0);

			al_flip_display();
		}
	}

	endAllegro(&timer, &display, &event_queue);

	return 0;
}

void initAllegro(ALLEGRO_TIMER **timer, ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue) {
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

	*event_queue = al_create_event_queue();
	if(!*event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(*display);
		al_destroy_timer(*timer);
		exit(-1);
	}

	al_register_event_source(*event_queue, al_get_display_event_source(*display));
	al_register_event_source(*event_queue, al_get_timer_event_source(*timer));
	al_register_event_source(*event_queue, al_get_keyboard_event_source());
	al_register_event_source(*event_queue, al_get_mouse_event_source());
}

void endAllegro(ALLEGRO_TIMER **timer, ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue) {
	al_destroy_timer(*timer);
	al_destroy_display(*display);
	al_destroy_event_queue(*event_queue);
}

void handleEvents(bool *doexit, bool *redraw, bool *shoot, time_point<system_clock> *lastShot, bool keys[], ALLEGRO_EVENT_QUEUE **event_queue, Player *player, int *mouse_x, int *mouse_y) {
	ALLEGRO_EVENT ev;
	al_wait_for_event(*event_queue, &ev);

	if(ev.type == ALLEGRO_EVENT_TIMER) {
		if(keys[KEY_UP] && player->getY() >= PLAYER_SPEED) {
			player->setCenterY(player->getCenterY() - PLAYER_SPEED);
		}

		if(keys[KEY_DOWN] && player->getY() <= SCREEN_H - player->getImgHeight() - PLAYER_SPEED) {
			player->setCenterY(player->getCenterY() + PLAYER_SPEED);
		}

		if(keys[KEY_LEFT] && player->getX() >= PLAYER_SPEED) {
			player->setCenterX(player->getCenterX() - PLAYER_SPEED);
		}

		if(keys[KEY_RIGHT] && player->getX() <= SCREEN_W - player->getImgWidth() - PLAYER_SPEED) {
			player->setCenterX(player->getCenterX() + PLAYER_SPEED);
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
			// Left button
			keys[MOUSE_LEFT] = true;
			break;
		}
	}
	else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		switch(ev.mouse.button) {
			case 1:
			// Left button
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
