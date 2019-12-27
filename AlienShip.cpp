#include "AlienShip.h"
#include"globals.h"
#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_image.h>

//class alienship function definitions/////////////////////////////////
AlienShip::AlienShip() {
	xpos = 0;
	ypos = 0;
	ydir = 0;
	xdir = 0;
	health = 0;
	//image = al_load_bitmap("mothership.png");
}
AlienShip::AlienShip(int x, int y, ALLEGRO_BITMAP *pic){
	xpos = x;
	ypos = y;
	ydir = UP;
	xdir = LEFT;
	health = 100;
	image = pic;
}
AlienShip::~AlienShip() {}
void AlienShip::move() {

	//Vertical movement
	if (rand() % 200 == 0) {
		if (ydir == UP)
			ydir = DOWN;
		else
			ydir = UP;
	}
	if (ydir == DOWN)
		ypos++;
	if (ydir == UP)
		ypos--;
	if (ydir == UP && ypos < 80)
		ydir = DOWN;
	if (ydir == DOWN && ypos > 200)
		ydir = UP;

	//horizontal movement
	if (rand() % 200 == 0) {
		if (xdir == RIGHT)
			xdir = LEFT;
		else
			xdir = RIGHT;
	}
	if (xdir == RIGHT)
		xpos++;
	if (xdir == LEFT)
		xpos--;
	if (xdir == RIGHT && xpos > SCREEN_W - 100)
		xdir = LEFT;
	if (xdir == LEFT && xpos < 100)
		xdir = RIGHT;

}
//void AlienShip::kill() {}
void AlienShip::draw() {
	//al_draw_filled_rectangle(xpos, ypos, xpos + 20, ypos + 20, al_map_rgb(200, 50, 20));
	al_draw_bitmap(image, xpos, ypos, NULL);
}
//bool AlienShip::offScreen() {
//	return false;
//}

int AlienShip::getX() {
	return xpos + 64;
}
int AlienShip::getY() {
	return ypos + 32;
}
void AlienShip::decreaseHealth() {
	health--;
}
int AlienShip::getHealth() {
	return health;
}

