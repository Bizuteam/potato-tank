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
	void displayAllegro();
	void displayTerm();
};

#endif
