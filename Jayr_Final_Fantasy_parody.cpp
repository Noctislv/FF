#include<iostream>
#include<allegro5\allegro.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_image.h>
using namespace std;

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;
enum MYKEYS { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_ENTER };
enum STATES { INTRO, PLAYING, FIGHTING, MENU, END, RUN };
enum ENEMIES { TRAPS, KNUCKLES, JESUS, BRO };

int main() {
	
	int enemygen = 0;
	int randnum = 0;
	int fight = 1;
	
	//Sprite
	const int maxFrame = 10;
	int curFrame = 0;
	int frameCount = 0;
	int frameDelay = 5;
	int frameWidth = 32;
	int frameHeight = 50;



	//overworld map
	int world[100][100];
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			world[i][j] = 0;


	// the world size
	int worldWidth = 1000;
	int worldHeight = 1000;

	// the camera's position
	int cameraX = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
	int cameraY = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
	int state = INTRO;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *background = NULL;
	ALLEGRO_BITMAP *goomba = NULL;
	ALLEGRO_BITMAP *jayr = NULL;
	ALLEGRO_BITMAP *sprite = NULL;

	float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
	float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
	bool key[5] = { false, false, false, false, false };
	bool redraw = true;
	bool doexit = false;

	ALLEGRO_FONT *font = NULL;
	ALLEGRO_FONT *bigFont = NULL;
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_init_image_addon();

	al_install_keyboard();

	timer = al_create_timer(1.0 / FPS);
	font = al_load_font("first.ttf", 20, NULL);
	if (font == NULL)
		cout << "derp" << endl;
	bigFont = al_load_font("first.ttf", 80, NULL);

	display = al_create_display(SCREEN_W, SCREEN_H);

	//Load images
	sprite = al_load_bitmap("Sprites.png");
	

	traps = al_load_bitmap("traps.jfif");
	jayr = al_load_bitmap("Jayr.jpg");
	ALLEGRO_BITMAP *jesus = al_load_bitmap("Jesus.png");
	ALLEGRO_BITMAP *bro = al_load_bitmap("bro.jfif");
	ALLEGRO_BITMAP *knuckles = al_load_bitmap("knuckles.jpg");

	background = al_load_bitmap("background.jpg");
	al_convert_mask_to_alpha(jayr, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(traps, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(jesus, al_map_rgb(255, 0, 255));
	al_convert_mask_to_alpha(sprite, al_map_rgb(159, 202, 215));
	al_convert_mask_to_alpha(knuckles, al_map_rgb(255, 0, 255));

	al_set_target_bitmap(bouncer);

	al_clear_to_color(al_map_rgb(255, 0, 255));

	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	al_flush_event_queue(event_queue);//clear buffer
									  //game loop
	while (!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		//cout << "case is " << state << endl;

		//state logic
		switch (state) {


			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////intro case//////////////////////////////////////////////
		case INTRO:
			cout << "intro state" << endl;
			if (ev.type == ALLEGRO_EVENT_TIMER) {
				if (key[KEY_ENTER]) {
					state = PLAYING;
				}

				redraw = true;
			}
			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				break;
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
				//cout << "key down" << endl;
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_ENTER:
					//cout << "enter has been pressed" << endl;
					key[KEY_ENTER] = true;
					break;

				}
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
				switch (ev.keyboard.keycode) {

				case ALLEGRO_KEY_ENTER:
					key[KEY_ENTER] = false;
					break;
				case ALLEGRO_KEY_ESCAPE:
					doexit = true;
					break;
				}
			}
			//cout << "flag1" << endl;
			if (redraw && al_is_event_queue_empty(event_queue)) {
				//cout << "intro render" << endl;
				redraw = false;

				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_textf(bigFont, al_map_rgb(150, 150, 150), 10, 80, 0, "Noctis goes to VRChat");
				al_draw_textf(font, al_map_rgb(150, 150, 150), 400, 400, 0, "Press Enter To Begin");

				al_flip_display();
			}
			break;

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			////////////////////playing state/////////////////////////////////////////////////////////////////////////////////////

		case PLAYING:
			cout << "playing state" << endl;
			if (ev.type == ALLEGRO_EVENT_TIMER) {
				if (key[KEY_UP] && bouncer_y >= 4.0) {
					randnum = rand() % 100;
					if (randnum == 1)
						state = FIGHTING;
					cout << "rand is " << randnum << endl;
					bouncer_y -= 4.0;
				}

				if (key[KEY_DOWN] && bouncer_y <= SCREEN_H - BOUNCER_SIZE - 4.0) {
					randnum = rand() % 100;
					if (randnum == 1)
						state = FIGHTING;
					cout << "rand is " << randnum << endl;
					bouncer_y += 4.0;
				}

				if (key[KEY_LEFT] && bouncer_x >= 4.0) {
					randnum = rand() % 100;
					if (randnum == 1)
						state = FIGHTING;
					cout << "rand is " << randnum << endl;
					bouncer_x -= 4.0;
				}

				if (key[KEY_RIGHT] && bouncer_x <= SCREEN_W - BOUNCER_SIZE - 4.0) {
					randnum = rand() % 100;
					if (randnum == 1)
						state = FIGHTING;
					cout << "rand is " << randnum << endl;
					bouncer_x += 4.0;
				}

				// making sure the camera stays within the boundary of the game world
				if (cameraX < 0) cameraX = 0;
				if (cameraY < 0) cameraY = 0;
				if (cameraX > worldWidth - SCREEN_W) cameraX = worldWidth - SCREEN_W;
				if (cameraY > worldHeight - SCREEN_H) cameraY = worldHeight - SCREEN_H;
				redraw = true;

				// make the camera follow the player
				cameraX = bouncer_x - SCREEN_W / 2;
				cameraY = bouncer_y - SCREEN_H / 2;

				if (state == FIGHTING)
					enemygen = rand() % 4;

			}
			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				doexit = true;
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
				case ALLEGRO_KEY_ENTER:
					key[KEY_ENTER] = true;
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

				case ALLEGRO_KEY_ESCAPE:
					doexit = true;
					break;
				}
			}

			if (++frameCount >= frameDelay)
			{
				if (++curFrame >= maxFrame)
					curFrame = 0;


				frameCount = 0;
			}

			x -= 5;

			if (x <= 0 - frameWidth)
				x = width;
		}

		al_draw_bitmap_region(sprite, curFrame*frameWidth, 0, frameWidth, frameHeight, x, y, 0);

			if (redraw && al_is_event_queue_empty(event_queue)) {
				redraw = false;

				al_clear_to_color(al_map_rgb(50, 150, 50));Y;

				for (int i = 0; i < 100; i++)
					for (int j = 0; j < 100; j++)
						al_draw_rectangle((i) * 10 - cameraX, (j) * 10 - cameraY, (i) * 10 + 10 - cameraX, (j) * 10 + 10 - cameraY, al_map_rgb(0, 0, 0), 1);

				//cout << bouncer_x << " , " << bouncer_y << endl;

				al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);

				al_flip_display();
			}
			break;

			////////////////////////////////////////////////////////////fighting state//////////////////////////////////////////////////////////////////////////////


		case FIGHTING:

			cout << "fighting state" << endl;

			if (ev.type == ALLEGRO_EVENT_TIMER) {
				if (key[KEY_RIGHT]) {
					if (fight == 0)
						fight = 1;
					else if (fight == 1)
						fight = 2;
					else if (fight == 2)
						fight = 3;

				}
				if (key[KEY_LEFT]) {
					if (fight == 3)
						fight = 2;
					else if (fight == 2)
						fight = 1;
					else if (fight == 1)
						fight = 0;

				}
				
				/*if (key[KEY_ENTER]) {
					if (fight == RUN) {

						al_draw_textf(font, al_map_rgb(150, 150, 150), 50, 450, 0, "Attempting to run...");
						al_flip_display();
						al_rest(2);
						state = PLAYING;
					}
					if (fight == RUN) {

						//wait one second
						//draw explosion over bad guy
						//play sound effect
						//randomly generate damage and subtract from bad guy HP
						//(add HPS for bad guys and display them)
						//if HP bad guy <=0, state = playing
					}

				}*/

				redraw = true;
			}



			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				break;
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
				//cout << "key down" << endl;
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
				case ALLEGRO_KEY_ENTER:
					key[KEY_ENTER] = true;
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

				case ALLEGRO_KEY_ESCAPE:
					doexit = true;
					break;



				}
			}
			//cout << "flag1" << endl;
			if (redraw && al_is_event_queue_empty(event_queue)) {
				//cout << "intro render" << endl;
				redraw = false;

				al_clear_to_color(al_map_rgb(0, 0, 200));

				//top left window
				al_draw_rectangle(0, 0, 300, 300, al_map_rgb(255, 255, 255), 5);
				//top right window
				al_draw_rectangle(304, 0, SCREEN_W - 3, 300, al_map_rgb(255, 255, 255), 5);
				//menu
				al_draw_rectangle(0, 304, SCREEN_W - 3, SCREEN_H - 3, al_map_rgb(255, 255, 255), 5);

				if (enemygen == TRAPS)
					al_draw_bitmap(traps, 20, 20, NULL);
				else if (enemygen == KNUCKLES)
					al_draw_bitmap(knuckles, 20, 20, NULL);
				else if (enemygen == JESUS)
					al_draw_bitmap(jesus, 20, 20, NULL);
				else if (enemygen == BRO)
					al_draw_bitmap(bro, 20, 20, NULL);


				al_draw_textf(font, al_map_rgb(150, 150, 150), 100, 400, 0, "Run");
				al_draw_textf(font, al_map_rgb(150, 150, 150), 300, 400, 0, "Fight");
				al_draw_textf(font, al_map_rgb(150, 150, 150), 500, 400, 0, "Magic");
				al_draw_bitmap(jayr, 400, 0, NULL);

				//select commands
				if (fight == 0)
					al_draw_textf(bigFont, al_map_rgb(255, 0, 255), 100, 400, 0, "Run");
				else if (fight == 1)
					al_draw_textf(bigFont, al_map_rgb(255, 0, 255), 300, 400, 0, "Fight");
				else if (fight == 2)
					al_draw_textf(bigFont, al_map_rgb(255, 0, 255), 500, 400, 0, "Magic");

				//al_draw_textf(font, al_map_rgb(150, 150, 150), 400, 400, 0, "stats window");

				al_flip_display();
				/*al_rest(2);
				if (fight == 0)
				state = PLAYING;*/

			}
			break;
		case MENU:
			break;
		case END:
			break;
		}




	}

	al_destroy_bitmap(bouncer);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}