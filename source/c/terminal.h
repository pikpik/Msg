// Included header files

#include <termios.h>
#include <unistd.h>


// Functions

void enableCharacterBreakMode ( int fd );

void restoreTerminal ( int fd );

int getch ();