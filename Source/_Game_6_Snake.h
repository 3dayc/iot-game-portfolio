/*
 * Snake.h
 *
 *  Created on: 2019. 2. 14.
 *      Author: java
 */

#ifndef GAME_6_SNAKE_H_
#define GAME_6_SNAKE_H_

#define MAX_SNAKE 10

class Snake {
public:
	int snake_x[MAX_SNAKE];
	int snake_y[MAX_SNAKE];
	int snake_z[MAX_SNAKE];
	int direction;

	int mouse_x;
	int mouse_y;
	bool mouse_z = false;

	int score;
	int score_acc = 10;
	int speed;
	int line;
	bool collision;

	void reset() {
		snake_x[0] = 5;
		snake_y[0] = 5;
		snake_z[0] = true;
		for(int i=1; i<MAX_SNAKE; i++){
			snake_x[i] = 0;
			snake_y[i] = 0;
			snake_z[i] = false;
		}

		score = 0;
		speed = 20;
		line = 1;

		collision = false;
		direction = JoystickXY::State::RIGHT;
		matrix.setLed(0,snake_x[0],snake_y[0],true);
		create();
	}

	void show() {
		bool onoff = false;
		for(int a=0; a<2; a++){
			for(int i=0; i<MAX_SNAKE; i++){
				if(snake_z[i]){
					if(snake_x[i] < 8)
						matrix.setLed(0,snake_x[i],snake_y[i],onoff);
					else
						matrix.setLed(1,snake_x[i]-8,snake_y[i],onoff);
				}else
					break;
			}
			onoff = !onoff;
			if(onoff) {
				if(move())
					move();
			}
		}
		if(line>1)
			for(int i=1; i<MAX_SNAKE; i++)
				if(snake_z[i])
					if(snake_x[0]==snake_x[i] && snake_y[0]==snake_y[i])
						collision = true;
	}

	bool move() {
		int x = snake_x[0];
		int y = snake_y[0];

		switch(direction){
		case JoystickXY::State::UP 		:	y++;	break;
		case JoystickXY::State::RIGHT	:	x++;	break;
		case JoystickXY::State::DOWN 	:	y--;	break;
		case JoystickXY::State::LEFT 	:	x--;	break;
		}

		if(!eat_mouse(x, y)){
			for(int i=MAX_SNAKE-1; i>0; i--){
				if(snake_z[i]){
					snake_x[i] = snake_x[i-1];
					snake_y[i] = snake_y[i-1];
				}
			}
			snake_x[0] = x;
			snake_y[0] = y;
			buz->buz_set(1);
			return false;
		}else
			return true;
	}

	void direction_set() {
		if(joyxy->state != JoystickXY::State::NORMAL){
			int i = direction;
			int j = joyxy->state;
			if(line!=1){
				if(!((i-j==2) || (j-i==2)))
					direction = joyxy->state;
			}else
				direction = joyxy->state;
		}
	}

	void create() {
		if(mouse_z){
			bool check;
			do{
				check = false;
				randomSeed(millis());
				mouse_x = random(16);
				mouse_y = random(8);
				for(int i=0; i<MAX_SNAKE; i++){
					if(!snake_z[i])
						break;
					if(mouse_x==snake_x[i] && mouse_y==snake_y[i])
						check = true;
				}
			}while(check);
			mouse_z = false;
			show_mouse();
		}
	}

	bool eat_mouse(int x, int y) {
		if((x==mouse_x && y==mouse_y) && !snake_z[MAX_SNAKE-1]) {
			for(int i=0; i<MAX_SNAKE; i++) {
				if(!snake_z[i]){
					snake_z[i] = true;
					break;
				}
			}

			if(!snake_z[MAX_SNAKE-1]){
				for(int i=MAX_SNAKE-1; i>0; i--){
					if(snake_z[i]){
						snake_x[i] = snake_x[i-1];
						snake_y[i] = snake_y[i-1];
					}
				}
				snake_x[0] = mouse_x;
				snake_y[0] = mouse_y;

				if(line%5==0){
					score_acc += 10;
				}
				if(speed >= 5)
					speed--;
				line++;
			}

			mouse_z = true;
			score += score_acc;

			return true;
		}else
			return false;
	}

	void show_mouse() {
		if(mouse_x < 8)
			matrix.setLed(0, mouse_x, mouse_y, true);
		else
			matrix.setLed(1, mouse_x-8, mouse_y, true);
	}

	bool range_check() {
		if(snake_x[0]<0 || snake_x[0]>15)
			return false;
		if(snake_y[0]<0 || snake_y[0]>7)
			return false;

		return true;
	}

	void lcd_print() {
		LCD_LineClear(0);
		lcd.print(String("6.Snake Line=")+line);
		LCD_LineClear(1);
		lcd.print(String("  Score = ")+score);
	}
};

static byte num321[8][4] = {
		{0B00000000, 0B00000000, 0B00000000, 0B00000000},
		{0B01001001, 0B01111001, 0B00000000, 0B01111111},
		{0B01001001, 0B01001001, 0B00000000, 0B01000001},
		{0B01001001, 0B01001001, 0B01111111, 0B01000001},
		{0B01001001, 0B01001001, 0B01111111, 0B01000001},
		{0B01001001, 0B01001001, 0B00000000, 0B01000001},
		{0B01111111, 0B01001111, 0B00000000, 0B01111111},
		{0B00000000, 0B00000000, 0B00000000, 0B00000000}
};

#endif /* GAME_6_SNAKE_H_ */
