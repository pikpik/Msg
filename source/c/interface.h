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

#include "helpers.h"


// Globals

extern char message [ 256 ];


// Functions

void addTextToScreen ( char * text );

void updateMessageLine ( void );

void clearMessageLine ( void );

void sendToTerminal ( void );

void moveCursorToPosition ( int position );

void moveCursorForward ( void );

void moveCursorBackward ( void );

void deleteCharacter ( void );

void interpretKey ( char * input );

void startIRCConnection ( void );

void interpretCommand ();

void interpretIRCCommand ( string message );

void sendPrivateMessageToRecipient ( string message, string recipient );

void showNewMessage ( char * text );

void clearMessage ( void );

void joinChannel ( string channel );

void filterChannel ( string channel );