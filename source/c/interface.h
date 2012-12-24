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


// Globals

extern char message [ 256 ];


// Functions

void addLineToScreen ( char * text );

void updateMessageLine ( void );

void clearMessageLine ( void );

void sendToTerminal ( void );

void moveCaretToPosition ( int position );

void moveCaretForward ( void );

void moveCaretBackward ( void );

void deleteCharacter ( void );

void interpretKey ( char * input );

void interpretCommand ();

void showNewMessage ( char * text );