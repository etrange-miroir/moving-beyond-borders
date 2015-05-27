#include "Lang.h"

Lang en(2, HIGH, "en");
Lang fr(3, HIGH, "fr");
Lang es(4, HIGH, "es");
Lang it(5, HIGH, "it");
Lang ar(6, HIGH, "ar");

const int NUMBER_OF_LANG = 5;
Lang languages[NUMBER_OF_LANG] = { en, fr, es, it, ar };

void setup() {
	Serial.begin(9600);
}

void loop() {
	for(int i = 0; i < NUMBER_OF_LANG; i++){
		languages[i].check();
	}
}
