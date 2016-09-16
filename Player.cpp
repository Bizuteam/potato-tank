#include "Player.hpp"

Player::Player(int center_x, int center_y, std::string imgPath) {
	this->center_x = center_x;
	this->center_y = center_y;
	if(imgPath != "") {
		this->img = al_load_bitmap(imgPath.c_str());
		this->imgWidth = al_get_bitmap_width(this->img);
		this->imgHeight = al_get_bitmap_height(this->img);
	}
	else {
		this->img = NULL;
		this->imgWidth = 0;
		this->imgHeight = 0;
	}
	this->x = center_x - (this->imgWidth / 2);
	this->y = center_y - (this->imgHeight / 2);
}

void Player::setCenterX(float center_x) {
	this->center_x = center_x;
	this->x = center_x - (this->imgWidth / 2);
}

void Player::setCenterY(float center_y) {
	this->center_y = center_y;
	this->y = center_y - (this->imgHeight / 2);
}

void Player::setImg(string imgPath) {
	if(imgPath != "") {
		this->img = al_load_bitmap(imgPath.c_str());
		this->imgWidth = al_get_bitmap_width(this->img);
		this->imgHeight = al_get_bitmap_height(this->img);
	}
	else {
		this->img = NULL;
		this->imgWidth = 0;
		this->imgHeight = 0;
	}
}

float Player::getX() {
	return x;
}

float Player::getY() {
	return y;
}

int Player::getCenterX() {
	return center_x;
}

int Player::getCenterY() {
	return center_y;
}

ALLEGRO_BITMAP *Player::getImg() {
	return img;
}

int Player::getImgWidth() {
	return imgWidth;
}

int Player::getImgHeight() {
	return imgHeight;
}
