#include <allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_image.h>
#include<allegro5/allegro_font.h>
#include<allegro5\allegro_ttf.h>
#include<vector>
#include<iostream>
#include"stars.h"
#include"missile.h"
#include"bullet.h"
#include"AlienShip.h"
#include"globals.h"

using namespace std;
enum states{INTRO, PLAYING, LOST, WON};

int main()
{
	srand(time(NULL));
	//set up allegro
	al_init();
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	//set up game screen, event queue, and timer
	ALLEGRO_DISPLAY *display = al_create_display(SCREEN_W, SCREEN_H);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_FONT *font = al_load_font("raidercrusader.ttf", 20, NULL);
	ALLEGRO_FONT *font2 = al_load_font("raidercrusader.ttf", 40, NULL);
	ALLEGRO_BITMAP *image = al_load_bitmap("ship.png");
	ALLEGRO_BITMAP *mothershipPic = al_load_bitmap("mothership.png");
	ALLEGRO_BITMAP *missilePic = al_load_bitmap("missile.png");
	ALLEGRO_BITMAP *explosion = al_load_bitmap("explosion.png");
	ALLEGRO_BITMAP *bulletPic = al_load_bitmap("bullet.png");
	al_start_timer(timer);
	//position of player
	double xPos = 400;
	double yPos = 700;
	//game variables
	bool key[5] = { false, false, false, false, false }; //holds key clicks
	bool redraw = true; //variable needed for render section
	bool doexit = false; //handles game loop
	int counter = 0; //slow down object creation
	int num = 0; //to keep track of # of bullets (debugging purposes only)
	int moveTimer = 0;
	int playerHealth = 100;
	double minBullets = 60;
	int justShot = 0;
	int HumanHit = 0;
		
	int AlienHit = 0;
	int hitX = 0;
	int hitY = 0;

	int state = INTRO;

	//sprite timers for explosions
	int maxFrame = 5;
	int curFrame = 0;
	int frameCount = 0;
	int frameDelay = 5;
	int frameWidth = 64;
	int frameHeight = 64;
	//sprite timers for ships
	int maxFrame2 = 5;
	int curFrame2 = 0;
	int frameCount2 = 0;
	int frameDelay2 = 5;
	int frameWidth2 = 32;
	int frameHeight2 = 32;
	

	//tell event queue what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	//starfield vector
	vector<stars *> starfield;
	vector<stars *>::iterator iter3;
	for (int i = 0; i < 200; i++) {
		stars *newStar = new stars();
		starfield.push_back(newStar);
	}
	//vector to hold bullets
	vector<bullet *> bullets;
	vector<bullet *>::iterator iter;

	//vector to hold missiles
	vector<missile *> missiles;
	vector<missile *>::iterator iter2;
	for (int i = 0; i < 5; i++) {
		missile *newMissile = new missile(0,0, missilePic);
		missiles.push_back(newMissile);
	}
	
	//create alien mothership
	AlienShip mothership(SCREEN_W/2, 100, mothershipPic);
	


	while (!doexit )//game loop!
	{

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//timer (physics) section////////////////////////////////////////
		if (ev.type == ALLEGRO_EVENT_TIMER) {

			if (state == INTRO) {
				if (key[KEY_SPACE]) {
					if (state == INTRO)
						state = PLAYING;
				}
			}

			if (state == PLAYING && playerHealth < 0)
				state = LOST;

			if (state == PLAYING && mothership.getHealth()<0)
				state = WON;

			if (state == PLAYING) {

			
				justShot++;
				
				//sprite timing
				if (++frameCount >= frameDelay)
				{
					if (++curFrame >= maxFrame)
						curFrame = 0;

					frameCount = 0;
				}
				if (++frameCount2 >= frameDelay2)
				{
					if (++curFrame2 >= maxFrame2)
						curFrame2 = 0;

					frameCount2 = 0;
				}


				//move the starfield
				for (iter3 = starfield.begin(); iter3 != starfield.end(); iter3++) {
					(*iter3)->reposition();
					(*iter3)->move();
				}

				counter++; //variable to slow down object creation. Initalize it to 0 above your game loop. 
				minBullets -= .001; //variable initialized to 60. Subtracting here speeds up object creation over time!
				if (counter > minBullets) {
					//create new bullets, push into vector

					bullet *newbullet = new bullet(mothership.getX(), mothership.getY(), 0);
					bullets.push_back(newbullet);
					bullet *newbullet2 = new bullet(mothership.getX(), mothership.getY(), 3.14);
					bullets.push_back(newbullet2);
					bullet *newbullet3 = new bullet(mothership.getX(), mothership.getY(), 3.14/2);
					bullets.push_back(newbullet3);
					bullet *newbullet4 = new bullet(mothership.getX(), mothership.getY(), 3*3.14/2);
					bullets.push_back(newbullet4);
					//more bullet instantiations will go here!

					counter = 0;
				}


				//move the missiles
				for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
					if ((*iter2)->isAlive())
						(*iter2)->move();
				}
				//cull the missiles
				for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
					if ((*iter2)->offScreen())
						(*iter2)->kill();
				}

				//check missile collision w/Mothership
				for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
					if ((*iter2)->collide(mothership.getX(), mothership.getY())) {
						mothership.decreaseHealth();
						cout << "mothership hit!" << endl;
						AlienHit = 30;
						hitX = (*iter2)->getx();
						hitY = (*iter2)->gety();
					}
				}

				//move the bullets
				moveTimer+=2;
				if (moveTimer > 2400)
					moveTimer = 0;

				for (iter = bullets.begin(); iter != bullets.end(); iter++) {
					if (moveTimer < 600) {
						(*iter)->move1();
						//cout << "move3" << endl;
					}
					else if (moveTimer < 1200) {
						(*iter)->move2();
						//cout << "move2" << endl;
					}
					else if (moveTimer < 1800) {
						(*iter)->move1();
						//cout << "move1" << endl;
					}
					else if (moveTimer < 2400) {
						(*iter)->move4();
						//cout << "move4" << endl;
					}


				}

				//check bullet collision
				for (iter = bullets.begin(); iter != bullets.end(); iter++) {
					if ((*iter)->collide(xPos, yPos)) {
						cout << "BOOM" << endl;
						playerHealth--;
						HumanHit = 30;
					}
				}

				//cull the bullets that are off the screen
				for (iter = bullets.begin(); iter != bullets.end(); iter++) {
					if ((*iter)->offScreen()) {
						(*iter)->~bullet(); //call the DESTRUCTOR (destroys the object, releases memory)
						iter = bullets.erase(iter); //take it out of the vector, too
					}
				}

				//move the mothership
			//	mothership.move();

				//move player 4 pixels in a direction when key is pressed
				if (key[KEY_UP]) {
					yPos -= 4.0;
				}
				if (key[KEY_DOWN]) {
					yPos += 4.0;
				}
				if (key[KEY_LEFT]) {
					xPos -= 4.0;
				}
				if (key[KEY_RIGHT]) {
					xPos += 4.0;
				}
				if (key[KEY_SPACE]) {

					for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
						if (((*iter2)->isAlive()) == false && justShot > 5) {
							(*iter2)->shoot(xPos, yPos);
							justShot = 0;
						}

					}

				}
			}
			redraw = true;
		}
		//keyboard and screen sections//////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = true;
				break;

			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}



		//render section//////////////////////////////////////////////////
		if (redraw && al_is_event_queue_empty(event_queue)) {
			if (state == INTRO) {
				al_draw_text(font2, al_map_rgb(255, 255, 255), 100, SCREEN_H / 2, NULL, "TRIG PATTERN GAME");
				al_draw_text(font, al_map_rgb(255, 255, 255), 100, SCREEN_H / 2+50, NULL, "press space to start.");
			}
			else if (state == PLAYING) {
				redraw = false;
				al_clear_to_color(al_map_rgb(0, 0, 0)); //wipe screen black between drawing(without this things smear)

				//draw starfield
				for (iter3 = starfield.begin(); iter3 != starfield.end(); iter3++) {
					(*iter3)->draw();
				}


				//draw player healthbar
				al_draw_rectangle(20, 20, 120, 40, al_map_rgb(255, 255, 255), 10);
				al_draw_filled_rectangle(20, 20, 20 + playerHealth, 40, al_map_rgb(200, 40, 140));
				al_draw_textf(font, al_map_rgb(255, 255, 255), 20, 50, NULL, "Player Sheilds");


				//draw mothership healthbar
				al_draw_rectangle(400, 20, 500, 40, al_map_rgb(255, 255, 255), 10);
				al_draw_filled_rectangle(400, 20, 400 + mothership.getHealth(), 40, al_map_rgb(200, 200, 40));
				al_draw_textf(font, al_map_rgb(255, 255, 255), 400, 50, NULL, "Enemy Health");


				//draw bullets
				for (iter = bullets.begin(); iter != bullets.end(); iter++) {
					(*iter)->draw(curFrame);
				}

				//draw missiles
				for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
					(*iter2)->draw();
				}
				//draw alienship
				mothership.draw();

				//draw player
				//al_draw_circle(xPos, yPos, 10, al_map_rgb(50, 120, 10), 10); //draw the player
				if (key[KEY_RIGHT])
					al_draw_bitmap_region(image, curFrame2 * frameWidth2 + frameWidth2 * 5, 0, frameWidth2, frameHeight2, xPos, yPos, 0);
				else if (key[KEY_LEFT])
					al_draw_bitmap_region(image, curFrame2 * frameWidth2 + frameWidth2 * 5, 0, frameWidth2, frameHeight2, xPos, yPos, ALLEGRO_FLIP_HORIZONTAL);
				else
					al_draw_bitmap_region(image, curFrame2 * frameWidth2, 0, frameWidth2, frameHeight2, xPos, yPos, 0);


				//draw explosions
				if (AlienHit > 0) {
					al_draw_bitmap_region(explosion, curFrame * frameWidth, 0, frameWidth, frameHeight, hitX, hitY, 0);
					AlienHit--;
				}


				if (HumanHit > 0) {
					al_draw_bitmap_region(explosion, curFrame * frameWidth, 0, frameWidth, frameHeight, xPos - 10, yPos - 10, 0);
					HumanHit--;
				}
			}
			else if (state == WON) {
				al_draw_text(font2, al_map_rgb(255, 255, 255), 100, SCREEN_H / 2, NULL, "You Win!");
				al_draw_text(font, al_map_rgb(255, 255, 255), 100, SCREEN_H / 2 + 50, NULL, "press escape to quit.");
			}

			else if (state == LOST) {
				al_draw_text(font2, al_map_rgb(255, 255, 255), 100, SCREEN_H / 2, NULL, "You Lost!");
				al_draw_text(font, al_map_rgb(255, 255, 255), 100, SCREEN_H / 2 + 50, NULL, "press escape to quit.");

			}
			al_flip_display(); //flip everything from memory to gamescreen
		}//end render

	}//end game loop



	 //clean up memory
	

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;
}

