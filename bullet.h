#pragma once
#include"globals.h"
#include<allegro5\allegro.h>
#pragma once
#include"globals.h"
#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_image.h>

class bullet {
private:
	double xpos;
	double ypos;
	bool isAlive; //kills after edge of screen
	double angle;
	double radius;
	ALLEGRO_BITMAP *image;
public:
	bullet();
	bullet(double x, double y, double a);
	bullet(double x, double y, double a, ALLEGRO_BITMAP *pic);
	~bullet();
	void move1();
	void move2();
	void move3();
	void move4();
	void kill();
	void draw(int curFrame);
	bool offScreen();
	bool collide(double x, double y);
};