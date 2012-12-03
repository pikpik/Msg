// Included header files

#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <string.h>


// Global things

#define appName			"msg"
#define true			1
#define false			0
#define debugging		false

#if debugging == true
#	define debug() printf ( "%s:%s:%d\n", __FILE__, __func__, __LINE__ );
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

char * limitStringLength ( char * originalString, int length );

void introspectString ( char * string );