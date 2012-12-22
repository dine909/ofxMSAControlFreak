/*
 *  GuiBase.h
 *  MSA demo msalibs2
 *
 *  Created by Memo Akten on 01/10/2010.
 *  Copyright 2010 MSA Visuals Ltd. All rights reserved.
 *
 */

#pragma once

#include "MSAControlFreakParameter.h"
#include "MSAControlFreakGroup.h"

namespace MSA {
	namespace ControlFreak {
		
		class GuiBase {
		public:
			
			// add this parameter to the Gui
			virtual void addParameter(Parameter *param) = 0;
			
			// add this group to the Gui
//			virtual void addGroup(ParameterGroup &group) = 0;
			
		};
	}
}