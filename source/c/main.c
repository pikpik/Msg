// Included things

#include "main.h"

#include "terminal.h"
#include "network.h"
#include "helpers.h"
#include "events.h"
#include "irc.h"


// Begin

int main ( int argc, string argv [] ) {
	
	debug();
	
	
	// Get ready
	
	// string nickname is global.
	
	string domain;
	
	string port;
	
	awaken ();
	
	
	// What are we supposed to do?
	
	if ( ! (
		
		useNicknameOption ( argc, argv, 1, & nickname ) &&
		
		useDomainOption ( argc, argv, 2, & domain ) &&
		
		usePortOption ( argc, argv, 3, & port ) &&
		
		chatWithProtocolToServer (
			
			openConnection ( domain, port )
			
		)
		
	) ) help ();
	
	
	return 0;
	
}


// Functions

bool optionExists ( int argc, int number ) {
	
	return ( argc >= number + 1 );
	
}


bool badString ( int argc, string argv [], int number ) {
	
	return (
				! optionExists ( argc, number )
			
			||	strlen ( argv [ number ] ) >= 256
	);
	
}


bool useNicknameOption ( int argc, string argv [], int number, string * nickname ) {
	
	if ( badString ( argc, argv, number ) ) {
		
		warning (
			
			"\n"
			"Sorry, that's not a valid nickname.\n"
			"\n"
			
		);
		
		return false;
		
	}
	
	* nickname = argv [ number ];
	
	return true;
	
}


bool useDomainOption ( int argc, string argv [], int number, string * domain ) {
	
	if ( badString ( argc, argv, number ) ) {
		
		warning (
			
			"\n"
			"Sorry, I don't think that's a valid server name.\n"
			"\n"
			
		);
		
		return false;
		
	}
	
	* domain = argv [ number ];
	
	return true;
	
}


bool usePortOption ( int argc, char * argv [], int number, string * port ) {
	
	if ( badString ( argc, argv, number ) ) {
		
		warning (
			
			"\n"
			"Sorry, that's not a valid.\n"
			"\n"
			
		);
		
		return false;
		
	}
	
	* port = argv [ number ];
	
	return true;
	
}


bool chatWithProtocolToServer ( int connection ) {
	
	debug();
	
	startUsingTerminal ( STDIN_FILENO );
	
	startIRCSession ();
	
	runLoop ();
	
	stopUsingTerminal ( STDIN_FILENO );
	
	close ( connection );
	
	return true;
	
}