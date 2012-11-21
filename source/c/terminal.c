// Included header files

#include "terminal.h"
#include "helpers.h"


// Functions

/*
 Source	StackOverflow
 From	http://stackoverflow.com/a/6857444
 Author	Daniel Leschkowski - http://stackoverflow.com/users/839180/daniel-leschkowski
 Editor	Tim Cooper - http://stackoverflow.com/users/142162/tim-cooper
 */

static struct termios newterm;
static struct termios originalterm;

void enableCharacterBreakMode ( int fd ) {
	
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
	
	if ( tcsetattr ( fd, TCSANOW, & originalterm ) == -1 )
		
		error ( NULL );
	
}

int getch () {
	
	int cinput;
	
	enableCharacterBreakMode ( STDIN_FILENO );
	
	cinput = getchar ();
	
	restoreTerminal ( STDIN_FILENO );
	
	return cinput;
	
}