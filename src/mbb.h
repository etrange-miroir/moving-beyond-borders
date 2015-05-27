#pragma once

#include "ofMain.h"
#include "ofxOMXPlayer.h"
#include "ofEvents.h"
#include "TerminalListener.h"

class mbb : public ofBaseApp, public ofxOMXPlayerListener, public KeyListener {
	public:
		// openframeworks routines
		void setup();
		void update();
		void draw();
		// load a movie with omxplayer
		void loadMovie(string movie, string language);
		// omxplayer events, not used
		void onVideoEnd(ofxOMXPlayerListenerEventData& e){};
		void onVideoLoop(ofxOMXPlayerListenerEventData& e){};
		// keyboard listener
		void onCharacterReceived(KeyListenerEventData& e);
		TerminalListener consoleListener;
		void keyPressed(int key);
		// arduino stuff
		ofSerial serial;
		void handleArduinoCommand(string cmd);
		//void analogPinChanged(const int & pinNum);
		void updateArduino();
		// instance of omxplayer
		ofxOMXPlayer omxPlayer;
		// flag to check if we need to fade out
		bool fadingOut;
		// alpha transparency while fading in and out
		float alpha;
		// next video to be played
		string nextVideo;
		// current language
		string currentLanguage;
		// fading timing
		unsigned long previousTime;
		// keep track of the last time we started a fade
		unsigned long lastFadeOutStart;
		// debug flag
		const static bool DEBUG = true;
};

