#pragma once
class stars {
private:
	int xpos;
	int ypos;
	//bool alive;
	int RG;
	int blue;
	int size;
public:
	stars();
	~stars();
	void move();
	void reposition();
	void draw();

};
