/*

1. �������� : �ڹ� & ���̽��� Ȱ���� IOT ���ø����̼� ������
2. �����Ⱓ : 2018/08/16 ~ 2019/02/20
3. ����� : IOT �ǹ� ������Ʈ
4. �ۼ��� : ������(1��)
5. �ۼ��� : 2019/02/20
6. ���� ; �̴ϰ�����
7. �����ڷ� :
	��. _Game_1_Box.h, Game__2_Push.h, Game_3_PingPong.h, Game_4_Packman.h, Game_5_Baseball.h, Game_6_Snake.h,
	 _main.cpp, _Minigam_Devices.h, _MiniGame.h, pitches.h, Superloop.h, TonePlayer.cpp, TonePlayer.h
	��. PPT ����, �����ڷ�, �����ڷ�(�����׿콺)
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



