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
	settings.enableTexture = false;
	omxPlayer.setup(settings);
	// load the first movie
	loadMovie("intro.mp4");
	// assign initial values
	alpha = 255;
	fadingOut = false;
	// arduino stuff
	arduino.connect("/dev/ttyACM0", 57600);
	ofAddListener(arduino.EInitialized, this, &mbb::setupArduino);
	arduinoSetupDone = false;
}

/**
 * Update routine
 */
void mbb::update() {
	unsigned long currentTime = ofGetElapsedTimeMillis();
	if (fadingOut) {
		if (currentTime - lastFadeOutStart > 1000) {
			fadingOut = false;
			loadMovie(nextVideo);
		}
		else {
			alpha = alpha - 1.0;
			alpha = ofClamp(alpha, 0, 255);
		}
	}
	else {
		alpha = alpha + 1.0;
		alpha = ofClamp(alpha, 0, 255);
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

	if (DEBUG) ofLogNotice(__func__) << ofGetFrameRate();
}

/**
 * Load the given movie
 */
void mbb::loadMovie(string movie) {
	ofLogNotice(__func__) << movie;
	string videoPath = "/media/mbb/" + movie;
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
			nextVideo = "intro.mp4";
			break;
		}
		case 'b': {
			fadingOut = true;
			lastFadeOutStart = ofGetElapsedTimeMillis();
			nextVideo = "bbb.mov";
			break;
		}
		case 'c': {
			fadingOut = true;
			lastFadeOutStart = ofGetElapsedTimeMillis();
			nextVideo = "bbb.mp4";
			break;
		}
		case 'p': {
			omxPlayer.togglePause();
			ofLogNotice(__func__) << "pause: " << omxPlayer.isPaused();
			break;
		}
		case 'o': {
			arduino.sendDigital(13, ARD_HIGH);
			break;
		}
		case 'i': {
			arduino.sendDigital(13, ARD_LOW);
			break;
		}
		default: {
			break;
		}
	}
}

/**
 * Arduino setup
 */
void mbb::setupArduino(const int &version) {
	// remove listener because we don't need it anymore
	ofRemoveListener(arduino.EInitialized, this, &mbb::setupArduino);
	arduinoSetupDone = true;
	arduino.sendDigitalPinMode(13, ARD_OUTPUT);
}
