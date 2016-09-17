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

	mapImg = al_load_bitmap("resources/map.png");

	// grassImg = al_load_bitmap("resources/grassImg.png");
	// rockImg = al_load_bitmap("resources/rockImg.png");
}

ALLEGRO_BITMAP *Map::getMapImg() {
	return mapImg;
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

// void Map::displayAllegro() {
// 	int line, col;
//
// 	for(line = 0 ; line < 50 ; line ++) {
// 		for(col = 0 ; col < 70 ; col ++) {
// 			al_draw_bitmap(getImgFromChar(charArray[col][line]), col*16, line*16, 0);
// 		}
// 	}
// }

// ALLEGRO_BITMAP *Map::getImgFromChar(char c) {
// 	switch(c) {
// 		case 'G':
// 			return grassImg;
// 		case 'R':
// 			return rockImg;
// 	}
// 	return NULL;
// }
