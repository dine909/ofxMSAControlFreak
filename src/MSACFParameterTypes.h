/*
 *  MSACGParameterTypes.h
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 07/11/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#pragma once

#include <string>

using namespace std;

namespace MSA {
	namespace ControlFreak {
		namespace Types {
			
			enum Index {
				kFloat,
				kInt,
				kToggle,
				kBang,
				kNamedIndex,
				kNumTypes
			};
			
			Index indexForName(string s);
			string nameForIndex(Index i);
		}
	}
}