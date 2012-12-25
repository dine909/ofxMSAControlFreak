#include  "ofxMSAControlFreak/src/gui/Includes.h"

namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            Panel::Panel(Panel* parent, string name) : Control(parent, name) {
                disableAllEvents();
                width = 0;
                height = ofGetHeight();
                activeControl = NULL;
                setXMLName(name + "_settings.xml");
            }
            
            Panel::~Panel() {
                // delete all controls
            }
            
            
            Panel& Panel::setXMLName(string s) {
                xmlFilename = s;
                return *this;
            }
            
            
            void Panel::loadXml() {
                ofLog(OF_LOG_VERBOSE,  "ofxMSAControlFreak/src/gui/Panel::loadXml: " + xmlFilename);
                
                if(xmlFilename.compare("") == 0) return;
                
                if(XML.loadFile(xmlFilename) == false) {
                    ofLog(OF_LOG_ERROR, "Error loading xmlFilename: " + xmlFilename);
                    return;
                }
                
                XML.pushTag("controls");
                for(int i=0; i < controls.size(); i++) {
                    controls[i]->readFromXml(XML);
                }
                XML.popTag();
            }
            
            
            void Panel::saveXml() {
                if(controls.size() <= 1 || xmlFilename.compare("") == 0) return;	// if it has no controls (title counts as one control)
                
                XML.clear();	// clear cause we are building a new xml file
                
                XML.addTag("controls");
                XML.pushTag("controls");
                for(int i=0; i < controls.size(); i++) {
                    controls[i]->writeToXml(XML);
                }
                XML.popTag();
                
                XML.saveFile(xmlFilename);
                //	if(doSaveBackup)
                ofLog(OF_LOG_VERBOSE,  "ofxMSAControlFreak/src/gui/Panel::saveXml: " + xmlFilename + " " + ofToString(controls.size(), 0) + " items");
            }
            
            
            float Panel::getNextY(float y) {
                return y;
                int iy = (int)ceil(y/config->gridSize.y);
                return (iy) * config->gridSize.y;
            }
            
            
            void Panel::draw(float x, float y, bool alignRight) {
                setPos(x += config->offset.x, y += config->offset.y);
                if(alignRight) x = ofGetWidth() - x -  config->gridSize.x;
                
                float posX		= 0;
                float posY		= 0;
                float stealingX = 0;
                float stealingY = 0;
                
                ofSetRectMode(OF_RECTMODE_CORNER);
                
                for(int i=0; i<controls.size(); i++) {
                    Control& control = *controls[i];
                    
                    if(control.newColumn) {
                        if(alignRight) posX -= config->gridSize.x;
                        else posX += config->gridSize.x;
                        posY = 0;
                    }
                    
                    float controlX = posX + x;
                    float controlY = posY + y;
                    
                    //we don't draw the event stealing controls until the end because they can expand and overlap with other controls (e.g. combo box)
                    if(activeControl == &control) {
                        stealingX = controlX;
                        stealingY = controlY;
                    } else {
                        //			printf("drawing control: %s %s\n", control.controlType.c_str(), control.name.c_str());
                        control.draw(controlX, controlY);
                    }
                    
                    if(control.hasTitle) {
                        ofNoFill();
                        ofSetHexColor(config->borderColor);
                        glLineWidth(0.5f);
                        ofRect(controlX, controlY, control.width, control.height);
                    }
                    posY = getNextY(posY + control.height + config->padding.y);
                    
                    if(posY + y >= height - control.height - config->padding.y) {
                        if(alignRight) posX -= config->gridSize.x;
                        else posX += config->gridSize.x;
                        posY = 0;
                    }
                    
                    //		if(guiFocus == controls[i]->guiID) controls[i]->focused = true;		// MEMO
                    //		else							   controls[i]->focused = false;
                }
                //event stealing controls get drawn on top
                if(activeControl) {
                    activeControl->draw(stealingX, stealingY);
                    if(activeControl->hasTitle) {
                        ofNoFill();
                        ofSetHexColor(config->borderColor);
                        glLineWidth(0.5f);
                        ofRect(stealingX, stealingY, activeControl->width, activeControl->height);
                    }
                }
            }
            
            
            Control& Panel::addControl(Control& control) {
                controls.push_back(&control);
                width += control.width + config->padding.x;
                return control;
            }
            
            Button& Panel::addButton(string name, bool& value) {
                return (Button&)addControl(* new Button(this, name, value));
            }
            
            
            ColorPicker& Panel::addColorPicker(string name, ofFloatColor& color) {
                return (ColorPicker&)addControl(* new ColorPicker(this, name, color));
            }
            
            
            ComboBox& Panel::addComboBox(string name, int& value, int numChoices, string* choiceTitles) {
                return (ComboBox&)addControl(* new ComboBox(this, name, value, numChoices, choiceTitles));
            }
            
            ComboBox& Panel::addComboBox(string name, int& value, vector<string>& choiceTitles) {
                return (ComboBox&)addComboBox(name, value, choiceTitles.size(), &choiceTitles[0]);
            }

            Content& Panel::addContent(string name, ofBaseDraws& content, float fixwidth) {
                if(fixwidth == -1) fixwidth = config->gridSize.x - config->padding.x;
                return (Content&)addControl(* new Content(this, name, content, fixwidth));
            }
            
            FPSCounter& Panel::addFPSCounter() {
                return (FPSCounter&)addControl(* new FPSCounter(this));
            }
            
            QuadWarp& Panel::addQuadWarper(string name, ofBaseDraws& baseDraw, ofPoint *pts) {
                return (QuadWarp&)addControl(* new QuadWarp(this, name, baseDraw, pts));
            }
            //
            //MovieSlider& Panel::addMovieSlider(string name, ofVideoPlayer& input) {
            //	return (MovieSlider&)addControl(* new MovieSlider(name, input));
            //}
            
            SliderInt& Panel::addSlider(string name, int& value, int min, int max) {
                return (SliderInt&)addControl(* new SliderInt(this, name, value, min, max));
            }
            
            SliderFloat& Panel::addSlider(string name, float& value, float min, float max) {
                return (SliderFloat&)addControl(* new SliderFloat(this, name, value, min, max));
            }
            
            Slider2d& Panel::addSlider2d(string name, ofPoint& value, float xmin, float xmax, float ymin, float ymax) {
                return (Slider2d&)addControl(* new Slider2d(this, name, value, xmin, xmax, ymin, ymax));
            }
            
            Title& Panel::addTitle(string name, float height) {
                return (Title&)addControl(* new Title(this, name, height));
            }
            
            Toggle& Panel::addToggle(string name, bool& value) {
                return (Toggle&)addControl(* new Toggle(this, name, value));
            }

            
            
            void Panel::update(ofEventArgs& e) {
                for(int i=0; i<controls.size(); i++) controls[i]->update();
            }
            
            void Panel::setActiveControl(Control* control) {
                activeControl = control;
            }
            void Panel::releaseActiveControl() {
                activeControl = NULL;
            }
            
            void Panel::mouseMoved(ofMouseEventArgs& e) {
                if(activeControl)
                    activeControl->_mouseMoved(e);
                else
                    for(int i=0; i<controls.size(); i++) controls[i]->_mouseMoved(e);
            }
            
            void Panel::mousePressed(ofMouseEventArgs& e) {
                if(activeControl)
                    activeControl->_mousePressed(e);
                else
                    for(int i=0; i<controls.size(); i++) {
                        controls[i]->_mousePressed(e);
                        if(controls[i]->hitTest(e.x, e.y)) setActiveControl(controls[i]);
                    }
            }
            
            void Panel::mouseDragged(ofMouseEventArgs& e) {
                if(activeControl)
                    activeControl->_mouseDragged(e);
                else
                    for(int i=0; i<controls.size(); i++) controls[i]->_mouseDragged(e);
            }
            
            void Panel::mouseReleased(ofMouseEventArgs& e) {
                if(activeControl)
                    activeControl->_mouseReleased(e);
                else
                    for(int i=0; i<controls.size(); i++) controls[i]->_mouseReleased(e);
                
                releaseActiveControl();
            }
            
            void Panel::keyPressed(ofKeyEventArgs& e) {
                bool keyUp		= e.key == OF_KEY_UP;
                bool keyDown	= e.key == OF_KEY_DOWN;
                bool keyLeft	= e.key == OF_KEY_LEFT;
                bool keyRight	= e.key == OF_KEY_RIGHT;
                bool keyEnter	= e.key == OF_KEY_RETURN;
                
                for(int i=0; i<controls.size(); i++) {
                    Control *c = controls[i];
                    if(c->isMouseOver()) {
                        if(keyUp)		c->onKeyUp();
                        if(keyDown)		c->onKeyDown();
                        if(keyLeft)		c->onKeyLeft();
                        if(keyRight)	c->onKeyRight();
                        if(keyEnter)	c->onKeyEnter();
                        c->_keyPressed(e);
                    }
                }
            }
            
            void Panel::keyReleased(ofKeyEventArgs& e) {
                for(int i=0; i<controls.size(); i++) if(controls[i]->isMouseOver()) controls[i]->_keyReleased(e);
            }
            
            
            vector <Control*>&	Panel::getControls() {
                return controls;
            }
            
        }
    }
}