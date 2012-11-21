// Included header files

#include "helpers.h"


// Functions

void warning ( const char * message ) {
	
	if ( errno )
		
		perror ( ( message ) ? message : NULL );
		
	else if ( message )
		
		printf ( "%s\n", message );
	
}

void error ( const char * message ) {
	
	warning ( ( message ) ? message : NULL );
	
	exit ( 1 );
	
}