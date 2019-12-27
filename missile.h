#pragma once
#include"globals.h"
#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_image.h>

class missile {
private:
	int xpos;
	int ypos;
	bool alive;
	ALLEGRO_BITMAP *image;
public:
	missile();
	~missile();
	missile(int x, int y, ALLEGRO_BITMAP *pic);
	void move();
	void draw();
	void kill();
	bool offScreen();
	void shoot(int x, int y);
	bool isAlive();
	bool collide(double x, double y);
	int getx();
	int gety();
};
