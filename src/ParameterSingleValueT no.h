/*
 
 Template base class for any parameter which contains a simple single value (e.g. number)
 
 */

#pragma once

#include "ofxMSAControlFreak/src/ParameterValueT.h"

namespace msa {
    namespace ControlFreak {
        
        template <typename T>
        class ParameterSingleValueT : public ParameterValueT<T> {
        public:

            T operator=(const T & v) { this->setValue(v); }
			operator T() const { return this->getValue(); }

		protected:
            ParameterSingleValueT(string name, ParameterGroup *parent, Type::Index typeIndex)
            : ParameterValueT<T>(name, parent, typeIndex) {
//                ofLogVerbose() << "msa::ControlFreak::ParameterSingleValueT::ParameterSingleValueT: " <<  this->getPath();
                this->setValue(0);
            }
            
            // from ParameterValueT
            virtual void clamp();
            virtual void snap();
            
            // from Parameter
            virtual void writeToXml(ofxXmlSettings &xml, bool bOnlyValues);
            virtual void readFromXml(ofxXmlSettings &xml, bool bOnlyValues);
        };
        
        
        //--------------------------------------------------------------
        //--------------------------------------------------------------
        //--------------------------------------------------------------
		template <typename T>
        void ParameterSingleValueT<T>::writeToXml(ofxXmlSettings &xml, bool bOnlyValues) {
			ofLogVerbose() << "msa::ControlFreak::ParameterSingleValueT::writeToXml: " << this->getPath();
            
                        
            Parameter::writeToXml(xml, bOnlyValues);  // IMPORTANT: always start with parents write to xml
            xml.addAttribute(this->_xmlTag, "value", this->getValue(), this->_xmlTagId);
            if(!bOnlyValues) {
                xml.addAttribute(this->_xmlTag, "min", this->getMin(), this->_xmlTagId);
                xml.addAttribute(this->_xmlTag, "max", this->getMax(), this->_xmlTagId);
                xml.addAttribute(this->_xmlTag, "doClamp", this->getClamp(), this->_xmlTagId);
                xml.addAttribute(this->_xmlTag, "inc", this->getIncrement(), this->_xmlTagId);
                xml.addAttribute(this->_xmlTag, "doSnap", this->getSnap(), this->_xmlTagId);
            }
        }
        
        //--------------------------------------------------------------
		template <typename T>
        void ParameterSingleValueT<T>::readFromXml(ofxXmlSettings &xml, bool bOnlyValues) {
                        
            Parameter::readFromXml(xml, bOnlyValues);
            this->setValue(xml.getAttribute(this->_xmlTag, "value", T(), this->_xmlTagId));
            
			ofLogVerbose() << "msa::ControlFreak::ParameterSingleValueT::readFromXml: " << this->getPath();
        }
        
        //--------------------------------------------------------------
        template <typename T>
        void ParameterSingleValueT<T>::clamp() {
                        
            this->_setValue( this->getValue() < this->getMin() ? this->getMin() : this->getValue() > this->getMax() ? this->getMax() : this->getValue() );
        }
        
        //--------------------------------------------------------------
        template <typename T>
        void ParameterSingleValueT<T>::snap() {
            //            float inv = 1.0f / this->getIncrement();
            int ival = floor((this->getValue() - this->getMin()) / this->getIncrement());
            this->_setValue(this->getMin() + (T) (ival * this->getIncrement()) );
        }
        

    }
}