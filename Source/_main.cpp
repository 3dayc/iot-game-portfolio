/*

1. 교육과정 : 자바 & 파이썬을 활용한 IOT 애플리케이션 개발자
2. 교육기간 : 2018/08/16 ~ 2019/02/20
3. 과목명 : IOT 실무 프로젝트
4. 작성자 : 주지훈(1조)
5. 작성일 : 2019/02/20
6. 주제 ; 미니게임팩
7. 제출자료 :
	ㄱ. _Game_1_Box.h, Game__2_Push.h, Game_3_PingPong.h, Game_4_Packman.h, Game_5_Baseball.h, Game_6_Snake.h,
	 _main.cpp, _Minigam_Devices.h, _MiniGame.h, pitches.h, Superloop.h, TonePlayer.cpp, TonePlayer.h
	ㄴ. PPT 파일, 영상자료, 사진자료(프로테우스)
 */

#include <Arduino.h>

#include "_Minigame_Devices.h"
#include "_MiniGame.h"

void setup() {
	Serial.begin(115200);

	LCD_INIT();

	recv 	= new RECV();
	buz  	= new BUZ();
	joyxy 	= new JoystickXY();
	joysw 	= new JoystickSW();
	dot 	= new DOT();

	mGame  = new MiniGame();
	timerx = new TimerX();
}

void loop() {

	recv->loop();
	buz->loop();
	joyxy->loop();
	joysw->loop();
	dot->loop();

	mGame->loop();
	timerx->loop();

}



