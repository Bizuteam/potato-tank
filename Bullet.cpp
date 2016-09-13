#include "Bullet.hpp"

Bullet::Bullet(float center_x, float center_y, double angle, string imgPath) {
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
	this->angle = angle;
	this->diff_x = sin(angle);
	this->diff_y = - cos(angle);
}

void Bullet::setCenterX(float center_x) {
	this->center_x = center_x;
	this->x = center_x - (this->imgWidth / 2);
}

void Bullet::setCenterY(float center_y) {
	this->center_y = center_y;
	this->y = center_y - (this->imgHeight / 2);
}

void Bullet::setAngle(double angle) {
	this->angle = angle;
	this->diff_x = sin(angle);
	this->diff_y = - cos(angle);
}

void Bullet::setImg(string imgPath) {
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

float Bullet::getX() {
	return x;
}

float Bullet::getY() {
	return y;
}

int Bullet::getCenterX() {
	return center_x;
}

int Bullet::getCenterY() {
	return center_y;
}

float Bullet::getDiffX() {
	return diff_x;
}

float Bullet::getDiffY() {
	return diff_y;
}

double Bullet::getAngle() {
	return angle;
}

ALLEGRO_BITMAP *Bullet::getImg() {
	return img;
}

int Bullet::getImgWidth() {
	return imgWidth;
}

int Bullet::getImgHeight() {
	return imgHeight;
}
