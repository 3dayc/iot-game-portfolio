/*
 * _Minigame.h
 *
 *  Created on: 2019. 2. 15.
 *      Author: java
 */

#ifndef MINIGAME_H_
#define MINIGAME_H_

#include "_Game_1_Box.h"
#include "_Game_2_Push.h"
#include "_Game_3_PingPong.h"
#include "_Game_4_Packman.h"
#include "_Game_5_Baseball.h"
#include "_Game_6_Snake.h"
#include "_Minigame_Devices.h"


Box *box;
Packman *packman;
PingPong *pp;
Push *push;
Snake *snake;
Baseball *baseball;

class MiniGame : public SuperLoop {
public:
	int number;
	bool first;

	MiniGame() : SuperLoop(10) {
		number = 0;
		first = true;

		box = new Box();
		packman = new Packman();
		pp = new PingPong();
		push = new Push();
		baseball = new Baseball();
		snake = new Snake();
	}

	/*//////////////////////////////////////////////////////////
	 *
	 * 		1. box
	 *		2. push
	 * 		3. pingpong
	 *		4. packman
	 *		5. baseball
	 *		6. snake
	 *
	 *//////////////////////////////////////////////////////////

	void process() {
		switch(number) {
		case 0:
			main_menu();
			break;
		case 1:
			game_box();
			break;
		case 2:
			game_push();
			break;
		case 3:
			game_pingpong();
			break;
		case 4:
			game_packman();
			break;
		case 5:
			game_baseball();
			break;
		case 6:
			game_snake();
			break;
		}
	}

	/*//////////////////////////////////////////////////////////
	 *
	 * 		main menu
	 *
	 *//////////////////////////////////////////////////////////
	void main_menu() {
		static bool menu = true;

		if(menu) {
			if(first) {
				LCD_Menu_1();
				first = false;
			}
		}else{
			if(first) {
				LCD_Menu_2();
				first = false;
			}
		}

		if(recv->flag) {
			int num = recv->num;

			if(menu) {
				switch(num){
				case '1':
					number = 1;
					first = true;
					break;
				case '2':
					number = 2;
					first = true;
					break;
				case '3':
					number = 3;
					first = true;
					break;
				case 'R':
					menu = false;
					first = true;
					break;
				}
			}else{
				switch(num){
				case '4':
					number = 4;
					first = true;
					break;
				case '5':
					number = 5;
					first = true;
					break;
				case '6':
					number = 6;
					first = true;
					break;
				case 'L':
					menu = true;
					first = true;
					break;
				}
			}

			buz->buz_set(1);
			recv->flag = false;
		}
	}

	/*//////////////////////////////////////////////////////////
	 *
	 * 		1. box
	 *
	 *//////////////////////////////////////////////////////////
	void game_box() {
		static int count  = 0;

		if (first) {
			first = false;
			dot->flag = false;
			joyxy->move_able = true;

			box->reset();
			box->lcd_print();
			box->lcd_print2();
		}else if(recv->flag){
			int num = recv->num;
			if(num == 'O'){
				first = true;
				number = 0;

				dot->flag = true;
				joyxy->move_able = false;

				box->result();
				buz->buz_set(2);
			}
			recv->flag = false;
		}

		if(joyxy->move_flag) {
			box->set_move();
			joyxy->move_flag = false;
		}else if(joysw->reset){
			box->eat_box();
			count = 0;
			joysw->reset = false;
		}

		if(count >= box->boxTime/10) {
			box->draw_ran(false);
			box->new_ran();
			box->draw_ran(true);

			count = 0;
		}else
			count++;
	}

	/*//////////////////////////////////////////////////////////
	 *
	 * 		2. packman
	 *
	 *//////////////////////////////////////////////////////////
	void game_packman() {
		static bool endgame = false;
		static int count = 0;

		if(first) {
			first = false;
			dot->flag = false;
			joyxy->move_able = true;

			packman->reset();
			packman->initLevel();

		}else if(endgame){
			if(!timerx->flag){
				endgame = false;
				count = 0;
				first = true;
				number = 0;
			}

		}else if(count >= packman->packTime/10){

			packman->skeleton();
			count = 0;
			if(packman->eat_pack()){
				endgame = true;

				packman->gameover();
				dot->flag = true;
				joyxy->move_able = false;

				timerx->max = 300;
				timerx->flag = true;
			}

		}else if(!packman->finish) {
			if(!timerx->flag){
				count = 0;
				packman->finish = true;
				packman->initLevel();
			}

		}else
			count++;

		if(joyxy->move_flag) {
			if(joyxy->state != JoystickXY::State::NORMAL){
				int x = 0;
				int y = 0;
				int state = joyxy->state;
				switch(state){
				case 1: y--; break;
				case 2: x++; break;
				case 3: y++; break;
				case 4: x--; break;
				}
				packman->packman(x, y);
				if(packman->eat_pack())
					endgame = true;
			}
			joyxy->move_flag = false;
		}

	}

//	/*//////////////////////////////////////////////////////////
//	 *
//	 * 		3. pingpong
//	 *
//	 *//////////////////////////////////////////////////////////
	void game_pingpong() {
		static int count = 0;
		static bool endgame = false;

		if(first) {
			first = false;
			dot->flag = false;
			pp->reset();
		}

		if(endgame){
			if(count>=20) {
				if(pp->gameover()) {
					first = true;
					number = 0;
					dot->flag = true;
					endgame = false;
				}
				count = 0;

			}else
				count++;

		}else{
			if(count >= pp->P_speed) {
				count = 0;
				pp->move_pp();
			}else
				count++;

			static int countxy = 0;

			if(countxy > 5) {
				countxy = 0;
				pp->draw_xy_val();
			}else
				countxy++;

			if(pp->check_over())
				endgame = true;
		}

	}

//	/*//////////////////////////////////////////////////////////
//	 *
//	 * 		4. push
//	 *
//	 *//////////////////////////////////////////////////////////
	void game_push() {
		static bool endgame = false;

		if(first) {
			first = false;

			push->reset();
			push->lcd_print();
		}else if(joysw->reset){
			first = true;
			number = 0;

			buz->buz_set(2);
			joysw->reset = false;
		}else if(endgame) {
			if(!timerx->flag) {
				first = true;
				number = 0;

				endgame = false;
			}
		}

		if(recv->flag) {
			int num = recv->num - 48;

			if(num>=0 && num<=9) {
				if(push->push_check(num)){
					buz->buz_set(1);
				}else
					buz->buz_set(0);
			}
			push->lcd_print();
			recv->flag = false;
		}else if(push->count>=10){
			endgame = true;

			push->count = 0;
			push->time = millis() - push->time;
			push->time /= 1000.;
			LCD_LineClear(1);
			lcd.print(String("time = ")+push->time);

//			char num_buff[30];
//			sprintf(num_buff,"[Push Game] time = %d.%d", sec, ms);
//			Serial.println(num_buff);

			timerx->max = 300;
			timerx->flag = true;

			buz->buz_set(3);
		}
	}
//
//	/*//////////////////////////////////////////////////////////
//	 *
//	 * 		5. snake
//	 *
//	 *//////////////////////////////////////////////////////////
	void game_snake() {
		static bool start = true;
		static bool endgame = false;

		if(first) {
			first = false;

			dot->flag = false;
			joyxy->move_able = true;

			for(int i=0; i<8; i++){
				matrix.setRow(0,i,false);
				matrix.setRow(1,i,false);
			}

			snake->lcd_print();

			timerx->max = 100;
			timerx->flag = true;
		}else if(joysw->reset){
			first = true;
			number = 0;

			start = true;

			dot->flag = true;
			joyxy->move_able = false;
			joysw->reset = false;

			buz->buz_set(2);
		}

		if(start){
			static int second321 = 0;
			if(!timerx->flag) {
				for(int i=0; i<8; i++)
					matrix.setRow(0, i, num321[i][second321]);
				if(second321==3) {
					second321 = 0;
					start = false;
					for(int i=0; i<8; i++){
						matrix.setRow(0,i,false);
						matrix.setRow(1,i,false);
					}
					snake->reset();
					snake->mouse_z = true;
				}else{
					second321++;
					timerx->max = 100;
					timerx->flag = true;
				}
			}

		}else if(endgame) {
			if(!timerx->flag) {
				first = true;
				number = 0;
				start = true;
				endgame = false;
				dot->flag = true;
			}

		}else{
			static int count  = 0;

			if(joyxy->move_flag) {
				snake->direction_set();
				joyxy->move_flag = false;
			}

			if(count>=snake->speed) {
				snake->show();
				count = 0;
				if(!snake->range_check() || snake->collision){
					endgame = true;

					timerx->max = 500;
					timerx->flag = true;

					joyxy->move_able = false;
					int score = snake->score;
//					Serial.println(String("[Snake Game] Score = ")+score);
					buz->buz_set(2);
				}
			}else
				count++;

			if(snake->mouse_z){
				snake->lcd_print();
				snake->create();
			}
		}
	}

//	/*//////////////////////////////////////////////////////////
//	 *
//	 * 		6. baseball
//	 *
//	 *//////////////////////////////////////////////////////////
	void game_baseball() {
		static bool flag_round = true;
		static bool CORRECT = false;

		if(first) {
			first = false;

			baseball->reset();
			baseball->LCD_print();
			LCD_LineClear(1);
		}else if(joysw->reset){
			first = true;
			number = 0;

			flag_round = true;
			CORRECT = false;

			joysw->reset = false;
			buz->buz_set(2);
		}else if(flag_round){
			baseball->LCD_print();
			flag_round = false;
		}else if(CORRECT) {
			if(!timerx->flag) {
				CORRECT = false;
				first = true;
				number = 0;
			}

		}

		if(recv->flag) {
			int num = recv->num - 48;
			static int num_count = 0;

			if(num>=0 && num<=9) {
				lcd.setCursor(0,0);
				lcd.print(num_count);
				lcd.setCursor(num_count,1);
				lcd.print(num);
				for(int i=0; i<16-num_count; i++)
					lcd.print(" ");
				baseball->num[num_count] = num;
				num_count++;
				buz->buz_set(1);
			}else if(num == 'O' - 48) {
				if(baseball->wrong_input(num_count)) {
					if(baseball->answer_check()) {
						CORRECT = true;

						timerx->max = 500;
						timerx->flag = true;

						LCD_LineClear(0);
						lcd.print(baseball->cnt+String("R Right Answer"));

						baseball->ls_print();
//						Serial.println(baseball->cnt+String("Round Correct Answer"));

						buz->buz_set(3);
					}else{
						flag_round = true;
						baseball->ls_print();
						baseball->cnt++;
					}
				}else{
					buz->buz_set(2);
				}
				num_count = 0;
			}

			recv->flag = false;
		}
	}
};

MiniGame *mGame;

#endif /* MINIGAME_H_ */
