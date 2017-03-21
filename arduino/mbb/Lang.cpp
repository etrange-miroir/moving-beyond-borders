#include "Lang.h"

Lang::Lang(int pin, int previousState, String code) : _pin(pin), _previousState(previousState), _code(code) {
	pinMode(pin, INPUT_PULLUP);
}

void Lang::check() {
	int currentState = digitalRead(_pin);
	if (currentState == LOW && _previousState == HIGH) {
		Serial.print(_code);
	}
	_previousState = currentState;
	delay(20);
}
