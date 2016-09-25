#include "Map.hpp"

Map::Map(string filename) {
	FILE *mapFile = fopen("resources/main.map", "r");
	char c;
	int line = 0, col = 0;
	while((c = fgetc(mapFile)) != EOF) {
		if(c == '\n') {
			col = 0;
			line ++;
		}
		else {
			charArray[col][line] = c;
			col ++;
		}
	}
	fclose(mapFile);

	grassImg = al_load_bitmap("resources/grassImg.png");
	rockImg = al_load_bitmap("resources/rockImg.png");
}

ALLEGRO_BITMAP *Map::getMapImg() {
	return mapImg;
}

void Map::setMapImg(string imgPath) {
	if(imgPath != "") {
		this->mapImg = al_load_bitmap(imgPath.c_str());
	}
	else {
		this->mapImg = NULL;
	}
}

void Map::displayTerm() {
	int line, col;

	for(line = 0 ; line < 50 ; line ++) {
		for(col = 0 ; col < 70 ; col ++) {
			cout << charArray[col][line];
		}
		cout << endl;
	}
}

void Map::displayArray() {
	int line, col;

	for(line = 0 ; line < 50 ; line ++) {
		for(col = 0 ; col < 70 ; col ++) {
			al_draw_bitmap(getImgFromChar(charArray[col][line]), col*16, line*16, 0);
		}
	}
}

ALLEGRO_BITMAP *Map::getImgFromChar(char c) {
	switch(c) {
		case 'G':
		return grassImg;
		case 'R':
		return rockImg;
	}
	return NULL;
}

ALLEGRO_BITMAP *Map::getImgFromPos(int x, int y) {
	switch(charArray[x][y]) {
		case 'G':
		return grassImg;
		case 'R':
		return rockImg;
	}
	return NULL;
}

void Map::redrawOver(float x, float y, int width, int height, int screenWidth, int screenHeight) {
	int startX = 0, startY = 0, nbX = 0, nbY = 0;

	float size = max(width, height);
	startX = (int) (x/16) - 1;
	startY = (int) (y/16) - 1;
	nbX = (size/16) + 2;
	nbY = (size/16) + 2;
	cout << "(" << startX << ";" << startY << ") " << nbX << "*" << nbY << " (" << size << ")" << endl;
	int col, line;
	for(col = startX ; col <= startX + nbX ; col ++) {
		for(line = startY ; line <= startY + nbY ; line ++) {
			if(col >= 0 && col < screenWidth/16 && line >= 0 && line < screenHeight/16) {
				al_draw_bitmap(getImgFromPos(col, line), col*16, line*16, 0);
			}
		}
	}
}
