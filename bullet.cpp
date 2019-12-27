#include "bullet.h"
#include"globals.h"
#include<allegro5\allegro_primitives.h>
#include<math.h>
#include<allegro5\allegro_image.h>


bullet::bullet() { //default constructor
	xpos = 0;
	ypos = 0;
	isAlive = true;
	angle = 0;
	radius = 0;

}
bullet::bullet(double x, double y, double a, ALLEGRO_BITMAP *pic) {//constructor
	xpos = x;
	ypos = y;
	isAlive = true;
	angle = a;
	radius = 10;
	image = pic;
}
bullet::~bullet() {//destructor

}
bullet::bullet(double x, double y, double a) {
	xpos = x;
	ypos = y;
	isAlive = true;
	angle = a;
	radius = 10;
}

void bullet::move1() {
	angle += .01;
	xpos = xpos + cos(angle)*2;
	ypos++;
}


void bullet::move2() {
	radius = 10;
	angle += .1;
	if (angle > 6.28)
		angle = 0;
	xpos = xpos + cos(angle)*(radius) / 2;
	ypos = ypos + sin(angle)*(radius) / 2 + 1;
}
void bullet::move3() {
	radius = 8;
	angle += .01;
	if (angle > 6)
		angle = 0;
	xpos = xpos + cos(angle)*(radius) / 2;
	ypos = ypos + sin(angle)*(radius) / 2 + .5;

}
void bullet::move4() {
	angle += .1;
	if (angle > 6)
		angle = 0;
	xpos = xpos + cos(angle)*(radius) / 3;
	ypos += 2;
}
void bullet::kill() {
	isAlive = false;
}

void bullet::draw(int curFrame) {
	al_draw_filled_circle(xpos, ypos, 5, al_map_rgb(255, 255, 255));
	//if(curFrame%2==0)
	//al_draw_bitmap_region(image, 32, 0, 32, 32, xpos, ypos, 0);
	//else
	//	al_draw_bitmap_region(image, 0, 0, 32, 32, xpos, ypos, 0);
}

bool bullet::offScreen() {
	if (xpos > (SCREEN_W + 400) || ypos > SCREEN_H || ypos <-400 || xpos <-400)
		return true;
	else
		return false;

}
bool bullet::collide(double x, double y) {
	if (sqrt((x - xpos)*(x - xpos) + (y - ypos)*(y - ypos)) < 15) {

		return true;
	}
	else
		return false;

}
