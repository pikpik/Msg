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
	
	
	// Put what the user's writing on the screen.
	
	moveCaretToPosition ( 0 );
	
	printf ( "%s", message );
	
	moveCaretToPosition ( caretPosition );
	
	
	// Make sure things get sent to the terminal.
	
	if ( fflush ( stdout ) != 0 )
		
		error ( NULL );
	
}


void moveCaretToPosition ( int position ) {
	
	debug();
	
	printf ( "%c[%dG", escapeKeyCharacter, position );
	
}


void moveCaretForward ( void ) {
	
	debug();
	
	// We let the caret go a character further than the text.
	
	if ( caretPosition < strlen ( message ) + 1 ) caretPosition++;
	
	updateMessageLine ();
	
}


void moveCaretBackward ( void ) {
	
	debug();
	
	caretPosition = ( caretPosition <= 0 ) ? 0 : caretPosition - 1;
	
	updateMessageLine ();
	
}


void editMessageLine ( void ) {
	
	debug();
	
	if ( input [ 0 ] == escapeKeyCharacter ) {
		
		if ( strcmp ( input, leftArrowKeyString ) == 0 || strcmp ( input, cursorBackwardKeyString ) == 0 ) {
			
			clearString ( input );
			
			moveCaretBackward ();
			
		} else if ( strcmp ( input, rightArrowKeyString ) == 0 || strcmp ( input, cursorForwardKeyString ) == 0 ) {
			
			clearString ( input );
			
			moveCaretForward ();
				
		} else {
			
			if ( strlen ( input ) > 2 ) {
				
				strcpy ( input, "" );
				
			}
			
		}
		
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