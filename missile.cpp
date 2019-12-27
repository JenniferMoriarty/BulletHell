#include "missile.h"
#include"globals.h"
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_image.h>
#include<math.h>

//missile functions/////////////////////////////
missile::missile() {
	xpos = 0;
	ypos = 0;
	alive = false;
	//image = al_load_bitmap("missile.png");
}
missile::~missile() {}
missile::missile(int x, int y, ALLEGRO_BITMAP *pic) {
	xpos = x;
	ypos = y;
	alive = false;
	image = pic;

}
void missile::move() {
	ypos -= 5;
}
void missile::draw() {
	//if (image != NULL)
	if(alive)
		al_draw_bitmap(image, xpos, ypos, NULL);
	//else
	//al_draw_filled_circle(xpos, ypos, 3, al_map_rgb(255, 255, 0));
}
void missile::kill() {
	alive = false;
}
bool missile::offScreen() {
	if (ypos < 0)
		return true;
	else
		return false;
}
void missile::shoot(int x, int y) {
	alive = true;
	xpos = x;
	ypos = y;
}

bool missile::isAlive() {
	return alive;
}
bool missile::collide(double x, double y) {
	if (sqrt((x - xpos)*(x - xpos) + (y - ypos)*(y - ypos)) < 32) {

		return true;
	}
	else
		return false;

}
int missile::getx() {
	return xpos;
}
int missile::gety() {
	return ypos;
}
