// Included header files

#include "events.h"

#include "helpers.h"
#include "network.h"
#include "terminal.h"
#include "interface.h"


// Global variables

#define listenerLimit	FD_SETSIZE

int numberOfListeners = 0;

typedef struct {
	
	int file;
	
	void ( * action ) ( int, int );
	
} listenerStructure;

listenerStructure listeners [ listenerLimit ];


fd_set	listeningToRead,		listeningToWrite,		listeningForFailure,
		listenersCanRead,		listenersCanWrite,		listenersHaveFailed;


// Use this to stop.

int stillListening = true;


// Functions

void awaken ( void ) {
	
	debug();
	
	
	int numberOfListeners = 0;
	
	
	FD_ZERO ( & listeningToRead );
	
	FD_ZERO ( & listeningToWrite );
	
	FD_ZERO ( & listeningForFailure );
	
}


void when ( int file, int events, void ( * action ) ) {
	
	debug();
	
	
	listeners [ numberOfListeners ].file = file;
	
	listeners [ numberOfListeners ].action = action;
	
	
	if ( events & EventReadable )
		
		FD_SET ( file, & listeningToRead );
	
	if ( events & EventWritable )
		
		FD_SET ( file, & listeningToWrite );
	
	if ( events & EventFailed )
		
		FD_SET ( file, & listeningForFailure );
	
	
	numberOfListeners++;
	
}


void recognize ( int i ) {
	
	debug();
	
	
	int events = 0;
	
	
	if ( FD_ISSET ( listeners [ i ].file, & listenersCanRead ) ) {
		
		events |= EventReadable;
		
		
		/*
		 
		 Notes
		 
		 Bug: the first to read gets the data.
		 
		 Solution: allow many listeners per event source.
		 
		 Have one fd_set of sources and another queue with listeners per source.
		 
		 listeners [ FD ] [ event type ] = { function 1, function 2, ... };
		 
		 When a listener is added for a file descriptor (FD), the FD is added to the fd_set if it isn't already in it.
		 
		 When a listener is removed for an FD, the list is searched by function address and the function is removed.
		 
		 If an FD's list empties, then the list is removed and the FD is removed from the fd_set.
		 
		 When an event arrives for an FD, the data is read into a buffer, and then the buffer of data is copied to every appropriate listener.
		 
		*/
		
		/*char whatWasRead [ 256 ];
		
		memset ( & whatWasRead, '\0', 256 );
		
		read ( listeners [ i ].file, whatWasRead, 255 );
		
		printf ( "%s\n", whatWasRead );*/
		
	}
	
	if ( FD_ISSET ( listeners [ i ].file, & listenersCanWrite ) )
		
		events |= EventWritable;
	
	if ( FD_ISSET ( listeners [ i ].file, & listenersHaveFailed ) )
		
		events |= EventFailed;
	
	
	if ( listeners [ i ].action != NULL )
		
		listeners [ i ].action ( listeners [ i ].file, events );
	
}


int getHighestFileDescriptor ( void ) {
	
	debug();
	
	
	int highest = -1;
	
	
	for ( int i = 0; i < numberOfListeners; i++ )
		
		if ( listeners [ i ].file > highest )
			
			highest = listeners [ i ].file;
	
	
	return highest;
	
}


int listening ( void ) {
	
	debug();
	
	
	FD_COPY ( & listeningToRead, & listenersCanRead );
	
	FD_COPY ( & listeningToWrite, & listenersCanWrite );
	
	FD_COPY ( & listeningForFailure, & listenersHaveFailed );
	
	
	//struct timeval timeout;
	
	//timeout.tv_sec = 2;
	
	
	int result = select (
		
		getHighestFileDescriptor () + 1,
		
		& listenersCanRead,
		
		& listenersCanWrite,
		
		& listenersHaveFailed,
		
		NULL //& timeout
		
	);
	
	
	if ( result < 0 ) {
		
		error ( __FILE__ );
		
		stillListening = false;
		
	}
	
	
	for (
		
		int listener = 0;
		
		listener < numberOfListeners;
		
		listener++
		
	)	recognize ( listener );
	
	
	return stillListening;
	
}


void runLoop ( void ) {
	
	debug();
	
	while ( listening () );
	
}


int chatWithProtocolToServer ( char * protocol, int connection ) {
	
	debug();
	
	startUsingTerminal ( STDIN_FILENO );
	
	startIRCConnection ();
	
	runLoop ();
	
	stopUsingTerminal ( STDIN_FILENO );
	
	close ( connection );
	
	return true;
	
}