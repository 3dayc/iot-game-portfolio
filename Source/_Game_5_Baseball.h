/*
 * BullsAndCows.h
 *
 *  Created on: 2019. 2. 12.
 *      Author: java
 */

#ifndef GAME_5_BASEBALL_H_
#define GAME_5_BASEBALL_H_

class Baseball {
public:
	int ans[4]; // 답
	int num[16]; // 입력 값
	int cnt;
	int s, b;

	void reset() {
		// 4자리 각각 다른 수 랜덤으로 생성.
		randomSeed(millis());
		for(int i=0; i<4; i++){
			ans[i] = random(10);
			for(int j=0; j<i; j++){
				if(ans[i] == ans[j]){
					i--;
					break;
				}
			}
		}

		cnt = 1;
		s = 0;
		b = 0;
	}

	void LCD_print() {
		LCD_LineClear(0);
		lcd.print("5.baseball");
		lcd.setCursor(13,0);
		lcd.print(cnt+String("R"));
	}

	// 답
	void answer() {
		lcd.setCursor(0,0);
		lcd.print("Answer is ");
		for(int i=0; i<4; i++)
			lcd.print(ans[i]);
	}

	bool wrong_input(int count) {
		if(count != 4) {
			LCD_LineClear(1);
			lcd.print("input 4 number");
			return false;
		}else{
			for(int i=0; i<3; i++)
				for(int j=i+1; j<4; j++){
					if(num[i] == num[j]){
						LCD_LineClear(1);
						lcd.print("Duplicate");
						return false;
					}

				}
		return true;
		}
	}

	bool answer_check() {
		s = 0;
		b = 0;

		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++) {
				if(num[i]==ans[j]) {
					if(i==j)
						s++;
					else
						b++;
					break;
				}
			}

		if(s==4) return true;
		return false;
	}

	void ls_print() {
		LCD_LineClear(1);
//		Serial.print(cnt+String("R "));
		for(int i=0; i<4; i++){
			lcd.print(num[i]);
//			Serial.print(num[i]);
		}
		lcd.print(String(" - ")+s+String("S")+b+String("B"));
//		Serial.println(String(" - ")+s+String("S")+b+String("B"));
	}

};

#endif /* GAME_5_BASEBALL_H_ */
