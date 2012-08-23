/*
 *  DvoracleRemapper.h
 *  Dvoracle
 *
 */
 
#ifndef DVORACLE_REMAPPER_H
#define DVORACLE_REMAPPER_H

#include <IOKit/IOLib.h>

 
namespace com_phogy_Dvoracle
{
 
    struct KeybEvent
    {
                               OSObject *target;
        /* eventFlags  */      unsigned   eventType;
        /* flags */            unsigned   flags;
        /* keyCode */          unsigned   key;
        /* charCode */         unsigned   charCode;
        /* charSet */          unsigned   charSet;
        /* originalCharCode */ unsigned   origCharCode;
        /* originalCharSet */  unsigned   origCharSet;
        /* keyboardType */     unsigned   keyboardType;
        /* repeat */           bool       repeat;
        /* atTime */           AbsoluteTime ts;
    };
        
    class DvoracleRemapper
    {
    private:
        static DvoracleRemapper *s_pInstance;
        DvoracleRemapper();
        
        enum
        {
            SVORAK_KEYMAP_SIZE = 100,
            KEYMAP_ENDMARK = 0xFFFFFFFF
        };
        
        struct KeyMapEntry
        {
            unsigned original;
            unsigned remap;
        };
        
        struct KeyMapOptionEntry
        {
            unsigned original;
            unsigned remapKey;
            unsigned remapFlags;
        };
        
        const static KeyMapEntry s_svorakKeymap[];
        const static KeyMapOptionEntry s_svorakA5Keymap[];
        
        typedef enum 
        {
            ALL_SVORAK_MODE,
            SVORAK_WITH_QWERTY_SHORTCUTS,
            ALL_QWERTY_MODE
        } KeyMapModeType;
        
        KeyMapModeType m_mode;
        
    protected:
    
        bool RemapSvorak(KeybEvent& event, bool &isMoreInSequence, unsigned sequenceIndex);
        bool RemapWindowsCopyPaste(KeybEvent& event, bool &isMoreInSequence, unsigned sequenceIndex);
        bool RemapHomeEnd(KeybEvent& event, bool &isMoreInSequence, unsigned sequenceIndex);
        bool RemapAppKey(KeybEvent& event, bool &isMoreInSequence, unsigned sequenceIndex);
        
        bool HandleModeSelector(KeybEvent& event, bool &isMoreInSequence, unsigned sequenceIndex);
    
    public:
        virtual ~DvoracleRemapper();
        
        static DvoracleRemapper *GetInstance() {if (!s_pInstance) {s_pInstance = new DvoracleRemapper;} return s_pInstance;}
        
        virtual void Remap(KeybEvent& event, bool &isMoreInSequence, unsigned sequenceIndex);
    
    };
 
 
}

#endif





