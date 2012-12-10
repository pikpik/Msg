// Included header files

#include "terminal.h"

#include "helpers.h"
#include "events.h"
#include "interface.h"


/*
 Source	StackOverflow
 From	http://stackoverflow.com/a/6857444
 Author	Daniel Leschkowski - http://stackoverflow.com/users/839180/daniel-leschkowski
 Editor	Tim Cooper - http://stackoverflow.com/users/142162/tim-cooper
 */


// Functions

char input [ 256 ];

static struct termios newterm;

static struct termios originalterm;


// Functions

void enableCharacterBreakMode ( int fd ) {
	
	debug();
	
	if ( tcgetattr ( fd, & originalterm ) == -1 )
		
		error ( NULL );
	
	newterm = originalterm;
	
	newterm.c_lflag = newterm.c_lflag & ~ ( ECHO | ICANON );
	
	newterm.c_cc [ VMIN ] = 1;
	
	newterm.c_cc [ VTIME ] = 0;
	
	if ( tcsetattr ( fd, TCSAFLUSH, & newterm ) == -1 )
		
		error ( NULL );
	
}


void restoreTerminal ( int fd ) {
	
	debug();
	
	if ( tcsetattr ( fd, TCSANOW, & originalterm ) == -1 )
		
		error ( NULL );
	
}


int getch () {
	
	debug();
	
	int cinput;
	
	enableCharacterBreakMode ( STDIN_FILENO );
	
	cinput = getchar ();
	
	restoreTerminal ( STDIN_FILENO );
	
	return cinput;
	
}


void interpretKey ( char character ) {
	
	debug();
	
	if ( strlen ( input ) > 0 ) {
		
		fflush ( stdout );
		
		appendCharacterToStringToLimit ( character, input, 255 );
		
		editMessageLine ();
		
	} else {
		
		if ( (int) character == escapeKeyInteger ) {
			
			// It could be the beginning of an ANSI escape sequence.
			
			// We'll check later characters for line-editing commands.
			
			strcpy ( input, escapeKeyString );
			
		} else if ( character == enterKeyCharacter ) {
			
			interpretCommand ();
			
		} else {
			
			// It's probably an ordinary character the user typed.
			
			appendCharacterToStringToLimit ( character, message, 255 );
			
			moveCaretForward ();
			
		}
		
	}
}


void onKeyPress ( int fileNumber, int event ) {
	
	debug();
	
	if ( event & EventReadable ) {
		
		interpretKey ( getchar () );
		
	}
	
	if ( event & EventFailed )
		
		error ( "I had a problem while waiting for keys to be pressed!\n" );
	
}