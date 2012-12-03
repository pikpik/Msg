// Included things

#include "main.h"

#include "helpers.h"
#include "network.h"
#include "events.h"


// Begin

int main ( int argc, char * argv [] ) {
	
	// To see the path:
	
	// Set debugging to true in helpers.h,
	// run build.sh,
	// and run the program again.
	
	debug();
	
	
	// What are we supposed to do?
	
	int protocol;
	
	char * domain;
	
	int port;
	
	
	if ( argc >= 2 )
		
		protocol = useProtocolOption ( argv [ 1 ] );
		
	else
		
		help ();
	
	
	if ( argc >= 3 )
		
		domain = useDomainOption ( argv [ 2 ] );
		
	else
		
		help ();
	
	
	if ( argc >= 4 )
		
		port = usePortOption ( argv [ 3 ] );
		
	else
		
		help ();
	
	
	chatWithProtocolToServer (
		
		protocol,
		
		openConnection ( domain, port )
		
	);
	
	return 0;
	
}


// Functions

int useProtocolOption ( char * protocolOption ) {
	
	debug();
	
	
	// Do we recognize the option?
	
	if ( strcmp ( protocolOption, "irc" ) == 0 ) {
		
		// Later, this should return a struct of named functions for actions.
		
		return true;
		
	}
	
	
	warning (
			 
			 "\n"
			 "Unknown protocol.\n"
			 "\n"
			 "Try: irc\n"
			 
			 );
	
	help ();
	
}


char * useDomainOption ( char * domainOption ) {
	
	if ( strlen ( domainOption ) < 4 ) {
		
		warning (
				 
				 "\n"
				 "Unknown domain.\n"
				 "\n"
				 "Try: irc.freenode.net\n"
				 
				 );
		
		help ();
		
	}
	
	return limitStringLength ( domainOption, 255 );
	
}


int usePortOption ( char * portOption ) {
	
	debug();
	
	int port = atoi ( portOption );
	
	// Switch to strtol?
	
	if ( port >= 0 ) {
		
		return port;
		
	} else {
		
		warning (
				 
				 "\n"
				 "Not a port.\n"
				 "\n"
				 "Try: 6667\n"
				 
				 );
		
		help ();
		
	}
	
}