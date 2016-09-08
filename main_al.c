#include <stdio.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define PI 3.14159265

const float FPS = 60;
const int SCREEN_W = 1100;
const int SCREEN_H = 900;
const int PLAYER_SIZE = 40;
const int PLAYER_SPEED = 2;

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int main(int argc, char **argv) {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *player = NULL;
	float player_x = SCREEN_W / 2.0 - PLAYER_SIZE / 2.0;
	float player_y = SCREEN_H / 2.0 - PLAYER_SIZE / 2.0;
	int player_center_x = ((int) player_x) + PLAYER_SIZE/2;
	int player_center_y = ((int) player_y) + PLAYER_SIZE/2;
	int mouse_x = SCREEN_W/2, mouse_y = 0;

	bool key[4] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;

	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if(!al_init_image_addon()) {
		fprintf(stderr, "failed to initialize image addon!\n");
		return -1;
	}

	if(!al_install_mouse()) {
		fprintf(stderr, "failed to initialize the mouse!\n");
		return -1;
	}

	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}
	al_set_window_title(display, "Shoot'em up !");

	player = al_load_bitmap("resources/arrow.png");
	if(!player) {
		fprintf(stderr, "failed to load player bitmap!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_bitmap(player);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	al_draw_bitmap(player, player_x, player_y, 0);
	al_flip_display();

	al_start_timer(timer);

	while(!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER) {
			if(key[KEY_UP] && player_y >= PLAYER_SPEED) {
				player_y -= PLAYER_SPEED;
				player_center_y = ((int) player_y) + PLAYER_SIZE/2;
			}

			if(key[KEY_DOWN] && player_y <= SCREEN_H - PLAYER_SIZE - PLAYER_SPEED) {
				player_y += PLAYER_SPEED;
				player_center_y = ((int) player_y) + PLAYER_SIZE/2;
			}

			if(key[KEY_LEFT] && player_x >= PLAYER_SPEED) {
				player_x -= PLAYER_SPEED;
				player_center_x = ((int) player_x) + PLAYER_SIZE/2;
			}

			if(key[KEY_RIGHT] && player_x <= SCREEN_W - PLAYER_SIZE - PLAYER_SPEED) {
				player_x += PLAYER_SPEED;
				player_center_x = ((int) player_x) + PLAYER_SIZE/2;
			}

			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if(ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
			mouse_x = ev.mouse.x;
			mouse_y = ev.mouse.y;
			redraw = true;
			// printf("%d ; %d - %d ; %d\n", mouse_x, mouse_y, player_center_x, player_center_y);
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_Z:
				key[KEY_UP] = true;
				break;

				case ALLEGRO_KEY_S:
				key[KEY_DOWN] = true;
				break;

				case ALLEGRO_KEY_Q:
				key[KEY_LEFT] = true;
				break;

				case ALLEGRO_KEY_D:
				key[KEY_RIGHT] = true;
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_Z:
				key[KEY_UP] = false;
				break;

				case ALLEGRO_KEY_S:
				key[KEY_DOWN] = false;
				break;

				case ALLEGRO_KEY_Q:
				key[KEY_LEFT] = false;
				break;

				case ALLEGRO_KEY_D:
				key[KEY_RIGHT] = false;
				break;

				case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}

		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(50, 200, 50));

			int x_diff = mouse_x - player_center_x;
			int y_diff = mouse_y - player_center_y;
			double angle = PI - atan2(x_diff, y_diff);

			al_draw_rotated_bitmap(player, PLAYER_SIZE/2, PLAYER_SIZE/2, player_center_x, player_center_y, angle, 0);

			al_flip_display();
		}
	}

	al_destroy_bitmap(player);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}
