#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#include "ofxMSAControlFreak/src/gui/Gui.h"
#include "ofxMSAControlFreak/src/ControlFreak.h"


class testApp : public ofSimpleApp{
	
public:
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
};

#endif

