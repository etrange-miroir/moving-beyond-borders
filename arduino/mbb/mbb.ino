#include "Lang.h"
#include "Book.h"

Lang en(2, HIGH, "en");
Lang fr(3, HIGH, "fr");
Lang es(4, HIGH, "es");
Lang it(5, HIGH, "it");
Lang ar(6, HIGH, "ar");

const int NUMBER_OF_LANG = 5;
Lang languages[NUMBER_OF_LANG] = { en, fr, es, it, ar };

Book book(7, 8, 9, 10, A2, A0);

void setup() {
	Serial.begin(9600);
}

void loop() {
	// player notifies arduino for readiness, send current page
	if (Serial.available() > 0) {
		char initCmd = Serial.read();
		if (initCmd == '#') {
			String state = book.getState();
			Serial.print(state);
		}
	}
	// continuously check for book changes and lang changes
	for(int i = 0; i < NUMBER_OF_LANG; i++){
		languages[i].check();
	}
	book.check();
}
