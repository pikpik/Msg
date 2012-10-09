#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>

#include "network.h"
#include "signals.h"
#include "session.h"


using namespace std;


char outbox [ 256 ];


// Use this to stop.

int waiting = 1;


void editMessage ( void ) {

  printf ( " > " );

  bzero ( outbox, 256 );

  fgets ( outbox, 255, stdin );

  sendMessage ( outbox );

}


void showNewMessage ( char * inbox ) {

  printf ( "%s", inbox );

}


void runLoop ( void ) {


  // Make two sets of signals.

  sigset_t listeningSignals, allSignals;


  // Say which signals we're listening for.

  sigemptyset ( & listeningSignals );

  sigaddset ( & listeningSignals, SIGIO );

  sigaddset ( & listeningSignals, SIGUSR1 );


  // Begin the "critical section" by ignoring our signals until we're suspended.

  sigprocmask ( SIG_BLOCK, & listeningSignals, & allSignals );


  //memmove ( outbox, "GET /", 5 );
  //sendMessage ( outbox );

  editMessage ();


  // Wait and respond to events.

  while ( waiting ) {

    // Let the user write and send something.

    //editMessage ();


    // Show what the server says in response.

    // http://en.wikibooks.org/wiki/Serial_Programming/termios


    // Ignore all other signals while we wait.
    // The previously blocked signals are unblocked.

    sigsuspend ( & allSignals );

  }


  // This ends the "critical section" by listening to signals normally again.

  sigprocmask ( SIG_UNBLOCK, & listeningSignals, NULL );


  // In the future, this should be done asynchronously.

  // When data's available, it should be displayed
  // and the interface should be redrawn.

}


void session ( char * domain, int port ) {

  // Start the connection to the server.

  startConnection ( domain, port );


  // Later this might involve reading, writing, or interacting,
  // depending on what's specified.

  runLoop ();


  endConnection ();

}
