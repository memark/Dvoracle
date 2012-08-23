#ifndef DVORACLE_H
#define DVORACLE_H

#include <IOKit/IOService.h>
#include "DvoracleKeyboardHandler.h"

//namespace com_phogy_Dvoracle
//{
	
	class Dvoracle : public IOService
	{
		OSDeclareDefaultStructors(Dvoracle)
		
	public:
		virtual bool init(OSDictionary *dictionary = 0);
		virtual void free(void);
		
		virtual IOService *probe(IOService *provider, SInt32 *score);
		
		virtual bool start(IOService *provider);
		virtual void stop(IOService *provider);

		IONotifier *m_pKeybMatchedNotification;
		IONotifier *m_pKeybTerminatedNotification;
		
		com_phogy_Dvoracle::DvoracleKeyboardHandler *m_pKeybHandler;
	};
//}

#endif

