/*
 *  DvoracleRemapper.cpp
 *  Dvoracle
 *
 */

#include "DvoracleRemapper.h"
#include "KeyConstants.h"

namespace com_phogy_Dvoracle
{

    DvoracleRemapper *DvoracleRemapper::s_pInstance = 0;
    
    // Svorak layout on Swedish Pro
    const DvoracleRemapper::KeyMapEntry DvoracleRemapper::s_svorakKeymap[] = {
        {0x00, 0x00}, {0x01, 0x1F}, {0x02, 0x0E}, {0x03, 0x20},
        {0x04, 0x02}, {0x05, 0x22}, {0x06, 0x2F}, {0x07, 0x0c},
        {0x08, 0x26}, {0x09, 0x28}, {0x0B, 0x07}, {0x0C, 0x21}, 
        {0x0D, 0x27}, {0x0E, 0x29}, {0x0F, 0x23}, {0x10, 0x03},
        {0x11, 0x10}, {0x1F, 0x0F}, {0x20, 0x05}, {0x21, 0x2B},
        {0x22, 0x08}, {0x23, 0x25}, {0x25, 0x2D}, {0x26, 0x04},
        {0x27, 0x2C}, {0x28, 0x11}, {0x29, 0x01}, {0x2a, 0x2a},
        {0x2b, 0x0d}, {0x2c, 0x06}, {0x2d, 0x0b}, {0x2e, 0x2e},
        {0x2f, 0x09},
        {KEYMAP_ENDMARK, 0x00}
    };
    
    const DvoracleRemapper::KeyMapOptionEntry DvoracleRemapper::s_svorakA5Keymap[] = {
        {0x00, 0x2B, SHIFT_FLAG}, {0x01, 0x1A, SHIFT_FLAG},
        {0x02, 0x1C, SHIFT_FLAG}, {0x03, 0x19, SHIFT_FLAG},
        {0x04, 0x14, SHIFT_FLAG}, {0x05, 0x1A, OPTION_FLAG},
        {0x06, 0x2F, SHIFT_FLAG}, {0x07, 0x1D, SHIFT_FLAG},
        {0x08, 0x13, OPTION_FLAG}, {0x09, 0x12, SHIFT_FLAG},
        {0x0B, 0x1A, SHIFT_FLAG | OPTION_FLAG}, {0x0C, 0x1C, SHIFT_FLAG | OPTION_FLAG},
        {0x0D, 0x19, SHIFT_FLAG | OPTION_FLAG}, {0x0E, 0x1C, OPTION_FLAG},
        {0x0F, 0x19, OPTION_FLAG}, {0x10, 0x13, SHIFT_FLAG},
        {0x11, 0x15, OPTION_FLAG}, {0x1F, 0x32, 0},
        {0x20, 0x1B, SHIFT_FLAG}, {0x22, 0x16, SHIFT_FLAG},
        {0x23, 0x32, SHIFT_FLAG}, {0x25, 0x13, SHIFT_FLAG},
        {0x26, 0x2C, 0}, {0x28, 0x14, SHIFT_FLAG},
        {0x29, 0x1E, OPTION_FLAG}, {0x2A, 0x2A, SHIFT_FLAG},
        {0x2B, 0x2A, SHIFT_FLAG},
        {0x2C, 0x15, SHIFT_FLAG}, {0x2D, 0x17, SHIFT_FLAG},
        {0x2E, 0x1B, 0}, {0x2F, 0x1E, SHIFT_FLAG},

        {KEYMAP_ENDMARK, 0x00, 0}
    };
    
    DvoracleRemapper::DvoracleRemapper():
        m_mode(ALL_SVORAK_MODE)
    {
    }
    
    
    DvoracleRemapper::~DvoracleRemapper()
    {
        s_pInstance = 0;
    }
    
    void DvoracleRemapper::Remap(KeybEvent& event, bool &isMoreInSequence, unsigned sequenceIndex)
    {
        HandleModeSelector(event, isMoreInSequence, sequenceIndex);
    
        // Remap Copy, cut and paste on TypeMatrix
        RemapWindowsCopyPaste(event, isMoreInSequence, sequenceIndex);

        // Remap Svorak keys if enabled
        if (m_mode == ALL_SVORAK_MODE || 
            (m_mode == SVORAK_WITH_QWERTY_SHORTCUTS &&
                !(event.flags & (OPTION_FLAG | COMMAND_FLAG | CONTROL_FLAG))))
        {
            if (RemapSvorak(event, isMoreInSequence, sequenceIndex)) 
            {
                return;
            }
        }
    
        // Remap home and end keys
        if (RemapHomeEnd(event, isMoreInSequence, sequenceIndex))
        {
            return;
        }
    }
    
    bool DvoracleRemapper::HandleModeSelector(KeybEvent& event, bool &isMoreInSequence, unsigned sequenceIndex)
    {
        if (event.flags & CAPSLOCK_FLAG)
        {
            m_mode = ALL_QWERTY_MODE; //SVORAK_WITH_QWERTY_SHORTCUTS
        }
        else
        {
            m_mode = ALL_SVORAK_MODE;
        }

        if (event.flags & CAPSLOCK_FLAG)
        {
            event.flags &= ~CAPSLOCK_FLAG; // Clear Caps lock.
        }
        
        return true;
    }
    
    bool DvoracleRemapper::RemapSvorak(KeybEvent& event, bool &isMoreInSequence, unsigned sequenceIndex)
    {
        if ((event.flags & OPTION_FLAG))
        {
            event.flags &= ~OPTION_FLAG;
            // Perform some A5 mappings
            int k = 0;
            while(s_svorakA5Keymap[k].original != KEYMAP_ENDMARK && k < SVORAK_KEYMAP_SIZE)
            {
                if (s_svorakA5Keymap[k].original == event.key)
                {
                    event.key = s_svorakA5Keymap[k].remapKey;
                    event.flags = s_svorakA5Keymap[k].remapFlags;
                    return true;
                }
                
                k++;
            }
            
            event.flags |= OPTION_FLAG;

        }        
        
        // Remap the keys according to keymap array
        
        int k = 0;
        while(s_svorakKeymap[k].original != KEYMAP_ENDMARK && k < SVORAK_KEYMAP_SIZE)
        {
            if (s_svorakKeymap[k].original == event.key)
            {
                event.key = s_svorakKeymap[k].remap;
                return true;
            }
            
            k++;
        }
        

        return false;
    }
    
    bool DvoracleRemapper::RemapWindowsCopyPaste(KeybEvent& event, bool &isMoreInSequence, unsigned sequenceIndex)
    {
        if (event.key == FORWARD_DELETE_KEY &&
             (event.flags & SHIFT_FLAG))
        {
            // CUT
            
            if (event.eventType == KEY_DOWN)
            {
                if (sequenceIndex == 0) 
                {
                    event.key = COMMAND_KEY;
                    event.eventType = KEY_MODIFY;
                    event.flags = COMMAND_FLAG;
                    event.charCode = 0;
                    event.charSet = 0;
                    event.origCharCode = 0;
                    event.origCharSet = 0;   
                    
                    isMoreInSequence = true;
                }
                else
                {
                    event.flags = COMMAND_FLAG;
                    event.eventType = KEY_DOWN;
                    event.key = 11;
                    event.charCode = 98;
                    event.charSet = 0;
                    event.origCharCode = 98;
                    event.origCharSet = 0;
                }
            }
            else
            {
                if (sequenceIndex == 0)
                {
                    event.flags = COMMAND_FLAG;
                    event.eventType = KEY_UP;
                    event.key = 11;
                    event.charCode = 98;
                    event.charSet = 0;
                    event.origCharCode = 98;
                    event.origCharSet = 0;
                    
                    isMoreInSequence = true;
                }
                else
                {
                    event.key = COMMAND_KEY;
                    event.eventType = KEY_MODIFY;
                    event.flags = 0;
                    event.charCode = 0;
                    event.charSet = 0;
                    event.origCharCode = 0;
                    event.origCharSet = 0;
                }
            }


            return true;
        }
        
        if (event.key == INSERT_KEY &&
                (event.flags & SHIFT_FLAG))
        {
            // PASTE
            if (event.eventType == KEY_DOWN)
            {
                if (sequenceIndex == 0) 
                {
                    event.key = COMMAND_KEY;
                    event.eventType = KEY_MODIFY;
                    event.flags = COMMAND_FLAG;
                    event.charCode = 0;
                    event.charSet = 0;
                    event.origCharCode = 0;
                    event.origCharSet = 0;   
                    
                    isMoreInSequence = true;
                }
                else
                {
                    event.flags = COMMAND_FLAG;
                    event.eventType = KEY_DOWN;
                    event.key = 47;
                    event.charCode = 46;
                    event.charSet = 0;
                    event.origCharCode = 46;
                    event.origCharSet = 0;
                }
            }
            else
            {
                if (sequenceIndex == 0)
                {
                    event.flags = COMMAND_FLAG;
                    event.eventType = KEY_UP;
                    event.key = 47;
                    event.charCode = 46;
                    event.charSet = 0;
                    event.origCharCode = 46;
                    event.origCharSet = 0;
                    
                    isMoreInSequence = true;
                }
                else
                {
                    event.key = COMMAND_KEY;
                    event.eventType = KEY_MODIFY;
                    event.flags = 0;
                    event.charCode = 0;
                    event.charSet = 0;
                    event.origCharCode = 0;
                    event.origCharSet = 0;
                }
            }
            
            return true;
        }
        
        if (event.key == INSERT_KEY &&
                (event.flags & CONTROL_FLAG))
        {
            // COPY
            if (event.eventType == KEY_DOWN)
            {
                if (sequenceIndex == 0) 
                {
                    event.key = COMMAND_KEY;
                    event.eventType = KEY_MODIFY;
                    event.flags = COMMAND_FLAG;
                    event.charCode = 0;
                    event.charSet = 0;
                    event.origCharCode = 0;
                    event.origCharSet = 0;   
                    
                    isMoreInSequence = true;
                }
                else
                {
                    event.flags = COMMAND_FLAG;
                    event.eventType = KEY_DOWN;
                    event.key = 34; 
                    event.charCode = 105; 
                    event.charSet = 0;
                    event.origCharCode = 105;
                    event.origCharSet = 0;
                }
            }
            else
            {
                if (sequenceIndex == 0)
                {
                    event.flags = COMMAND_FLAG;
                    event.eventType = KEY_UP;
                    event.key = 34; 
                    event.charCode = 105; 
                    event.charSet = 0;
                    event.origCharCode = 105;
                    event.origCharSet = 0;
                    
                    isMoreInSequence = true;
                }
                else
                {
                    event.key = COMMAND_KEY;
                    event.eventType = KEY_MODIFY;
                    event.flags = 0;
                    event.charCode = 0;
                    event.charSet = 0;
                    event.origCharCode = 0;
                    event.origCharSet = 0;
                }
            }
            
            return true;
        }
        
        return false;
    }
    
    bool DvoracleRemapper::RemapHomeEnd(KeybEvent& event, bool &isMoreInSequence, unsigned sequenceIndex)
    {
        if ((event.key == HOME_KEY || event.key == END_KEY) && 
                ((event.flags & COMMAND_FLAG) == 0))
        {
            if (event.eventType == KEY_DOWN) // Home Key Down
            {
                if (sequenceIndex == 0)
                {
                    // Press the Cmd key
                    event.key = COMMAND_KEY;
                    event.eventType = KEY_MODIFY;
                    event.flags = COMMAND_FLAG;
                    event.charCode = 0;
                    event.charSet = 0;
                    event.origCharCode = 0;
                    event.origCharSet = 0;
                    
                    isMoreInSequence = true;
                }
                else
                {
                    // Simulate the Cmd - Left key down
                    event.key = event.key == HOME_KEY ? LEFT_ARROW_KEY : RIGHT_ARROW_KEY;
                    event.flags |= COMMAND_FLAG;
                }
            }
            else // Home Key Up 
            {
                if (sequenceIndex == 0)
                {
                    // Simulate Cmd - Left key up
                    event.key = event.key == HOME_KEY ? LEFT_ARROW_KEY : RIGHT_ARROW_KEY;
                    event.flags |= COMMAND_FLAG;
                    
                    isMoreInSequence = true;
                }
                else
                {
                    // Release the Cmd key
                    event.key = COMMAND_KEY;
                    event.eventType = KEY_MODIFY;
                    event.flags = 0;
                    event.charCode = 0;
                    event.charSet = 0;
                    event.origCharCode = 0;
                    event.origCharSet = 0;
                }
            }

            return true; // Key was remapped.
        }

        return false;
    }
    
    bool DvoracleRemapper::RemapAppKey(KeybEvent& event, bool &isMoreInSequence, unsigned sequenceIndex)
    {
        if (event.key == APP_KEY)
        {
            if (event.eventType == KEY_DOWN) // App key pressed
            {
                if (sequenceIndex == 0)
                {
                    event.key = COMMAND_KEY;
                    event.eventType = KEY_MODIFY;
                    event.flags = COMMAND_FLAG;
                    event.charCode = 0;
                    event.charSet = 0;
                    event.origCharCode = 0;
                    event.origCharSet = 0;
                    
                    isMoreInSequence = true;

                }
                else
                {
                    event.key = 50;
                    event.charCode = 96;
                    event.charSet = 0;
                    event.origCharCode = 96;
                    event.origCharSet = 0;
                    event.flags = COMMAND_FLAG;
                }
            }
            else // App Key released
            {
                if (sequenceIndex == 0)
                {
                    event.key = 50;
                    event.charCode = 96;
                    event.charSet = 0;
                    event.origCharCode = 96;
                    event.origCharSet = 0;
                    event.flags = COMMAND_FLAG;
                    
                    isMoreInSequence = true;
                }
                else
                {
                    event.key = COMMAND_KEY;
                    event.eventType = KEY_MODIFY;
                    event.flags = 0;
                    event.charCode = 0;
                    event.charSet = 0;
                    event.origCharCode = 0;
                    event.origCharSet = 0;
                    
                }
            }

        }
    
        return false;
    }

}