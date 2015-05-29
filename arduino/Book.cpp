#include "Book.h"

Book::Book(int pin0, int pin1, int pin2, int pin3, int pin4, int pin5) {
	_pin[0] = pin0;
	pinMode(_pin[0], INPUT_PULLUP);
	_pin[1] = pin1;
	pinMode(_pin[1], INPUT_PULLUP);
	_pin[2] = pin2;
	pinMode(_pin[2], INPUT_PULLUP);
	_pin[3] = pin3;
	pinMode(_pin[3], INPUT_PULLUP);
	_pin[4] = pin4;
	pinMode(_pin[4], INPUT_PULLUP);
	_pin[5] = pin5;
	pinMode(_pin[5], INPUT_PULLUP);
	_previousState = "in";
}

void Book::check() {
	String state = getState();
	// state changed, notify the player
	if (state != _previousState) {
		_previousState = state;
		Serial.print(_previousState);
		delay(50);
	}
}

String Book::getState() {
	// intro
	if (!digitalRead(_pin[3]) && !digitalRead(_pin[4]) && !digitalRead(_pin[5])) {
		return "in";
	}
	// page 1
	else if (!digitalRead(_pin[0]) && !digitalRead(_pin[4]) && !digitalRead(_pin[5])) {
		return "p1";
	}
	// page 2
	else if (!digitalRead(_pin[0]) && !digitalRead(_pin[1]) && !digitalRead(_pin[5])) {
		return "p2";
	}
	// outro
	else if (!digitalRead(_pin[0]) && !digitalRead(_pin[1]) && !digitalRead(_pin[2])) {
		return "ou";
	}
	// not all pages are laid
	else {
		return "ko";
	}
}
