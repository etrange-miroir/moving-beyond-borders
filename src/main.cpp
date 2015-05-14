#include "ofMain.h"
#include "mbb.h"
//#include "ofGLProgrammableRenderer.h"

int main() {
	ofSetLogLevel(OF_LOG_NOTICE);
	ofSetLogLevel("ofThread", OF_LOG_ERROR);
	//ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	ofSetupOpenGL(1920, 1080, OF_WINDOW);
	ofRunApp(new mbb());
}
