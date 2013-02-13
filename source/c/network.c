// Included things

#include "network.h"

#include "interface.h"
#include "helpers.h"
#include "events.h"


// Global variables

char outbox [ 256 ];

char inbox [ 256 ];


// Functions

int openConnection ( string domain, string port ) {
	
	debug();
	
	
	int socketConnection;
	
	int response;
	
	
	struct addrinfo options;
	
	memset ( & options, 0, sizeof options );
	
	options.ai_family = AF_UNSPEC;
	options.ai_socktype = SOCK_STREAM;
	options.ai_flags = AI_PASSIVE;
	
	
	struct addrinfo * addressMatches;
	
	response = getaddrinfo ( domain, port, & options, & addressMatches );
	
	if ( response ) {
		
		printf ( "%s\n", gai_strerror ( response ) );
		
		exit ( 1 );
		
	}
	
	
	for ( struct addrinfo * attempt = addressMatches; attempt != NULL; attempt = attempt->ai_next ) {
		
		socketConnection = socket ( attempt->ai_family, attempt->ai_socktype, attempt->ai_protocol );
		
		if ( socketConnection < 0 )
			
			continue;
		
		
		response = connect ( socketConnection, attempt->ai_addr, attempt->ai_addrlen );
		
		if ( response )
			
			continue;
		
		
		break;
	}
	
	
	// Let's read from the "file," or socket, without waiting for it.
	
	fcntl ( socketConnection, F_SETFL, O_NONBLOCK );
	
	
	// Start listening!
	
	when ( socketConnection, EventReadable | EventWritable | EventFailed, & onNetworkMessage );
	
	
	return socketConnection;
	
}


void onNetworkMessage ( int connection, int events ) {
	
	debug();
	
	
	if ( events & EventReadable ) {
		
		int response;
		
		while ( ( response = receiveMessage ( connection ) ) > 0 ) {
			
			showNewMessage ( inbox );
			
		}
		
		
		if ( response == 0 )
			
			stillListening = false;
		
	}
	
	if ( events & EventWritable )
		
		//printf ( "I can write now!\n" );
		
		sendMessage ( connection );
	
	/*if ( events & EventFailed )
		
		printf ( "Something went wrong.\n" );*/
	
}


void putMessageInOutbox ( char * message ) {
	
	debug();
	
	clearString ( outbox, 256 );
	
	copyStringLengthIntoString ( message, 255, outbox );
	
}


void sendMessage ( int connection ) {
	
	debug();
	
	
	if ( ! strlen ( outbox ) ) return;
	
	
	outbox [ strlen ( outbox ) ] = '\r';
	outbox [ strlen ( outbox ) ] = '\n';
	
	int result = write ( connection, outbox, strlen ( outbox ) );
	
	if ( result < 0 )
		
		error ( "Unable to send messages." );
	
	
	clearString ( outbox, 256 );
	
}


int receiveMessage ( int connection ) {
	
	debug();
	
	memset ( & inbox, 0, sizeof inbox );
	
	return read ( connection, inbox, 255 );
	
}