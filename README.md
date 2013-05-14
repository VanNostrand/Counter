Counter
=======

Magic the Gathering Counter for Manabase.de


Usage
=====
* The lifecounter is the LCD number, it's default value is 20.
* Click + or - to increase or decrease the lifecounter by 1.
* The log window shows date and time and the last changes.
* Use Add to add the given value in the spinbox right to the Add button to the lifecounter. Adding a negative number subtracts it.
* Use Set to set the lifecounter to the given value in the spinbox right to the Set button.
* Use Reset to set the lifecounter to the given value in the spinbox right to the Reset button and clear the log window.
* You may use the file chooser to select/create a *.txt file where the current life value is being written into. The content will be overwritten. You have to delete the file manually.

License
=======
See COPYING.
Images are from the Crystal Clear icon set by Everaldo Coelho, licensed under LGPL.


Build Instructions
==================
You can download the source code from https://github.com/VanNostrand/Counter

* On Windows install MinGW
* Install Qt4
* Run qmake
* Run make on Linux and make -f Makefile.Release on Windows
* Use NSIS installer to create a distributable package.