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


bool isCharacterSafeForPrinting ( char character ) {
	
	return (
		
		(
			
				character == 9	// Horizontal tab (\t)
			
			||	character == 10	// Line feed (\n)
			
			||	character == 13	// Carriage return (\r)
			
		)
		
		||	isCharacterPrintable ( character )
		
	);
	
}


bool isCharacterPrintable ( char character ) {
	
	// See http://en.wikipedia.org/wiki/ASCII#ASCII_control_characters
	
	return (
		
			character > 31		// Control characters
		
		&&	character != 127	// Delete
		
	);
	
}

/*

Start of text-searching engine.

Concept:
 
 char * message = "/join (channel)\0";
 
 if ( ! stringsMatch ( afterStringPattern ( afterStringPattern ( afterString ( message, "JOIN" ), & isWhitespaceCharacter ), & isPrintableCharacter ), "\0" ) ) {
	
	char * channel = stringPattern ( afterStringPattern ( afterString ( message, "JOIN" ), & isWhitespaceCharacter ), & isPrintableCharacter );
	
	joinChannel ( channel );
	
 }
 
*/


bool isWhitespaceCharacter ( char character ) {
	
	return (
		
			character == '\t'
		||	character == ' '
		
	);
	
}

bool isPrintableCharacter ( char character ) {
	
	return isCharacterPrintable ( character );
	
}

/*bool isCharacterPattern () {
	
	for () {}
	
}

bool getCharacterPattern () {}*/


bool stringsMatch ( string a, string b ) {
	
	// Can strcmp compare \0's?
	
	// If not, we'll need to compare manually.
	
	return ( ! strcmp ( a, b ) );
	
}


/*string stringFromTo ( string source, int from, int to ) {
	
	char subbuff[5];
	
	memcpy( subbuff, &buff[10], 4 );
	
	subbuff[4] = '\0';
	
}*/


string stringAfterPattern ( string source, bool ( * patternFunction ) ( char ) ) {
	
	// Find the position after the pattern.
	
	int length = strlen ( source );
	
	int position;
	
	for ( position = 0; position < length; position++ ) {
		
		if ( ! patternFunction ( source [ position ] ) )
			
			break;
		
	}
	
	// If nothing matched,
	// or the position is after the source string,
	// then return an empty string.
	
	if (
			position == 0
		||	length <= position
	)
		
		return "\0";
	
	// Copy the rest.
	
	// Ok, let's cheat and just return a pointer that's looking at the start of the substring.
	
	// This is faster and saves memory, but makes things fragile:
	// any change to the substring changes the source string, and vice versa.
	
	return ( source + position );
	
}


string stringOfPattern ( string source, bool ( * patternFunction ) ( char ) ) {
	
	// Find the position after the pattern.
	
	int length = strlen ( source );
	
	int position;
	
	for ( position = 0; position < length; position++ ) {
		
		if ( ! patternFunction ( source [ position ] ) )
			
			break;
		
	}
	
	// If nothing matched,
	// or the position is after the source string,
	// then return an empty string.
	
	if (
			position == 0
		||	length <= position
	)
		
		return "\0";
	
	// Copy position-many characters, starting at the beginning.
	
	string result;
	
	strncpy ( result, source, position );
	
	return result;
	
}


string stringAfterString ( string source, string term ) {
	
	// Where is the term in the string?
	
	string substring = strstr ( source, term );
	
	// If the term isn't in the source string
	// or the term is longer than the source string, (Is this necessary?)
	// then the say nothing matched.
	
	if (
			substring == NULL
		||	strlen ( source ) < strlen ( substring )
	)
		
		return "\0";
	
	// Return a pointer to what's after the term.
	
	return substring + strlen ( term );
	
}


string stringAfterPrefix ( string source, string prefix ) {
	
	// Where is the prefix in the string?
	
	string substring = strstr ( source, prefix );
	
	// If the prefix isn't in the source string,
	// they aren't the same,
	// or the prefix is longer than the source string, (Is this necessary?)
	// then the say nothing matched.
	
	if (
			substring == NULL
		||	strcmp ( source, substring ) != 0
		||	strlen ( source ) < strlen ( substring )
	)
		
		return "\0";
	
	// Return a pointer to what's after the prefix.
	
	return source + strlen ( prefix );
	
}

/*
 
 String parser test cases
 
 To be moved to unit tests later.
 
 printf ( "Test ABC after A: [%s]\n", stringAfterString ( "ABC", "A" ) ); Should be: BC
 printf ( "Test ABC after B: [%s]\n", stringAfterString ( "ABC", "B" ) ); Should be: C
 printf ( "Test ABC after C: [%s]\n", stringAfterString ( "ABC", "C" ) ); Should be: (\0)
 printf ( "Test ABC after AB: [%s]\n", stringAfterString ( "ABC", "AB" ) ); Should be: C
 printf ( "Test ABC after BC: [%s]\n", stringAfterString ( "ABC", "BC" ) ); Should be: (\0)
 printf ( "Test ABC after ABC: [%s]\n", stringAfterString ( "ABC", "ABC" ) ); Should be: (\0)
 
 printf ( "\n" );
 
 printf ( "Test ABC after A: [%s]\n", stringAfterPrefix ( "ABC", "A" ) ); Should be: BC
 printf ( "Test ABC after B: [%s]\n", stringAfterPrefix ( "ABC", "B" ) ); Should be: (\0)
 printf ( "Test ABC after C: [%s]\n", stringAfterPrefix ( "ABC", "C" ) ); Should be: (\0)
 printf ( "Test ABC after AB: [%s]\n", stringAfterPrefix ( "ABC", "AB" ) ); Should be: C
 printf ( "Test ABC after BC: [%s]\n", stringAfterPrefix ( "ABC", "BC" ) ); Should be: (\0)
 printf ( "Test ABC after ABC: [%s]\n", stringAfterPrefix ( "ABC", "ABC" ) ); Should be: (\0)

*/