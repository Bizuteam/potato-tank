#include "Player.hpp"

Player::Player(int x, int y, int center_x, int center_y, std::string imgPath) {
	this->x = x;
	this->y = y;
	this->center_x = center_x;
	this->center_y = center_y;
	this->img = al_load_bitmap(imgPath.c_str());
}
