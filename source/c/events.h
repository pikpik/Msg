// Included header files

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


// Global variables

#define true			1
#define false			0

#define EventReadable	( 1 << 1 )
#define EventWritable	( 1 << 2 )
#define EventFailed		( 1 << 3 )


// Functions

void awaken ( void );

void when ( int file, int events, void ( * action ) );

void recognize ( int i );

int getHighestFileDescriptor ( void );

int waiting ( void );

void listenAndRespond ( void );