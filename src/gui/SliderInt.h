#pragma once

#include  "ofxMSAControlFreak/src/gui/SliderBase.h"


namespace msa {
    namespace ControlFreak {
        namespace gui {
            
            class SliderInt : public SliderBase<int> {
                
            public:
                SliderInt(Panel* parent, string name, int &value, int min, int max) : SliderBase<int>(parent, name, value, min, max) {
                    controlType = "SliderInt";
                    setIncrement(1);
                }
                
            };
            
        }
    }
}