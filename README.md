Dvoracle
========

Dvorak kernel module for Mac OS X
USE AT YOUR OWN RISK
It may crash at any time and that results for sure in a kernel panic, and the user losing all their unsaved work.

What it does:
----------------
Implements Svorak A5+ (Swedish dvorak). Hooks itself into the kernel and intercepts/translates keyboard events.
Use Caps Lock key to disable when loaded.

For info (Swedish) about the layout A5, visit http://aoeu.info/s/dvorak/svorak (I'm not the inventor of this layout)

There are no ways to configure this thing at this moment so probably of less usage for non-Swedish people.

System should have "Swedish Pro" (built-in Mac OS X) set as the current keyboard layout.
Dvoracle also supports the Windows style copy/paste Ctrl+Ins, Shift+Ins and Shift+Del commands. 
This is to support the excellent Typematrix (http://typematrix.com/2030/features.php) keyboard's easy access buttons. 
(Cmd+C/V/X are not as easily accessed on Dvorak)
Adds Home and End behavior as on PC.


