// Included things

#include "events.h"
#include "terminal.h"
#include "helpers.h"


// Functions

/* void onKeyPress ( int fileNumber, int event ) {
	
	if ( event & EventReadable ) {
		
		char buffer [ 1 ];
		
		read ( fileNumber, buffer, 1 );
		
		printf ( "A key was pressed! (%s)\n", buffer );
		
	}
	
	if ( event & EventFailed )
		
		error ( "I had a problem while waiting for keys to be pressed!\n" );
	
}


void aardvark ( int fileNumber, int event ) {
	
	printf ( "Hello!\n" );
	
} */


void onKeyPress ( int fileNumber, int event ) {
	
	if ( event & EventReadable ) {
		
		
		char character = getchar ();
		
		
		if ( character == '\n' )
			
			printf ( "\t(Hello!)\n" );
		
		else
			
			putchar ( character );
		
		
		if ( fflush ( stdout ) != 0 )
			
			error ( NULL );
		
	}
	
	if ( event & EventFailed )
		
		error ( "I had a problem while waiting for keys to be pressed!\n" );
	
}


void signUpListeners () {
	
	/* when (
		STDIN_FILENO,
		EventReadable | EventFailed,
		& onKeyPress
	);
	
	when (
		STDIN_FILENO,
		EventReadable,
		& aardvark
	); */
	
	when (
		STDIN_FILENO,
		EventReadable | EventFailed,
		& onKeyPress
	);
	
}


// Begin

int main ( void ) {
	
	awaken ();
	
	signUpListeners ();
	
	enableCharacterBreakMode ( STDIN_FILENO );
	
	listenAndRespond ();
	
	restoreTerminal ( STDIN_FILENO );
	
	return false;
	
}