// Included things

#include "main.h"

#include "helpers.h"
#include "network.h"
#include "events.h"


// Begin

int main ( int argc, char * argv [] ) {
	
	debug();
	
	
	// Get ready
	
	char protocol [ 256 ];
	
	char domain [ 256 ];
	
	char port [ 256 ];
	
	awaken ();
	
	
	// What are we supposed to do?
	
	if ( ! (
		
		argc >= 2 && useProtocolOption ( argv [ 1 ], protocol ) &&
		
		argc >= 3 && useDomainOption ( argv [ 2 ], domain ) &&
		
		argc >= 4 && usePortOption ( argv [ 3 ], port ) &&
		
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
		
		! strcmp ( protocolOption, "irc" ) &&
		
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
		
		strlen ( domainOption ) < 256 &&
		
		copyStringLengthIntoString ( domainOption, 255, domain )
		
	)	return true;
	
	
	warning (
		
		"\n"
		"Unknown domain.\n"
		"\n"
		
	);
	
	return false;
	
}


int usePortOption ( char * portOption, char * port ) {
	
	debug();
	
	
	// Switch atoi to strtol?
	
	if (
		
		strlen ( portOption ) < 256 &&
		
		atoi ( portOption ) >= 0 &&
		
		copyStringLengthIntoString ( portOption, 255, port )
		
	)	return true;
	
	
	warning (
		
		"\n"
		"Not a port.\n"
		"\n"
		
	);
	
	return false;
	
}