// Included header files

#include "helpers.h"


// Functions

void help ( void ) {
	
	debug();
	
	
	fprintf (
		
		stdout,
		
		"\n"
		"  Usage: " appName " <protocol> <server> <port>\n"
		"\n"
		"  protocols: irc\n"
		"\n"
		"     server: irc.freenode.net\n"
		"\n"
		"       port: 6667\n"
		"\n"
		
	);
	
	exit ( 1 );
	
}


void warning ( const char * message ) {
	
	debug();
	
	
	if ( errno )
		
		perror ( ( message ) ? message : NULL );
		
	else if ( message )
		
		printf ( "%s\n", message );
	
}


void error ( const char * message ) {
	
	debug();
	
	
	warning ( ( message ) ? message : NULL );
	
	exit ( 1 );
	
}


int appendStringToStringToLimit ( char * suffix, char * base, int lengthLimit ) {
	
	debug();
	
	
	strncat ( base, suffix, lengthLimit );
	
	return true;
	
}


int appendCharacterToStringToLimit ( char suffixCharacter, char * baseString, int lengthLimit ) {
	
	debug();
	
	
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

int insertStringAtPositionInStringToLimit ( char * source, int destinationPosition, char * destination, int lengthLimit ) {
	
	debug();
	
	
	// How much can we fit?
	
	int ignoredCharacters = destinationPosition;
	
	int consideredCharacters = lengthLimit - ignoredCharacters;
	
	int availableCharacters = consideredCharacters - ( strlen ( destination ) - ignoredCharacters );
	
	int charactersToCopy = strlen ( source );
	
	
	if ( availableCharacters < charactersToCopy ) return false;
	
	
	int positionToChange = ( strlen ( destination ) - 1 );
	
	int positionToMove = positionToChange + charactersToCopy;
	
	
	while ( positionToChange >= destinationPosition ) {
		
		// Move the destination's character back.
		
		destination [ positionToMove ] = destination [ positionToChange ];
		
		positionToChange--;
		
		positionToMove--;
		
	}
	
	
	positionToChange = destinationPosition;
	
	int positionToCopy = 0;
	
	
	for ( int charactersMoved = 0; charactersMoved < charactersToCopy; charactersMoved++ ) {
		
		// Copy the source's character to the destination.
		
		destination [ positionToChange ] = source [ positionToCopy ];
		
		positionToChange++;
		
		positionToCopy++;
		
	}
	
	
	return true;
	
}


char * limitStringLength ( char * originalString, int length ) {
	
	debug();
	
	
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


void clearString ( char * string, int length ) {
	
	debug();
	
	memset ( string, '\0', length );
	
}


void introspectString ( char * string ) {
	
	debug();
	
	for ( int i = 0; i < strlen ( string ); i++ )
		
		printf (
			" %c (%d);",
			string [ i ],
			string [ i ]
		);
	
	printf ( "\n" );
	
	fflush ( stdout );
	
}


void introspectStringToLength ( char * string, int length ) {
	
	debug();
	
	for ( int i = 0; i <= length; i++ )
		
		printf (
				" %c (%d);",
				string [ i ],
				string [ i ]
				);
	
	printf ( "\n" );
	
	fflush ( stdout );
	
}