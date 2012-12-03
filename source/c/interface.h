// Included things

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>


// Definitions

#define enterKeyCharacter '\n'
#define escapeKeyCharacter '\033'
#define escapeKeyString "\033"
#define escapeKeyInteger 27
#define ANSICSIString escapeKeyString "["
#define leftArrowKeyString ANSICSIString "D"
#define rightArrowKeyString ANSICSIString "C"
#define cursorBackwardKeyString ANSICSIString "1D"
#define cursorForwardKeyString ANSICSIString "1C"
#define clearLineString ANSICSIString "2K"

// See: http://en.wikipedia.org/wiki/ANSI_escape_sequences


// Globals

extern char message [ 256 ];


// Functions

void clearMessageLine ( void );

void updateMessageLine ( void );

void moveCaretForward ( void );

void moveCaretBackward ( void );

void editMessageLine ( void );

void interpretCommand ();

void showNewMessage ( char * inbox );