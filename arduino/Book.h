#ifndef Book_H
#define Book_H

#include "Arduino.h"

class Book {
	private:
		int _pin[6];
		String _previousState;

	public:
		Book(int pin0, int pin1, int pin2, int pin3, int pin4, int pin5);
		void check();
		String getState();
};

#endif
