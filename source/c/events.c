// Included header files

#include "events.h"

#include "helpers.h"
#include "network.h"
#include "terminal.h"


// Global variables

#define listenerLimit	255


int numberOfListeners = 0;


fd_set	listeningToRead,
		listeningToWrite,
		listeningForError;

fd_set	listenersAreReadable,
		listenersAreWritable,
		listenersAreFailed;


typedef struct {
	
	int file;
	
	void ( * action ) ( int, int );
	
} listenerStructure;


listenerStructure listeners [ listenerLimit ];


// Use this to stop.

int waitingToQuit = 1;


// Functions

void awaken ( void ) {
	
	debug();
	
	FD_ZERO ( & listeningToRead );
	
	FD_ZERO ( & listeningToWrite );
	
	FD_ZERO ( & listeningForError );
	
}


void when ( int file, int events, void ( * action ) ) {
	
	//printf("when\n");
	
	listeners [ numberOfListeners ].file = file;
	
	listeners [ numberOfListeners ].action = action;
	
	
	if ( events & EventReadable )
		
		FD_SET ( file, & listeningToRead );
	
	if ( events & EventWritable )
		
		FD_SET ( file, & listeningToWrite );
	
	if ( events & EventFailed )
		
		FD_SET ( file, & listeningForError );
	
	
	numberOfListeners++;
	
}


void recognize ( int i ) {
	
	//printf("recognize\n");
	
	int events = 0;
	
	
	if ( FD_ISSET ( listeners [ i ].file, & listenersAreReadable ) )
		
		events |= EventReadable;
	
	if ( FD_ISSET ( listeners [ i ].file, & listenersAreWritable ) )
		
		events |= EventWritable;
	
	if ( FD_ISSET ( listeners [ i ].file, & listenersAreFailed ) )
		
		events |= EventFailed;
	
	
	if ( listeners [ i ].action != NULL )
		
		listeners [ i ].action ( listeners [ i ].file, events );

}


int getHighestFileDescriptor ( void ) {
	
	//printf("getHighestFileDescriptor\n");
	
	int highest = -1;
	
	for ( int i = 0; i < numberOfListeners; i++ )
		
		if ( listeners [ i ].file > highest )
			
			highest = listeners [ i ].file;
	
	return ( highest > -1 ) ? highest + 1 : -1;
	
}


int waiting ( void ) {
	
	debug();
	
	
	listenersAreReadable = listeningToRead;
	
	listenersAreWritable = listeningToWrite;
	
	listenersAreFailed = listeningForError;

	
	int result = select (
		getHighestFileDescriptor (),
		& listenersAreReadable,
		& listenersAreWritable,
		& listenersAreFailed,
		NULL
	);
	
	if ( 0 > result )
		
		error ( __FILE__ );
	
	
	for (
		int listener = 0;
		listener < numberOfListeners;
		listener++
	)
		
		recognize ( listener );
	
	
	return true;
	
}


void listenAndRespond ( void ) {
	
	//printf("listenAndRespond\n");
	
	while ( waiting () && waitingToQuit );
	
}


void signUpListeners ( void ) {
	
	debug();
	
	awaken ();
	
	when (
		  STDIN_FILENO,
		  EventReadable | EventFailed,
		  & onKeyPress
		  );
	
}


void runLoop ( int connection ) {
	
	debug();
	
	//printf("runLoop");
	
	enableCharacterBreakMode ( STDIN_FILENO );
	
	listenAndRespond ();
	
	restoreTerminal ( STDIN_FILENO );
	
	// In the future, this should be done asynchronously.
	
	// When data's available, it should be displayed
	// and the interface should be redrawn.
	
}


int chatWithProtocolToServer ( int connection, int protocol ) {
	
	debug();
	
	signUpListeners ();
	
	// Later this might involve reading, writing, or interacting,
	// depending on what's specified.
	
	runLoop ( connection );
	
	close ( connection );
	
	// There were no errors.
	
	return true;
	
}


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