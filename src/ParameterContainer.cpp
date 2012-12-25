/*
 *  MSACFParameters.cpp
 *  UK Summer Games v2
 *
 *  Created by Memo Akten on 23/08/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#include "ofxMSAControlFreak/src/ControlFreak.h"


namespace msa {
	namespace ControlFreak {
        
        //--------------------------------------------------------------
		ParameterContainer::ParameterContainer(ParameterContainer *parent, string name, Type::Index typeIndex)
        : Parameter(parent, name, typeIndex) {
            ofLogVerbose() << "msa::ControlFreak::ParameterContainer::ParameterContainer " <<  getPath();
		}
		
        //--------------------------------------------------------------
		ParameterContainer::~ParameterContainer() {
            ofLogVerbose() << "msa::ControlFreak::ParameterContainer::~ParameterContainer " <<  getPath();
			int np = getNumParams();
			for(int i=0; i<np; i++) delete _paramArr[i];
		}
        
        
        //--------------------------------------------------------------
        int ParameterContainer::getNumParams() const {
			assert(_paramArr.size() == _paramMap.size());	// probably tried to add a parameter with the same name (in the same group)
			return _paramMap.size();
		}
		
        
        //--------------------------------------------------------------
        Parameter& ParameterContainer::getParameter(int index) {
			return *_paramArr[index];
        }
        
        //--------------------------------------------------------------
        Parameter& ParameterContainer::getParameter(string path) {
            //            ofLogVerbose() << "msa::ControlFreak::ParameterContainer::getParameter " << path;
            Parameter *p = _paramMap.at(path);
            return *p;
            //            vector<string> pathbits = ofSplitString(path, getPathDivider(), true, true);
            //            ParameterContainer *p = this;
            //            for(int i=0; i<pathbits.size(); i++) {
            //                //                p = &_paramMap[pathbits[i]];
            //                // TODO:
            //            }
            //			return *_paramMap[path];
        }
        
        //--------------------------------------------------------------
        ParameterValueT<int>& ParameterContainer::getInt(string path) {
            return dynamic_cast<ParameterInt&>(getParameter(path));
        }
        
        //--------------------------------------------------------------
        ParameterValueT<float>& ParameterContainer::getFloat(string path) {
            return dynamic_cast<ParameterFloat&>(getParameter(path));
        }
        
        //--------------------------------------------------------------
        ParameterValueT<bool>& ParameterContainer::getBool(string path) {
            return dynamic_cast<ParameterBool&>(getParameter(path));
        }
        
        //--------------------------------------------------------------
        ParameterNamedIndex& ParameterContainer::getNamedIndex(string path) {
            return dynamic_cast<ParameterNamedIndex&>(getParameter(path));
        }
        
        //--------------------------------------------------------------
        ParameterContainer& ParameterContainer::getContainer(string path) {
            return dynamic_cast<ParameterContainer&>(getParameter(path));
        }
        
        
        
        //--------------------------------------------------------------
        //		Parameter& ParameterContainer::operator[](int index) {
        //            return getParameter(index);
        //		}
        //
        //        //--------------------------------------------------------------
        //		Parameter& ParameterContainer::operator[](string path) {
        //            return getParameter(path);
        //		}
		
        //--------------------------------------------------------------
        void ParameterContainer::writeToXml(ofxXmlSettings &xml, bool bFull) {
			ofLogVerbose() << "msa::ControlFreak::ParameterContainer::writeToXml " << getPath();
            
            Parameter::writeToXml(xml, bFull);
            xml.pushTag(_xmlTag, _xmlTagId);
            
            for(int i=0; i<_paramArr.size(); i++) {
                Parameter &p = *_paramArr[i];
                p.writeToXml(xml, bFull);
            }
            
            xml.popTag();
        }
        
        //--------------------------------------------------------------
        void ParameterContainer::readFromXml(ofxXmlSettings &xml, bool bFull) {
			ofLogVerbose() << "msa::ControlFreak::ParameterContainer::readFromXml " << getPath();
            
        }
        
        
        //--------------------------------------------------------------
		Parameter& ParameterContainer::addParameter(Parameter *param) {
			ofLogVerbose() << "msa::ControlFreak::ParameterContainer::addParameter " << param->getPath() << " name: " << param->getName();
			
            _paramMap[param->getName()] = param;
            _paramArr.push_back(param);
            param->setParent(this);
            getNumParams();	// to check if correctly added to both containers
            return *param;
		}
        
        
        //--------------------------------------------------------------
        void ParameterContainer::update() {
            Parameter::update();
            int np = getNumParams();
            for(int i=0; i<np; i++) {
                Parameter &p = getParameter(i);
                p.update();
            }
        }
        
        
    }
}