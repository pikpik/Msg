// Included header files

#include "helpers.h"


// Functions

void help ( void ) {
	
	debug();
	
	fprintf (
		
		stdout,
		
		"\n"
		"Usage: " appName " <protocol> <server> <port>\n"
		"\n"
		
	);
	
	exit ( 1 );
	
}


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


int appendStringToStringToLimit ( char * suffix, char * base, int lengthLimit ) {
	
	strncat ( base, suffix, lengthLimit );
	
	return true;
	
}


int appendCharacterToStringToLimit ( char suffixCharacter, char * baseString, int lengthLimit ) {
	
	char convertedCharacter [ 1 ];
	
	if ( sprintf ( convertedCharacter, "%c", suffixCharacter ) <= 0 )
		
		return false;
	
	return appendStringToStringToLimit ( convertedCharacter, baseString, lengthLimit );
	
}


int copyStringLengthIntoString ( char * source, int length, char * destination ) {
	
	debug();
	
	memset (
		destination,
		'\0',
		sizeof ( destination )
	);
	
	strncpy (
		destination,
		source,
		length - 1
	);
	
	return true;
	
}


char * limitStringLength ( char * originalString, int length ) {
	
	// Add one byte for the null ending.
	
	int newStringLength = length + 1;
	
	char * newString = malloc ( newStringLength * sizeof ( char ) );
	
	memset (
		newString,
		'\0',
		sizeof ( newString )
	);
	
	strncpy (
		newString,
		originalString,
		newStringLength
	);
	
	return newString;
	
}


void introspectString ( char * string ) {
	
	for ( int i = 0; i < strlen ( string ); i++ )
		
		printf ( " %c (%d);", string [ i ], string [ i ] );
	
	printf ( "\n" );
	
	fflush ( stdout );
	
}