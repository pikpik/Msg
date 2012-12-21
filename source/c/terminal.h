// Included header files

#include <sys/fcntl.h>
#include <termios.h>
#include <unistd.h>


// Globals

extern char input [ 256 ];

// Functions

void startUsingTerminal ( int fd );

void enableCharacterBreakMode ( int fd );

void restoreTerminal ( int fd );

int getch ();

void onKeyPress ( int fileNumber, int event );

void stopUsingTerminal ( int fd );