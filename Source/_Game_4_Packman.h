/*
 * Packman.h
 *
 *  Created on: 2019. 2. 15.
 *      Author: java
 */

#ifndef PACKMAN_H_
#define PACKMAN_H_

#define MAXX 15 //X축 최댓값
#define MAXY 1  //Y축 최솟값

#define	Pack 	2
#define Skel 	3
#define Point	4

class Packman {

public:
	int packTime = 1500; //팩맨 해골의 스피드
	int packLevel = 1; //레벨 표시
	int xpac; //팩맨X축
	int ypac; //팩맨Y축
	int xfant; //해골X축
	int yfant; //해골Y축
	bool finish; //끝났는지체크
	int score = 0;

	bool points[MAXX + 1][MAXY + 1];

	void reset() {
		packTime = 1500;
		packLevel = 1;
	}

	void initLevel() { //시작할때
		LCD_LineClear(0);
		LCD_LineClear(1);

		for (int i = 0; i <= MAXX; i++) {
			for (int j = 0; j <= MAXY; j++) {
				points[i][j] = true;
				lcd.setCursor(i, j);
				lcd.write(byte(Point));
			}
		}
		randomSeed(millis());
		xpac = random(0, 16); ypac = random(0, 2);
		lcd.setCursor(xpac, ypac);
		lcd.write(byte(Pack));
		points[xpac][ypac] = false;

		xfant = random(0, 16); yfant = random(0, 2);
		lcd.setCursor(xfant, yfant);
		lcd.write(byte(Skel));
		points[xfant][yfant] = false;

		finish = true;
	}

	void skeleton() //상대
	{
		int oldx = xfant;
		int oldy = yfant;

		bool ran = random(0,2);
		if(ran) {
			if (yfant < ypac) yfant++;
			else if (yfant > ypac) yfant--;
			else if (xfant < xpac) xfant++;
			else if (xfant > xpac) xfant--;
		}else{
			if (xfant < xpac) xfant++;
			else if (xfant > xpac) xfant--;
			else if (yfant < ypac) yfant++;
			else if (yfant > ypac) yfant--;
		}


		lcd.setCursor(xfant, yfant);
		lcd.write(byte(Skel));

		lcd.setCursor(oldx, oldy);
		if ((oldx != xfant) || (oldy != yfant)) {
			if (points[oldx][oldy]) {
				lcd.write(byte(Point));
			} else {
				lcd.print(" ");
			}
		}
	}


	void packman(int x, int y) { // 팩맨
		int oldx = xpac;
		int oldy = ypac;
		if (((xpac + x) >= 0) && ((xpac + x) <= MAXX)) {
			xpac = xpac + x;
		}
		if (((ypac + y) >= 0) && ((ypac + y) <= MAXY)) {
			ypac = ypac + y;
		}

		lcd.setCursor(xpac, ypac);
		lcd.write(byte(Pack));

		lcd.setCursor(oldx, oldy);
		if(!(xpac==oldx && ypac==oldy))
			lcd.print(" ");

		if (points[xpac][ypac]) {
			points[xpac][ypac] = false;
			score++;
			buz->buz_set(0);
		}

		finish = false;
		for (int i = 0; i <= MAXX; i++) {
			for (int j = 0; j <= MAXY; j++) {
				if (points[i][j]) {
					finish = true;
				}
			}
		}

		if(finish) {
			timerx->max = 300;
			timerx->flag = true;
		}
	}

	void clear() { //클리어시
		packTime = packTime - 250;
		packLevel++;
		lcd.setCursor(0,0);
		lcd.print(String("----Level ") + packLevel + String("----"));
		lcd.setCursor(0,1);
		lcd.print(String("Score = ") + score + String("        "));
	}

	bool eat_pack() {
		if(xpac==xfant && ypac==yfant)
			return true;
		return false;
	}

	void gameover() {
		LCD_LineClear(0);
		lcd.print("---Game  Over---");
		LCD_LineClear(1);
		lcd.print(String("Score = ") + score);
	}

};

#endif /* PACKMAN_H_ */
