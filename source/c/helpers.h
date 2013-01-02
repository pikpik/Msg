// Included header files

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/errno.h>
#include <string.h>


// Definitions

#define appName					"msg"

#define debugging				false


// ANSI terminal sequences

#define enterKeyString			"\n"
#define escapeKeyString			"\033"
#define deleteKeyString			"\177"
#define escapeKeyString			"\033"

#define ANSICSIString			escapeKeyString "["

#define leftArrowKeyString		ANSICSIString "D"
#define rightArrowKeyString		ANSICSIString "C"
#define cursorBackwardKeyString	ANSICSIString "1D"
#define cursorForwardKeyString	ANSICSIString "1C"
#define clearLineString			ANSICSIString "2K"

// See:
//		http://en.wikipedia.org/wiki/ASCII
//		http://en.wikipedia.org/wiki/ANSI_escape_sequences
//		http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap06.html


// Macros

#if debugging == true

#	define debug() printf ( "%s: %s: %d\n", __FILE__, __func__, __LINE__ ); fflush ( stdout );

#else

#	define debug()

#endif


// Functions

void help ( void );

void warning ( const char * message );

void error ( const char * message );

int appendStringToStringToLimit ( char * suffix, char * base, int lengthLimit );

int appendCharacterToStringToLimit ( char suffixCharacter, char * baseString, int lengthLimit );

int copyStringLengthIntoString ( char * source, int length, char * destination );

int insertStringAtPositionInStringToLimit ( char * source, int destinationPosition, char * destination, int lengthLimit );

char * limitStringLength ( char * originalString, int length );

void clearString ( char * string, int length );

void introspectString ( char * string );

void introspectStringToLength ( char * string, int length );

bool isCharacterSafeForPrinting ( char character );

bool isCharacterPrintable ( char character );