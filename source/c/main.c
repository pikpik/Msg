// Included things

#include "main.h"

#include "helpers.h"
#include "network.h"
#include "events.h"


// Begin

int main ( int argc, char * argv [] ) {
	
	debug();
	
	char protocol [ 256 ];
	
	char domain [ 256 ];
	
	int port;
	
	
	// What are we supposed to do?
	
	if ( ! (
		
		argc >= 2 && useProtocolOption ( argv [ 1 ], protocol ) &&
		
		argc >= 3 && useDomainOption ( argv [ 2 ], domain ) &&
		
		argc >= 4 && usePortOption ( argv [ 3 ], & port ) &&
		
		chatWithProtocolToServer (
			
			protocol,
			
			openConnection ( domain, port )
			
		)
		
	) ) help ();
	
	
	return 0;
	
}


// Functions

int useProtocolOption ( char * protocolOption, char * protocol ) {
	
	debug();
	
	// Later, this should return a struct(ure) of named functions for actions.
	
	if (
		
		strcmp ( protocolOption, "irc" ) == 0 &&
		
		copyStringLengthIntoString ( protocolOption, 255, protocol )
		
	)	return true;
	
	warning (
		
		"\n"
		"Unknown protocol.\n"
		"\n"
		"Try: irc\n"
		
	);
	
	return false;
	
}


int useDomainOption ( char * domainOption, char * domain ) {
	
	debug();
	
	if (
		
		strlen ( domainOption ) > 3 &&
		
		copyStringLengthIntoString ( domainOption, 255, domain )
		
	)	return true;
	
	warning (
		
		"\n"
		"Unknown domain.\n"
		"\n"
		"Try: irc.freenode.net\n"
		
	);
	
	return false;
	
}


int usePortOption ( char * portOption, int * port ) {
	
	debug();
	
	// Switch to strtol?
	
	int testNumberOfPort = atoi ( portOption );
	
	if ( port >= 0 ) {
		
		// Copy the new number to port's address.
		
		* port = testNumberOfPort;
		
		return true;
		
	}
	
	warning (
		
		"\n"
		"Not a port.\n"
		"\n"
		"Try: 6667\n"
		
	);
	
	return false;
	
}