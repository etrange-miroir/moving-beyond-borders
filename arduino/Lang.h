#ifndef Lang_H
#define Lang_H

#include "Arduino.h"

class Lang {
	private:
		int _pin;
		int _previousState;
		String _code;

	public:
		Lang(int pin, int previousState, String code);
		void check();
};

#endif
