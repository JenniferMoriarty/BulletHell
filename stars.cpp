#include "stars.h"
#include"globals.h"
#include<allegro5\allegro_primitives.h>
stars::stars() {
	xpos = rand() % SCREEN_W;
	ypos = rand() % SCREEN_H;
	RG = rand() % 200;
	
	blue = rand() % 100 + 150;
	size = rand() % 2;
}
stars::~stars() {}
void stars::move() {
	ypos += 10;
}
void stars::reposition() {
	if (ypos > SCREEN_H) {
		ypos = 0;
		xpos = rand() % SCREEN_W;
		RG = rand() % 200;
		blue = rand() % 100 + 150;
		size = rand() % 2;
	}
}
void stars::draw() {
	al_draw_filled_circle(xpos, ypos, size, al_map_rgb(RG,RG, blue));
}