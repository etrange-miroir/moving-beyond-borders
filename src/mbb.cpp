#include "mbb.h"

/**
 * Setup routine
 */
void mbb::setup() {
	// some setup conf
	consoleListener.setup(this);
	ofBackground(0, 0, 0);
	ofHideCursor();
	// ofxOMXPlayer conf
	ofxOMXPlayerSettings settings;
	//settings.enableTexture = false;
	omxPlayer.setup(settings);
	// starting language
	currentLanguage = "en";
	// starting video
	nextVideo = "intro";
	// load the first movie
	loadMovie(nextVideo, currentLanguage);
	// assign initial values
	lastFadeOutStart = ofGetElapsedTimeMillis();
	previousTime = ofGetElapsedTimeMillis();
	alpha = 255;
	fadingOut = false;
	// arduino stuff
	serial.setup("/dev/ttyACM0", 9600);
}

/**
 * Update routine
 */
void mbb::update() {
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
	if (fadingOut) {
		if (currentTime - lastFadeOutStart > 1000) {
			fadingOut = false;
			loadMovie(nextVideo, currentLanguage);
		}
		else if (currentTime - previousTime > 30) {
			alpha = alpha - 10.0;
			alpha = ofClamp(alpha, 0, 255);
			previousTime = currentTime;
		}
	}
	else if (currentTime - previousTime > 30) {
		alpha = alpha + 10.0;
		alpha = ofClamp(alpha, 0, 255);
		previousTime = currentTime;
	}
}

/**
 * Draw routine
 */
void mbb::draw() {
	//if (alpha < 255) {
	ofSetColor(255, 255, 255, alpha);
	omxPlayer.setVolume(alpha/(255*2));
	//}
	omxPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());

	//if (DEBUG) ofLogNotice(__func__) << ofGetFrameRate();
	ofDrawBitmapStringHighlight(omxPlayer.getInfo(), 60, 60, ofColor(ofColor::black, 90), ofColor::yellow);
}

/**
 * Load the given movie
 */
void mbb::loadMovie(string movie, string language) {
	ofLogNotice(__func__) << movie << " " <<language;
	string videoPath = "/media/mbb/" + movie + "_" + language + ".mp4";
	omxPlayer.loadMovie(videoPath);
}

/**
 * Handle keyboard events
 */
void mbb::onCharacterReceived(KeyListenerEventData& e) {
	keyPressed((int)e.character);
}

void mbb::keyPressed(int key) {
	ofLogNotice(__func__) << "key: " << key;
	switch (key) {
		case 'a': {
			fadingOut = true;
			lastFadeOutStart = ofGetElapsedTimeMillis();
			nextVideo = "intro";
			break;
		}
		case 'b': {
			fadingOut = true;
			lastFadeOutStart = ofGetElapsedTimeMillis();
			nextVideo = "page1";
			break;
		}
		case 'c': {
			fadingOut = true;
			lastFadeOutStart = ofGetElapsedTimeMillis();
			currentLanguage = "en";
			break;
		}
		case 'd': {
			fadingOut = true;
			lastFadeOutStart = ofGetElapsedTimeMillis();
			currentLanguage = "fr";
			break;
		}
		case 'p': {
			omxPlayer.togglePause();
			ofLogNotice(__func__) << "pause: " << omxPlayer.isPaused();
			break;
		}
		default: {
			break;
		}
	}
}

/**
 * Handle arduino commands
 */
void mbb::handleArduinoCommand(string cmd) {
	if (cmd == "en" || cmd == "fr" || cmd == "es" || cmd == "it" || cmd == "ar") {
		fadingOut = true;
		lastFadeOutStart = ofGetElapsedTimeMillis();
		currentLanguage = cmd;
	}
	else if (cmd == "in") {

	}
	else if (cmd == "p1") {

	}
	else if (cmd == "p2") {

	}
	else if (cmd == "p3") {

	}
	else if (cmd == "ou") {

	}
}
