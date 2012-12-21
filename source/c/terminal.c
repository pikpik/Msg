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

void startUsingTerminal ( int fd ) {
	
	debug();
	
	enableCharacterBreakMode ( fd );
	
	// Let's read from the "file," or socket, without waiting for it.
	
	fcntl ( fd, F_SETFL, O_NONBLOCK );
	
}


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


void onKeyPress ( int fileNumber, int event ) {
	
	debug();
	
	if ( event & EventReadable ) {
		
		char inputString [ 256 ];
		char stringChunk [ 256 ];
		
		memset ( & inputString, 0, sizeof inputString );
		memset ( & stringChunk, 0, sizeof stringChunk );
		
		while ( read ( fileNumber, stringChunk, 255 ) > 0 )
			
			appendStringToStringToLimit ( stringChunk, inputString, 255 );
		
		interpretKey ( inputString );
		
	}
	
	if ( event & EventFailed )
		
		error ( "I had a problem while waiting for keys to be pressed!\n" );
	
}


void stopUsingTerminal ( int fd ) {
	
	debug();
	
	restoreTerminal ( fd );
	
}