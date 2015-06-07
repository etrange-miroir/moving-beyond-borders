#include "mbb.h"

/**
 * Setup routine
 */
void mbb::setup() {
	// some setup conf
	ofBackground(0, 0, 0);
	ofHideCursor();
	// ofxOMXPlayer conf
	ofxOMXPlayerSettings settings;
	//settings.enableTexture = false;
	omxPlayer.setup(settings);
	// starting language
	currentLanguage = "fr";
	// assign initial values
	lastFadeOutStart = ofGetElapsedTimeMillis();
	previousTime = ofGetElapsedTimeMillis();
	alpha = 255;
	fadingOut = false;
	// arduino stuff
	serial.setup("/dev/ttyACM0", 9600);
	initOK = false;
	// gpio stuff for shutdown button
	if(wiringPiSetup() == -1){
		ofLogNotice(__func__) << "Error on wiringPi setup";
	}
	pinMode(SHUTDOWN_PIN, INPUT);
	pullUpDnControl(SHUTDOWN_PIN, PUD_UP);
	wiringPiISR(SHUTDOWN_PIN, INT_EDGE_FALLING, &mbb::shutdown);
}

/**
 * Update routine
 */
void mbb::update() {
	// connection with arduino is OK, the app can work
	if (initOK) {
		// check for incoming data from arduino
		char first = serial.readByte();
		char second = serial.readByte();
		if (first != OF_SERIAL_NO_DATA && first != OF_SERIAL_ERROR
			&& second != OF_SERIAL_NO_DATA && second != OF_SERIAL_ERROR) {
			string cmd = string(1, first) + string(1, second);
			handleArduinoCommand(cmd);
		}
		// fade if needed
		unsigned long currentTime = ofGetElapsedTimeMillis();
		if (fadingOut && currentTime - previousTime > 30) {
			alpha = alpha - 10.0;
			alpha = ofClamp(alpha, 0, 255);
			previousTime = currentTime;
		}
		else if (currentTime - previousTime > 30) {
			alpha = alpha + 10.0;
			alpha = ofClamp(alpha, 0, 255);
			previousTime = currentTime;
		}
		// if auto mode (change language) or fading in (pages) is needed
		if ((autoFading && currentTime - lastFadeOutStart > 1000)
			|| fadingIn) {
			fadingOut = false;
			fadingIn = false;
			autoFading = false;
			if (nextVideo == "introLoop") {
				loadMovie(nextVideo, "");
			}
			else {
				loadMovie(nextVideo, currentLanguage);
			}
		}
		// check if video is ending
		if (nextVideo == "outro") {
			checkForEnd();
		}
	}
	// wait for the connection with arduino to be up and notify it
	// in order to get the current state of pages
	else if (serial.isInitialized() && !initOK) {
		initOK = true;
		char init = '#';
		serial.writeByte(init);
	}
}

/**
 * Draw routine
 */
void mbb::draw() {
	ofSetColor(255, 255, 255, alpha);
	omxPlayer.setVolume(alpha/(255*2));
	omxPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());

	if (DEBUG) {
		ofDrawBitmapStringHighlight(omxPlayer.getInfo(), 60, 60, ofColor(ofColor::black, 90), ofColor::yellow);
	}
}

/**
 * Load the given movie
 */
void mbb::loadMovie(string movie, string language) {
	string videoPath = "/media/mbb/" + movie;
	if (language == "") {
		videoPath += ".mp4";
	}
	else {
		videoPath += "_" + language + ".mp4";
	}
	ofLogNotice(__func__) << videoPath;
	omxPlayer.loadMovie(videoPath);
}

/**
 * Callback when a video ends
 */
void mbb::checkForEnd() {
	if (omxPlayer.getCurrentFrame() >= omxPlayer.getTotalNumFrames()) {
		nextVideo = "outroLoop";
		loadMovie("outroLoop", "");
	}
}

/**
 * Handle arduino commands
 */
void mbb::handleArduinoCommand(string cmd) {
	if (cmd == "en" || cmd == "fr" || cmd == "es" || cmd == "it" || cmd == "ar") {
		ofLogNotice(__func__) << cmd;
		currentLanguage = cmd;
		if(nextVideo == "introLoop" || nextVideo == "intro") {
			nextVideo = "intro";
			loadMovie("intro", currentLanguage);
		}
		// virer le loadMovie de dessus + le else (garder le if)
		// pour un fade entre introLoop et intro
		else if (nextVideo != "outroLoop") {
			fadingOut = true;
			fadingIn = false;
			autoFading = true;
			lastFadeOutStart = ofGetElapsedTimeMillis();
		}
	}
	// not all pages are down, fade out then
	else if (cmd == "ko") {
		ofLogNotice(__func__) << cmd;
		fadingOut = true;
		fadingIn = false;
		autoFading = false;
	}
	// intro
	else if (cmd == "in") {
		ofLogNotice(__func__) << cmd;
		fadingOut = false;
		fadingIn = true;
		autoFading = false;
		nextVideo = "introLoop";
	}
	// page 1
	else if (cmd == "p1") {
		ofLogNotice(__func__) << cmd;
		fadingOut = false;
		fadingIn = true;
		autoFading = false;
		nextVideo = "page1";
	}
	// page 2
	else if (cmd == "p2") {
		ofLogNotice(__func__) << cmd;
		fadingOut = false;
		fadingIn = true;
		autoFading = false;
		nextVideo = "page2";
	}
	// outro
	else if (cmd == "ou") {
		ofLogNotice(__func__) << cmd;
		fadingOut = false;
		fadingIn = true;
		autoFading = false;
		nextVideo = "outro";
	}
}

/**
 * Shutdown function
 */
void mbb::shutdown() {
	ofLogNotice(__func__) << "shutdown";
	system("shutdown -h now");
	ofExit();
}
