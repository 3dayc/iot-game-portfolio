/*
 * _Game_PingPong.h
 *
 *  Created on: 2019. 2. 19.
 *      Author: java
 */

#ifndef GAME_3_PINGPONG_H_
#define GAME_3_PINGPONG_H_

#define ROW_MIN 0
#define ROW_MAX	15
#define COL_MIN	0
#define COL_MAX	7

class PingPong {
public:
	int dot_x, dot_y;
	int P_speed;
	int row_pp, col_pp;
	int x_val, y_val;

	void reset() {
		P_speed = 20;
		dot_x = dot_y = 1;
		randomSeed(millis());
		row_pp = random(7, 9);
		col_pp = random(1, 7);

		x_val = y_val = -1;

		for(int i=0; i<8; i++){
			matrix.setColumn(0, i, false);
			matrix.setColumn(1, i, false);
		}

		LCD_LineClear(1);
		LCD_LineClear(0);
		lcd.print("3.PingPong");

		draw_xy_val();
		draw_pp(true);
	}

	void draw_xy_val() {
		int x = map(analogRead(JOYSTICK_X), 0, 1024, 0, 6);
		int y = map(analogRead(A2), 0, 1024, 0, 6);

		if(x != x_val) {
			matrix.setLed(1, ROW_MAX-8, x_val, LOW);
			matrix.setLed(1, ROW_MAX-8, x_val + 1, LOW);
			matrix.setLed(1, ROW_MAX-8, x_val + 2, LOW);
			x_val = x;
			matrix.setLed(1, ROW_MAX-8, x_val, HIGH);
			matrix.setLed(1, ROW_MAX-8, x_val + 1, HIGH);
			matrix.setLed(1, ROW_MAX-8, x_val + 2, HIGH);
		}

		if(y != y_val) {
			matrix.setLed(0, ROW_MIN, y_val, LOW);
			matrix.setLed(0, ROW_MIN, y_val + 1, LOW);
			matrix.setLed(0, ROW_MIN, y_val + 2, LOW);
			y_val = y;
			matrix.setLed(0, ROW_MIN, y_val, HIGH);
			matrix.setLed(0, ROW_MIN, y_val + 1, HIGH);
			matrix.setLed(0, ROW_MIN, y_val + 2, HIGH);
		}
	}

	void draw_pp(bool onoff) {
		if(row_pp>7)
			matrix.setLed(1, row_pp-8, col_pp, onoff);
		else
			matrix.setLed(0, row_pp, col_pp, onoff);
	}



	void move_pp(){
		draw_pp(false);

		if(col_pp== COL_MIN || col_pp==COL_MAX)
			dot_y = -dot_y;

		int x = row_pp + dot_x;
		int y = col_pp;

		if(x==ROW_MIN || x==ROW_MAX)
			if((y==x_val || y==x_val+1 || y==x_val+2 || (y==x_val-1 && dot_y==1)  || (y==x_val+3 && dot_y==-1))
			|| (y==y_val || y==y_val+1 || y==y_val+2 || (y==y_val-1 && dot_y==1) || (y==y_val+3 && dot_y==-1))){
				dot_x = -dot_x;
				buz->buz_set(2);
				if(P_speed>=5)
					P_speed--;
			}

		row_pp += dot_x;
		col_pp += dot_y;

		draw_pp(true);
	}

	bool gameover() {
		static int count = 0;

		if(count == 0) {
			LCD_LineClear(0);
			lcd.print("   Game Over   ");
		}

		for (int i = 0; i <= COL_MAX; i++)
			if(count>7)
				matrix.setLed(1, count-8, i, HIGH);
			else
				matrix.setLed(0, count, i, HIGH);

		if(count >= ROW_MAX){
			count = 0;
			return true;
		}else
			count++;

		return false;
	}

	bool check_over() {
		if(row_pp == ROW_MIN || row_pp == ROW_MAX)
			return true;
		else
			return false;
	}

};



#endif /* GAME_3_PINGPONG_H_ */
