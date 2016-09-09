#include "functions.h"

#define PI 3.14159265

const float FPS = 60;
const int SCREEN_W = 1100;
const int SCREEN_H = 900;
const int PLAYER_SIZE = 40;
const int PLAYER_SPEED = 2;
const int BULLET_SIZE = 20;
const int BULLET_SPEED = 7;

int main(int argc, char **argv) {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	PlayerStruct player = {.x = SCREEN_W / 2.0 - PLAYER_SIZE / 2.0, .y = SCREEN_H / 2.0 - PLAYER_SIZE / 2.0, .img = NULL};
	player.center_x = ((int) player.x) + PLAYER_SIZE/2;
	player.center_y = ((int) player.y) + PLAYER_SIZE/2;
	int mouse_x = SCREEN_W/2, mouse_y = 0;

	BulletStruct bullet = {0, 0, 0, 0, 0, 0, 0, NULL};

	bool keys[4] = { false, false, false, false };
	bool doexit = false, redraw = true, shoot = false;

	initAllegro(&timer, &display, &(player.img), &event_queue);

	al_draw_bitmap(player.img, player.x, player.y, 0);
	al_flip_display();

	al_start_timer(timer);

	while(!doexit) {
		handleEvents(&doexit, &redraw, &shoot, keys, &event_queue, &player, &mouse_x, &mouse_y);

		player.center_x = player.x + PLAYER_SIZE/2;
		player.center_y = player.y + PLAYER_SIZE/2;

		if(redraw && al_is_event_queue_empty(event_queue)) {
			printf("redraw");
			redraw = false;

			al_clear_to_color(al_map_rgb(50, 200, 50));

			int x_diff = mouse_x - player.center_x;
			int y_diff = mouse_y - player.center_y;
			double angle = PI - atan2(x_diff, y_diff);

			if(shoot) {
				printf("shoot\n");
				shoot = false;
				bullet.img = al_load_bitmap("resources/arrow_red.png");
				bullet.angle = angle;
				bullet.center_x = player.center_x;
				bullet.center_y = player.center_y;
				bullet.x = bullet.center_x - BULLET_SIZE/2;
				bullet.y = bullet.center_y - BULLET_SIZE/2;
			}

			al_draw_rotated_bitmap(player.img, PLAYER_SIZE/2, PLAYER_SIZE/2, player.center_x, player.center_y, angle, 0);

			if(bullet.x <= SCREEN_W && bullet.y <= SCREEN_H && bullet.img != NULL) {
				printf("bullet");
				bullet.x += BULLET_SPEED;
				bullet.y += BULLET_SPEED;
				bullet.center_x = bullet.x + BULLET_SIZE/2;
				bullet.center_y = bullet.y + BULLET_SIZE/2;
				al_draw_rotated_bitmap(bullet.img, BULLET_SIZE/2, BULLET_SIZE/2, bullet.center_x, bullet.center_y, bullet.angle, 0);
			}
			else {
				bullet.img = NULL;
			}

			printf("\n");
			al_flip_display();
		}
	}

	al_destroy_bitmap(bullet.img);
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

void handleEvents(bool *doexit, bool *redraw, bool *shoot, bool keys[], ALLEGRO_EVENT_QUEUE **event_queue, PlayerStruct *player, int *mouse_x, int *mouse_y) {
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
		// printf("clic\n");
		*shoot = true;
		*redraw = true;
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
