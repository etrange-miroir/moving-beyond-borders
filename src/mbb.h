#pragma once

#include "ofMain.h"
#include "ofxOMXPlayer.h"
#include "wiringPi.h"
//#include "ofEvents.h"

class mbb : public ofBaseApp, public ofxOMXPlayerListener {
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
		// arduino stuff
		ofSerial serial;
		void handleArduinoCommand(string cmd);
		bool initOK;
		// shutdown button
		const static int SHUTDOWN_PIN = 7;
		static void shutdown();
		// instance of omxplayer
		ofxOMXPlayer omxPlayer;
		// flag to check if we need to fade out
		bool fadingOut;
		// flag to check if we need to fade in
		bool fadingIn;
		// flag to check if fading is auto
		bool autoFading;
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
		const static bool DEBUG = false;
};

