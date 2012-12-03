// Included header files

#include <termios.h>
#include <unistd.h>


// Globals

extern char input [ 256 ];

// Functions

void enableCharacterBreakMode ( int fd );

void restoreTerminal ( int fd );

int getch ();

void onKeyPress ( int fileNumber, int event );

void interpretKey ( char character );