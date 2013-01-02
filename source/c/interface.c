// Included things

#include "interface.h"

#include "network.h"
#include "events.h"
#include "terminal.h"
#include "helpers.h"


// Global variables

#define messageLength				256

#define messagePossibleCharacters	255

char message [ messageLength ];


#define cursorStartingPosition		1

int cursorPosition = cursorStartingPosition;


int updateMessageLineTimes = 0;


// Functions

void addTextToScreen ( char * text ) {
	
	debug();
	
	clearMessageLine ();
	
	moveCursorToPosition ( 0 );
	
	printf ( "%s", text );
	
}


void updateMessageLine ( void ) {
	
	debug();
	
	addTextToScreen ( message );
	
	moveCursorToPosition ( cursorPosition );
	
	sendToTerminal ();
	
}


void clearMessageLine ( void ) {
	
	debug();
	
	printf ( clearLineString );
	
}


void sendToTerminal ( void ) {
	
	if ( fflush ( stdout ) != 0 )
		
		error ( NULL );
	
}


void moveCursorToPosition ( int position ) {
	
	debug();
	
	// Move the cursor horizontally.
	
	// See CHA - Cursor Horizontal Absolute at http://en.wikipedia.org/wiki/ANSI_escape_code#CSI_codes
	
	printf ( "%s[%dG", escapeKeyString, position );
	
}


void moveCursorForward ( void ) {
	
	debug();
	
	// We let the cursor go a character further than the text.
	
	if ( cursorPosition < strlen ( message ) + 1 ) cursorPosition++;
	
	updateMessageLine ();
	
}


void moveCursorBackward ( void ) {
	
	debug();
	
	cursorPosition = ( cursorPosition <= cursorStartingPosition ) ?
		cursorStartingPosition
	:
		cursorPosition - 1;
	
	updateMessageLine ();
	
}


void deleteCharacter ( void ) {
	
	if ( cursorPosition == cursorStartingPosition ) return;
	
	
	int positionToDelete = cursorPosition - 2;
	
	int originalMessageLength = strlen ( message );
	
	
	for (
		
		int position = positionToDelete;
		
		position <= originalMessageLength;
		
		position++
		
	)
		
		message [ position ] = message [ position + 1 ];
	
	
	moveCursorBackward ();
	
}


void interpretKey ( char * input ) {
	
	debug();
	
	if ( input [ 0 ] == escapeKeyString [ 0 ] ) {
		
		if ( ! strcmp ( input, leftArrowKeyString ) ) {
			
			moveCursorBackward ();
			
		} else if ( ! strcmp ( input, rightArrowKeyString ) ) {
			
			moveCursorForward ();
			
		}
		
	} else if ( ! strcmp ( input, enterKeyString ) ) {
		
		interpretCommand ();
		
	} else if ( ! strcmp ( input, deleteKeyString ) ) {
		
		deleteCharacter ();
		
	} else {
		
		// It's probably an ordinary character.
		
		if ( insertStringAtPositionInStringToLimit ( input, cursorPosition - 1, message, messagePossibleCharacters ) )
		
			moveCursorForward ();
		
	}
	
}


void interpretCommand () {
	
	debug();
	
	// See http://www.irchelp.org/irchelp/rfc/chapter4.html
	
	if ( strlen ( message ) == 0 ) {
		
		return;
		
	} /*else if ( message [ 0 ] == '/' ) {
		
		printf ( "A command!" );
		
		clearMessage ();
		
	}*/ else {
		
		// Show the message.
		
		addTextToScreen ( message );
		
		printf ( "\n" );
		
		
		// Send the message.
		
		putMessageInOutbox ( message );
		
		
		// We don't need the message anymore.
		
		clearMessage ();
		
	}
	
}


void showNewMessage ( char * text ) {
	
	debug();
	
	addTextToScreen ( text );
	
	updateMessageLine ();
	
}


void clearMessage ( void ) {
	
	cursorPosition = cursorStartingPosition;
	
	clearString ( message, messageLength );
	
	updateMessageLine ();
	
}