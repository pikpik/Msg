// Included things

#include "interface.h"

#include "network.h"
#include "events.h"
#include "terminal.h"
#include "helpers.h"


// Global variables

char message [ 256 ];

int caretPosition = 0;

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
	
	printf ( "%s", message );
	//printf ( "%s" "%d", message, ++updateMessageLineTimes );
	
	
	
	// Move the cursor/caret into position.
	
	//printf ( "%c[%dG", escapeKeyCharacter, caretPosition );
	
	// Make sure things get sent to the terminal.
	
	if ( fflush ( stdout ) != 0 )
		
		error ( NULL );
	
}


void moveCaretForward ( void ) {
	
	debug();
	
	printf("Yo!");
	
	// We let the caret go a character further than the text.
	
	if ( ( strlen ( message ) + 1 >= caretPosition ) && ( caretPosition < sizeof message ) ) caretPosition++;
	
	//strcpy ( message, "forward" );
	
	updateMessageLine ();
	
}


void moveCaretBackward ( void ) {
	
	debug();
	
	caretPosition = ( 0 >= caretPosition ) ? 0 : caretPosition - 1;
	
	//strcpy ( message, "backward" );
	
	updateMessageLine ();
	
}


void editMessageLine ( void ) {
	
	debug();
	
	// So helpful: http://en.wikipedia.org/wiki/ANSI_escape_sequences
	
	if ( input [ 0 ] == escapeKeyCharacter ) {
		
		debug();
		
		//introspectString ( input );
		//introspectString ( leftArrowKeyString );
		//introspectString ( cursorBackwardKeyString );
		//introspectString ( rightArrowKeyString );
		//introspectString ( cursorForwardKeyString );
		
		if ( strcmp ( input, leftArrowKeyString ) == 0 || strcmp ( input, cursorBackwardKeyString ) == 0 ) {
			
			debug();
			
			strcpy ( input, "" );
			
			moveCaretBackward ();
			
		} else if ( strcmp ( input, rightArrowKeyString ) == 0 || strcmp ( input, cursorForwardKeyString ) == 0 ) {
			
			debug();
			
			strcpy ( input, "" );
			
			moveCaretForward ();
				
		} else {
			
			debug();
			
			if ( strlen ( input ) > 2 ) {
				
				debug();
				
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
		
		strcpy ( message, "" );
		
		caretPosition = 0;
		
		updateMessageLine ();
		
	} else {
		
		// Send the message.
		
		printf ( "%s\n", message );
		
		strcpy ( message, "" );
		
		caretPosition = 0;
		
		updateMessageLine ();
		
	}
	
}


void showNewMessage ( char * inbox ) {
	
	debug();
	
	printf ( "%s", inbox );
	
}