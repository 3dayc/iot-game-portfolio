/*
 * Sequence.h
 *
 *  Created on: 2019. 2. 15.
 *      Author: java
 */

#ifndef Push_H_
#define Push_H_

class Push {
public:
	int ransu[10]; //랜덤 수 10개 생성
	long ranhex[10]; //생성된 10개 랜덤수 16진수 체크
	int count;
	long time;

	void reset() {
		count = 0;
		soo_ran();
		lcd_print();
		time = millis();
	}

	void lcd_print() {
		LCD_LineClear(0);
		lcd.print("2.Sequence");
		LCD_LineClear(1);
		lcd.setCursor(count,1);
		for(int i=count; i<10; i++){
			lcd.print(ransu[i]);
		}
	}

	void soo_ran() { //랜덤수 생성
		randomSeed(millis());
		for (int i = 0; i < 10; i++) {
			ransu[i] = random(0, 10);
			bool tell;
			do {
				tell = false;
				ransu[i] = random(0, 10);
				for (int j = 0; j < i; j++) {
					if (ransu[i] == ransu[j]) {
						tell = true;
						break;
					}
				}
			} while (tell);
		}
	}

	bool push_check(int num) {
		if(ransu[count]==num){
			count++;
			return true;
		}else
			return false;
	}
};

#endif /* Push_H_ */
