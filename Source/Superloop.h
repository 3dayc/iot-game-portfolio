/*
 * Superloop.h
 *
 *  Created on: 2019. 1. 17.
 *      Author: java
 */

#ifndef SUPERLOOP_H_
#define SUPERLOOP_H_

#include "Arduino.h"

/*
 * 	SuperLoop
 */
class SuperLoop{
public:
	unsigned long previousMillis;
	unsigned long interval;

	SuperLoop(unsigned long interval) {
			this->interval = interval;
			previousMillis = millis();
	}

	virtual void loop() {
		unsigned long currentMillis = millis();
		if (currentMillis-previousMillis>interval) {
			previousMillis = currentMillis;
			process();
		}
	}

	virtual void process() = 0; // 순수 가상(추상) 함수
	virtual ~SuperLoop(){

	}
};

/*
 * 	ButtonSuperLoop
 */
#define PULL_DOWN		 1
#define PULL_UP			 2
#define PULL_UP_INTERNAL 3

class ButtonSuperLoop : public SuperLoop{
public:
	int lastButtonState;
	int buttonState;
	int buttonNum;
	int buttonType;
	int button = 0;

	ButtonSuperLoop(int buttonNum, int buttonType) : SuperLoop(50){
		this->buttonNum = buttonNum;
		this->buttonType = buttonType;

		switch(buttonType){
		case PULL_DOWN :
			lastButtonState = LOW;
			buttonState = LOW;
			pinMode(buttonNum, INPUT);
			break;
		case PULL_UP :
			lastButtonState = HIGH;
			buttonState = HIGH;
			pinMode(buttonNum, INPUT);
			break;
		case PULL_UP_INTERNAL :
			lastButtonState = HIGH;
			buttonState = HIGH;
			pinMode(buttonNum, INPUT_PULLUP);
			break;
		}
	}

	void loop() {
		button = digitalRead(buttonNum);
		unsigned long currentMillis = millis();

		if(button != lastButtonState){
			previousMillis = currentMillis;
		}else
			SuperLoop::loop();

		lastButtonState = button;
	}

	void process() {
		if(button != buttonState){
			buttonState = button;

			if(buttonType==1)
				buttonState==HIGH ? push() : up();
			else
				buttonState==HIGH ? up() : push();
		}
	}

	virtual void push() = 0;
	virtual void up() = 0;

	virtual ~ButtonSuperLoop(){
	}
};



#endif /* SUPERLOOP_H_ */
