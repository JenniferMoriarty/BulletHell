#pragma once
#include"globals.h"
#include<allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_image.h>


class AlienShip {
private:
	int xpos;
	int ypos;
	int xdir;
	int ydir;
	int health;
	ALLEGRO_BITMAP *image;
public:
	AlienShip();
	AlienShip(int x, int y, ALLEGRO_BITMAP *pic);
	~AlienShip();
	void move();
	void draw();
	void decreaseHealth();
	int getX();
	int getY();
	int getHealth();
};