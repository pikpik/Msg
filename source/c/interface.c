// Included things

#include "interface.h"

#include "network.h"
#include "events.h"
#include "terminal.h"
#include "helpers.h"


// Global variables

char message [ 256 ];

int caretPosition = 1;

int updateMessageLineTimes = 0;


// Functions

void sendToTerminal ( void ) {
	
	// Make sure things get sent to the terminal.
	
	if ( fflush ( stdout ) != 0 )
		
		error ( NULL );
	
}


void clearMessageLine ( void ) {
	
	debug();
	
	// Return to first position on the line.
	
	printf ( clearLineString );
	
	// Erase the rest of the line.
	
	// How? Do we need to?
	
}


void updateMessageLine ( void ) {
	
	debug();
	
	clearMessageLine ();
	
	moveCaretToPosition ( 0 );
	
	printf ( "%s", message );
	
	moveCaretToPosition ( caretPosition );
	
	sendToTerminal ();
	
}


void moveCaretToPosition ( int position ) {
	
	debug();
	
	printf ( "%s[%dG", escapeKeyString, position );
	
}


void moveCaretForward ( void ) {
	
	debug();
	
	// We let the caret go a character further than the text.
	
	if ( caretPosition < strlen ( message ) + 1 ) caretPosition++;
	
	updateMessageLine ();
	
}


void moveCaretBackward ( void ) {
	
	debug();
	
	caretPosition = ( caretPosition <= 1 ) ? 1 : caretPosition - 1;
	
	updateMessageLine ();
	
}


void deleteCharacter ( void ) {
	
	if ( caretPosition == 1 ) return;
	
	
	int positionToDelete = caretPosition - 2;
	
	int originalMessageLength = strlen ( message );
	
	
	for ( int position = positionToDelete; position <= originalMessageLength; position++ )
		
		message [ position ] = message [ position + 1 ];
	
	
	moveCaretBackward ();
	
}


void interpretKey ( char * input ) {
	
	debug();
		
	if ( ! strcmp ( input, leftArrowKeyString ) ) {
		
		moveCaretBackward ();
		
	} else if ( ! strcmp ( input, rightArrowKeyString ) ) {
		
		moveCaretForward ();
		
	} else if ( ! strcmp ( input, deleteKeyString ) ) {
		
		deleteCharacter ();
		
	} else if ( ! strcmp ( input, enterKeyString ) ) {
		
		interpretCommand ();
		
	} else {
		
		// It's probably an ordinary character the user typed.
		
		if ( insertStringAtPositionInStringToLimit ( input, caretPosition - 1, message, 255 ) )
		
			moveCaretForward ();
		
	}
	
}


void interpretCommand () {
	
	debug();
	
	if ( strlen ( message ) == 0 ) {
		
		return;
		
	} else if ( message [ 0 ] == '/' ) {
		
		printf ( "A command!" );
		
		clearString ( message );
		
		caretPosition = 1;
		
		updateMessageLine ();
		
	} else {
		
		// Send the message.
		
		caretPosition = 1;
		
		updateMessageLine ();
		
		clearString ( message );
		
		printf ( "\n" );
		
	}
	
}


void showNewMessage ( char * inbox ) {
	
	debug();
	
	printf ( "%s", inbox );
	
}