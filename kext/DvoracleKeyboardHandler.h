/*
 *  DvoracleKeyboardHandler.h
 *  Dvoracle
 *
 *  Created by Christopher on 2007-12-04.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include <IOKit/IOService.h>
#include "DvoracleRemapper.h"
 
 // The Ugly Hack Part.
#define protected public
#include <IOKit/hidsystem/IOHIKeyboard.h>
#undef protected

#ifndef DVORACLE_KEYBOARD_HANDLER_H
#define DVORACLE_KEYBOARD_HANDLER_H

namespace com_phogy_Dvoracle {

	class DvoracleKeyboardHandler
	{
	private:
        static DvoracleKeyboardHandler *s_pInstance;
        
        enum
		{
			MAX_KEYBOARDS = 10,
            MAX_SEQUENCE = 32
		}; 
        
        struct KeybEntry
		{
			IOHIKeyboard *pKbd;
			KeyboardEventAction originalEventAction;
			KeyboardSpecialEventAction originalSpecialEventAction;
		};

        KeybEntry m_keyboards[MAX_KEYBOARDS];

        
        
        
        DvoracleKeyboardHandler();

		bool IsValidKeyboardType(const char *pTypeName);
        KeybEntry *FindCurrentKeybEntry();

       
    public:
		
		~DvoracleKeyboardHandler();
        static DvoracleKeyboardHandler *GetInstance() { if(!s_pInstance) {s_pInstance = new DvoracleKeyboardHandler();} return s_pInstance;}
        
        void HandleEvent(KeybEvent& event);
		
		void StartKeyboard(IOHIKeyboard *pKbd);
		void StopKeyboard(IOHIKeyboard *pKbd);
        
        void StopAllKeyboards();
	};
    

}

#endif

