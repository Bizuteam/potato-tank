#ifndef DEF_BULLET
#define DEF_BULLET

#include <iostream>
#include <cmath>
#include <allegro5/allegro.h>

using namespace std;

class Bullet {
private:
	float x, y;
	int center_x, center_y;
	double diff_x, diff_y;
	double angle;
	ALLEGRO_BITMAP *img;
	int imgWidth, imgHeight;

public:
	Bullet(int center_x, int center_y, double angle, string imgPath);

	void setCenterX(float center_x);
	void setCenterY(float center_y);
	void setAngle(double angle);
	void setImg(string imgPath);

	float getX();
	float getY();
	int getCenterX();
	int getCenterY();
	float getDiffX();
	float getDiffY();
	double getAngle();
	ALLEGRO_BITMAP *getImg();
	int getImgWidth();
	int getImgHeight();
};

#endif
