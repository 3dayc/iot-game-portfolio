/*
 * Minigame_Devices.h
 *
 *  Created on: 2019. 2. 15.
 *      Author: java
 */

#ifndef MINIGAME_DEVICES_H_
#define MINIGAME_DEVICES_H_

#include "Arduino.h"
#include "Superloop.h"

/*//////////////////////////////////////////////////////////
 *
 * 		LCD
 *
 *//////////////////////////////////////////////////////////
#include <LiquidCrystal_I2C.h>
#define 	LCD0 	0x27
LiquidCrystal_I2C lcd(LCD0, 16, 2); // @suppress("Abstract class cannot be instantiated")

void LCD_INIT();
void LCD_LineClear(int);
void LCD_Menu_1();
void LCD_Menu_2();

byte left[8] = {
		0b00010,
		0b00110,
		0b01110,
		0b11110,
		0b01110,
		0b00110,
		0b00010,
		0b00000
};

byte right[8] = {
		0b10000,
		0b11000,
		0b11100,
		0b11110,
		0b11100,
		0b11000,
		0b10000,
		0b00000
};

byte pack[8] = { //팩맨 모양
		B00000, B00000, B01110, B11011, B11100, B01110, B00000, B00000 };

byte skel[8] = { //해골 모양
		B00000, B00000, B01110, B10101, B11111, B11111, B10101, B00000 };

byte point[8] = { //벽돌 모양
		B00000, B00000, B00000, B01110, B01110, B00000, B00000, B00000 };


void LCD_INIT() {
	lcd.init();
	lcd.backlight();
	lcd.createChar(0,left);
	lcd.createChar(1,right);

	lcd.createChar(2, pack);
	lcd.createChar(3, skel);
	lcd.createChar(4, point);
}

void LCD_LineClear(int line) {
	lcd.setCursor(0,line);
	lcd.print("                ");
	lcd.setCursor(0,line);
}

void LCD_Menu_1() {
	LCD_LineClear(0);
	lcd.print("1.Box 3.PingPong");
	LCD_LineClear(1);
	lcd.print("2.Sequence");

	lcd.setCursor(15,1);
	lcd.write(byte(1));
}

void LCD_Menu_2() {
	LCD_LineClear(0);
	lcd.print("4.Packman6.Snake");
	LCD_LineClear(1);
	lcd.print("5.Baseball");

	lcd.setCursor(15,1);
	lcd.write(byte(0));
}

/*//////////////////////////////////////////////////////////
 *
 * 		REMOTE
 *
 *//////////////////////////////////////////////////////////
#include <IRremote.h>
#define RECV_PIN 	3
IRrecv irrecv(RECV_PIN);
decode_results results;

class RECV : public SuperLoop {
public :
	int num = 0;
	/*
	 * 	ASCII Code
	 * 	# - 35
	 * 	* - 42
	 *
	 * 	0 - 48
	 * 	1 - 49
	 * 	2 - 50
	 * 	...
	 * 	9 - 57
	 *
	 * 	D - 68
	 * 	L - 76
	 * 	O - 79
	 * 	R - 82
	 * 	U - 85
	 * 	X - 88
	 */
	bool flag = false;

	RECV() : SuperLoop(50)	{
		irrecv.enableIRIn();
	}

	void process() {
		if (irrecv.decode(&results)) {
			num = remoteHTI(results.value);
			irrecv.resume();
			if (num != 'X')
				flag = true;
		}
	}

	char remoteHTI(long hex) {
		switch (hex) {
		case 0xFFA25D:
			return '1';
		case 0xFF629D:
			return '2';
		case 0xFFE21D:
			return '3';
		case 0xFF22DD:
			return '4';
		case 0xFF02FD:
			return '5';
		case 0xFFC23D:
			return '6';
		case 0xFFE01F:
			return '7';
		case 0xFFA857:
			return '8';
		case 0xFF906F:
			return '9';
		case 0xFF9867:
			return '0';
		case 0xFF6897:
			return '*';
		case 0xFFB04F:
			return '#';
		case 0xFF38C7:
			return 'O';
		case 0xFF18E7:
			return 'U';
		case 0xFF5AA5:
			return 'R';
		case 0xFF4AB5:
			return 'D';
		case 0xFF10EF:
			return 'L';
		default:
			return 'X';
		}
	}
};

RECV *recv;

/*//////////////////////////////////////////////////////////
 *
 * 		BUZZER
 *
 *//////////////////////////////////////////////////////////
#include "pitches.h"
#include "TonePlayer.h"

#define DO_LOW	NOTE_C3	 // 도
#define DO		NOTE_C4  // 도
#define DOS		NOTE_CS4 // 도#
#define RE		NOTE_D4  // 레
#define RES 	NOTE_DS4 // 레#
#define MI		NOTE_E4  // 미
#define FA		NOTE_F4  // 파
#define FAS 	NOTE_FS4 // 파#
#define SOL		NOTE_G4  // 솔
#define SOLS	NOTE_GS4 // 솔#
#define LA		NOTE_A4  // 라
#define LAS		NOTE_AS4 // 라#
#define SI		NOTE_B4  // 시
#define DO_HIGH	NOTE_C5  // 도

#define BUZ0 9 // pin D9 (Uno), D11 (Mega)
TonePlayer tone0(TCCR1A, TCCR1B, OCR1AH, OCR1AL, TCNT1H, TCNT1L);

class BUZ : public SuperLoop {
public:
	int count;
	int sound_sel;
	int what;
	bool flag;

	BUZ() : SuperLoop(10) {
		count = 0;
		sound_sel = 0;
		what = 0;
		flag = false;
		pinMode(BUZ0, OUTPUT);
	}

	void process() {
		if (flag) {
			switch (sound_sel) {
			case 0:
				sound_effect(DO_HIGH, 10);
				break;
			case 1:
				sound_effect(DO, 10);
				break;
			case 2:
				sound_effect(DO_HIGH, 30);
				break;
			case 3:
				int hz[3] = {DO, MI, SOL};
				int size = sizeof(hz) / sizeof(int);
				sound_effect(hz, size, 30);
				break;
			}
		}
	}

	void buz_set(int sound_sel) {
		flag = true;
		this->sound_sel = sound_sel;
	}

	void sound_effect(int Hz, int how_long) {
		if(count == 0) {
			tone0.tone(Hz);
			count++;
		}else if(count >= how_long) {
			count = 0;
			tone0.noTone();
			sound_sel = 0;
			flag = false;
		}else
			count++;
	}

	void sound_effect(int Hz[], int size, int how_long) {
		if(count == 0){
			tone0.tone(Hz[what]);
			count++;
		}else if(count >= how_long) {
			count = 0;
			tone0.noTone();
			if(size <= what+1) {
				what = 0;
				sound_sel = 0;
				flag = false;
			}else
				what++;
		}else
			count++;
	}
};

BUZ *buz;

/*//////////////////////////////////////////////////////////
 *
 * 		Joystick
 *
 *//////////////////////////////////////////////////////////
#define JOYSTICK_SW 8
#define JOYSTICK_X	A1
#define JOYSTICK_Y	A0

class JoystickXY : public SuperLoop {
public:
	int x, y;
	enum State{
				NORMAL = 0, UP, RIGHT, DOWN, LEFT
	};
	State state;

	bool move_flag = false;
	bool move_able = false;

	JoystickXY() : SuperLoop(50) {
		x = mapping(JOYSTICK_X);
		y = mapping(JOYSTICK_Y);
		state_check();
	}

	void process() {
		int newX = mapping(JOYSTICK_X);
		int newY = mapping(JOYSTICK_Y);

		if ((x != newX) || (y != newY)) {
			x = newX;
			y = newY;
			state_check();
			if (move_able)
				move_flag = true;
		}
	}

	int mapping(int number) {
		return map(analogRead(number), 0, 1023, 0, 3);
	}

	void state_check() {
		if (x == 0)
			state = DOWN;
		else if (x == 2)
			state = UP;
		else if (y == 0)
			state = LEFT;
		else if (y == 2)
			state = RIGHT;
		else
			state = NORMAL;
	}
};

class JoystickSW : public ButtonSuperLoop {
public:
	bool reset = false;
	JoystickSW() : ButtonSuperLoop(JOYSTICK_SW, PULL_UP_INTERNAL) {

	}

	void push() {
		reset = true;
	}

	void up() {

	}
};

JoystickXY *joyxy;
JoystickSW *joysw;

/*//////////////////////////////////////////////////////////
 *
 * 		Dot Matrix
 *
 *//////////////////////////////////////////////////////////
#include <LedControl.h>

#define DIN    12
#define CS     11
#define CLK    10
LedControl matrix(DIN, CLK, CS, 2);

byte minigame[8][8] = { // M I N I G A M E
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x7e, 0x00, 0x7e, 0x00, 0x3c, 0x78, 0x7e, 0x7e},
		{0x04, 0x42, 0x04, 0x42, 0x42, 0x14, 0x04, 0x4a},
		{0x08, 0x7e, 0x18, 0x7e, 0x4a, 0x12, 0x08, 0x4a},
		{0x04, 0x42, 0x20, 0x42, 0x4a, 0x14, 0x04, 0x4a},
		{0x7e, 0x00, 0x7e, 0x00, 0x38, 0x78, 0x7e, 0x4a},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

class DOT : public SuperLoop {
public:
	bool flag = true;
	byte preset[8][8];

	DOT() : SuperLoop(10) {
		for(int i=0; i<2; i++){
			matrix.shutdown(i, false);
			matrix.setIntensity(i, 0);
			matrix.clearDisplay(i);
			for(int j=0; j<8; j++)
				matrix.setRow(i,j,false);
		}
		for(int i=0; i<8; i++)
			for(int j=0; j<8; j++)
				preset[i][j] = minigame[i][j];
	}

	void process() {
		static int count = 0;
		if (flag) {
			if (count > 5) {
				for (int i = 0; i < 8; i++) {
					matrix.setRow(0, i, preset[i][0]);
					matrix.setRow(1, i, preset[i][1]);
				}
				count = 0;
				bitShift();
			} else
				count++;
		}
	}

	void bitShift() {
		byte value1 = preset[0][0];
		byte value2;
		for (int i = 0; i < 8; i++) {
			if (i != 0)
				value2 = preset[0][i];
			for (int j = 1; j < 8; j++) {
				preset[j - 1][i] = preset[j][i];
			}
			if (i != 0)
				preset[7][i - 1] = value2;
		}
		preset[7][7] = value1;
	}
};

DOT *dot;

class TimerX : public SuperLoop {
public:
	bool flag;
	int cnt, max;
	TimerX() : SuperLoop(10) {
		flag = false;
		cnt = max = 0;
	}

	void process() {
		if(flag) {
			if(cnt >= max) {
				cnt = max = 0;
				flag = false;
			}else
				cnt++;
		}
	}
};

TimerX *timerx;

#endif /* MINIGAME_DEVICES_H_ */
