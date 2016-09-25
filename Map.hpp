#ifndef DEF_MAP
#define DEF_MAP

#include <iostream>
#include <allegro5/allegro.h>

using namespace std;

class Map {
private:
	char charArray[70][50];
	ALLEGRO_BITMAP *mapImg;

	ALLEGRO_BITMAP *grassImg, *rockImg;
	ALLEGRO_BITMAP *getImgFromChar(char c);

public:
	Map(string filename);
	ALLEGRO_BITMAP *getMapImg();
	void setMapImg(string imgPath);
	void displayArray();
	void displayTerm();
	void redrawOver(float x, float y, int width, int height, int screenWidth, int screenHeight);
	ALLEGRO_BITMAP *getImgFromPos(int x, int y);
};

#endif
