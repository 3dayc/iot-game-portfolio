/*
 * Box.cpp
 *
 *  Created on: 2019. 2. 18.
 *      Author: java
 */

#ifndef BOX_CPP_
#define BOX_CPP_

class Box {
public:
	int row; //박스 행
	int col; //박스 열.
	int row_r; //표적 행
	int col_r; //표적 열
	int boxTime; //표적 스피드
	int boxLevel; //박스게임 레벨
	int score;

	void reset() {
		row = 3;
		col = 3;
		boxTime = 5000;
		boxLevel = 1;
		score = 0;

		randomSeed(millis());
		new_ran();

		for(int i=0; i<8; i++){
			matrix.setColumn(0,i,0);
			matrix.setColumn(1,i,0);
		}

		draw(true);
		draw_ran(true);
	}

	void lcd_print() {
		LCD_LineClear(0);
		lcd.print("1.Box Game");
	}

	void lcd_print2() {
		LCD_LineClear(1);
		lcd.print(String("Score:") + score
				+ String(" Lv.") + boxLevel);
	}

	void new_ran() {
		do{
			row_r = random(1, 15);
			col_r = random(1, 7);
		}while(((row_r>=row-1)&&(row_r<=row+1))
				&&((col_r>=col-1)&&(col_r<=col+1)));
	}

	void draw(bool onoff) { //(3,3)에 박스 생성
		for(int i=row-1; i<=row+1; i++) {
			for(int j=col-1; j<=col+1; j++) {
				if(i >= 8) {
					if((i==row)&&(j==col))
						matrix.setLed(1,i-8,j,false);
					else
						matrix.setLed(1,i-8,j,onoff);
				} else {
					if((i==row)&&(j==col))
						matrix.setLed(0,i,j,false);
					else
						matrix.setLed(0,i,j,onoff);
				}
			}
		}
	}

	void draw_ran(bool onoff) { //랜덤수로 표적 생성
		if(row_r >= 8)
			matrix.setLed(1, row_r-8, col_r, onoff);
		else
			matrix.setLed(0, row_r, col_r, onoff);
	}

	void set_move() {
		if(joyxy->state != JoystickXY::State::NORMAL){
			draw(false);
			move(joyxy->state);
			draw(true);

			draw_ran(true);
			buz->buz_set(1);
		}
	}

	void move(int dir) {
		switch(dir) {
		case 1:
			if(col<6)
				col++;
			break;
		case 2:
			if(row<14)
				row++;
			break;
		case 3:
			if(col>1)
				col--;
			break;
		case 4:
			if(row>1)
				row--;
			break;
		}
	}

	void speed() {
		if (score/boxLevel == 500) { //점수별 스피드
			boxTime -= 500;
			boxLevel++;
		}
	}

	void eat_box() {
		if(row==row_r && col==col_r) {
			draw_ran(false);
			new_ran();
			draw_ran(true);

			score += 100;
			speed();
			lcd_print2();
			buz->buz_set(2);
		}
	}

	void result() {
//		Serial.println(String("[Box Game] Score = ")+score);
	}

};

#endif /* BOX_CPP_ */



