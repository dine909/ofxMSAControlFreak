/*
 *  MSACGParameterTypes.cpp
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 07/11/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */


#include "ofxMSAControlFreak/src/ControlFreak.h"

namespace msa {
	namespace ControlFreak {
		namespace Types {
            
			struct case_insensitive_compare {
				bool operator() (const string & s1, const string & s2) const {
					return strcasecmp(s1.c_str(), s2.c_str()) < 0;
				}
			};
			
			static map<string, Index, case_insensitive_compare> indices;	// map to convert from NAME to INDEX
			
			static string names[] = {			// array to convert from INDEX to NAME
                "Unknown",
				"Float",
				"Int",
				"Toggle",
				"Bang",
				"NamedIndex",
                "Group",
                "Vec2f",
                "Vec3f",
                "Vec4f",
                "Coloru8",
                "Colorf32",
			};
			
            //--------------------------------------------------------------
			void setup() {
				for(int i=0; i<kNumTypes; i++) indices[ names[i] ] = (Index) i;
			}
			
            //--------------------------------------------------------------
			Index indexForName(string s) {
				if(indices.empty()) setup();
				return indices[s];
			}
			
            //--------------------------------------------------------------
			string nameForIndex(Index i) {
				if(indices.empty()) setup();
				return names[i];
			}
		}
		
		
		
	}
}