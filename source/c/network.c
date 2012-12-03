// Included things

#include "network.h"

#include "helpers.h"
#include "events.h"
#include "interface.h"


// Global variables

char outbox [ 256 ];

char inbox [ 256 ];


// Functions

int openConnection ( char * domain, int port ) {
	
	debug();
	
	
	struct sockaddr_in serverIPAddress;
	
	struct hostent * server;
	
	
	int connection = socket ( AF_INET, SOCK_STREAM, 0 );
	
	if ( connection < 0 )
		
		error ( "Unable to start a connection." );
	
	
	server = gethostbyname ( domain );
	
	if ( server == NULL )
		
		error ( "Unable to find specified server." );
	
	
	memset (
			
			( char * ) &serverIPAddress,
			
			0,
			
			sizeof ( serverIPAddress )
			
	);
	
	bcopy (
			
			( char * ) server->h_addr,
			
			( char * ) &serverIPAddress.sin_addr.s_addr,
			
			server->h_length
			
	);
	
	
	serverIPAddress.sin_family = AF_INET;
	
	serverIPAddress.sin_port = htons ( port );
	
	
	if (
		
		connect (
				
				connection,
				
				( struct sockaddr * ) & serverIPAddress,
				
				sizeof ( serverIPAddress )
				
		) < 0
		
	)
		
		error ( "Unable to connect to the server." );
	
	
	// Let's read from the "file," or socket, without waiting for it.
	
	fcntl ( connection, F_SETFL, O_NONBLOCK );
	
	
	// Start listening!
	
	when ( connection, EventReadable | EventFailed, & newMessage );
	
	
	return connection;
	
}

void sendMessage ( int connection, char * buffer ) {
	
	debug();
	
	int result = write ( connection, buffer, strlen ( buffer ) );
	
	if ( result < 0 )
		
		error ( "Unable to send messages." );
	
}


void newMessage ( int connection, int events ) {
	
	debug();
	
	if ( events & EventReadable ) {
		
		int response;
		
		while ( ( response = receiveMessage ( connection ) ) > 0 ) {
			
			showNewMessage ( inbox );
			
		}
		
		
		if ( response == 0 )
			
			waitingToQuit = 0;
		
	}
	
}


int receiveMessage ( int connection ) {
	
	debug();
	
	memset ( & inbox, 0, sizeof inbox );
	
	return read ( connection, inbox, 255 );
	
}