// Included header files

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>


// Definitions

#define EventReadable	( 1 << 1 )
#define EventWritable	( 1 << 2 )
#define EventFailed		( 1 << 3 )


// Global variables

extern int stillListening;


// Functions

void awaken ( void );

void when ( int file, int events, void ( * action ) );

void recognize ( int i );

int getHighestFileDescriptor ( void );

int listening ( void );

void runLoop ( void );

int chatWithProtocolToServer ( char * protocol, int connection );