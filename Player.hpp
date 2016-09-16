#ifndef DEF_PLAYER
#define DEF_PLAYER

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

using namespace std;

class Player {
private:
	float x, y;
	int center_x, center_y;
	ALLEGRO_BITMAP *img;
	int imgWidth, imgHeight;

public:
	Player(int center_x, int center_y, std::string imgPath);

	void setCenterX(float center_x);
	void setCenterY(float center_y);
	void setImg(string imgPath);

	float getX();
	float getY();
	int getCenterX();
	int getCenterY();
	ALLEGRO_BITMAP *getImg();
	int getImgWidth();
	int getImgHeight();
};

#endif
