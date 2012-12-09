/*
 * Thanks to the fKeys project (http://www.kodachi.com/fKeys/)
 * for the IOKit technique used in this file.
 */

#include <IOKit/IOLib.h>
#include "Dvoracle.h"
#include "DvoracleKeyboardHandler.h"
#include "DvoracleRemapper.h"

//namespace com_phogy_Dvoracle
//{

	using namespace com_phogy_Dvoracle;

	// Notification callbacks
	bool CB_IOHIKeyboardMatched(void *target, void *refCon, IOService *newService);
    bool CB_IOHIKeyboardTerminated(void *target, void *refCon, IOService *newService);

	// Sole instance of the behavior manager.
	//KeyBehaviorManager keyBehaviorManager;

	// Define my superclass
	#define super IOService
	// REQUIRED! This macro defines the class's constructors, destructors,
	// and several other methods I/O Kit requires. Do NOT use super as the
	// second parameter. You must use the literal name of the superclass.
	OSDefineMetaClassAndStructors(Dvoracle, IOService)



	bool Dvoracle::init(OSDictionary *dict)
	{
		bool res = super::init(dict);
		//IOLog("init+++\n");
		
		//IOLog("init---\n");
		return res;
	}

	void Dvoracle::free(void)
	{
		//IOLog("Dvoracle free+++\n");
		
		delete DvoracleKeyboardHandler::GetInstance();
        delete DvoracleRemapper::GetInstance();
		
		super::free();
		//IOLog("Dvoracle free---\n");
	}

	IOService *Dvoracle::probe(IOService *provider, SInt32 *score)
	{
		//IOLog("probe+++\n");
		IOService *res = super::probe(provider, score);
		//IOLog("probe---\n");
		return res;
	}

	bool Dvoracle::start(IOService *provider)
	{
		//IOLog("start+++\n");
		bool res = super::start(provider);
		
		if (res)
		{

			m_pKeybMatchedNotification = addNotification(gIOMatchedNotification,
				serviceMatching("IOHIKeyboard"),
				((IOServiceNotificationHandler) &CB_IOHIKeyboardMatched),
				this, NULL, 0);
				
			if (m_pKeybMatchedNotification == NULL)
			{
				IOLog("Dvoracle ERROR: Cannot add notification for matching IOHIKeyboard.");
				return false;
			}

			m_pKeybTerminatedNotification = addNotification(gIOTerminatedNotification,
				serviceMatching("IOHIKeyboard"),
				((IOServiceNotificationHandler) &CB_IOHIKeyboardTerminated),
				this, NULL, 0);

			if (m_pKeybTerminatedNotification == NULL)
			{
				IOLog("Dvoracle ERROR: Cannot add notification for terminated IOHIKeyboard.");
				return false;
			}
		}
		
		//IOLog("start---\n");
		
		return res;
	}

	void Dvoracle::stop(IOService *provider)
	{
		//IOLog("Dvoracle stop+++\n");
        IOLog("Dvoracle VERBOSE: Service stop requested.\n");
        DvoracleKeyboardHandler::GetInstance()->StopAllKeyboards();
		
		// Cancel all notifications
		if (m_pKeybMatchedNotification)
		{
			m_pKeybMatchedNotification->remove();
		}
		if (m_pKeybTerminatedNotification)
		{
			m_pKeybTerminatedNotification->remove();
		}

		super::stop(provider);
		
		//IOLog("Dvoracle stop---\n");
	}
	
	// Called when a IOHIKeyboard has been matched
	bool CB_IOHIKeyboardMatched(void *target, void *refCon, IOService *newService)
	{
		//IOLog("CB_IOHIKeyboardMatched+++\n");
		
		//DvoracleKeyboardHandler *pKeybHandler = static_cast<DvoracleKeyboardHandler *> (target);
		DvoracleKeyboardHandler::GetInstance()->StartKeyboard(OSDynamicCast(IOHIKeyboard, newService));
		
		//IOLog("CB_IOHIKeyboardMatched---\n");
		return true;
	}

	// Called when a IOHIKeyboard has been terminated
	bool CB_IOHIKeyboardTerminated(void *target, void *refCon, IOService *newService)
	{
		//IOLog("CB_IOHIKeyboardTerminated+++\n");
		
		//DvoracleKeyboardHandler *pKeybHandler = static_cast<DvoracleKeyboardHandler *> (target);
		DvoracleKeyboardHandler::GetInstance()->StopKeyboard(OSDynamicCast(IOHIKeyboard, newService));
		
		//IOLog("CB_IOHIKeyboardTerminated---\n");
		return true;
	}

//} // Namespace
