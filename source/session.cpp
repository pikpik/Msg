#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "network.h"
#include "session.h"


using namespace std;


void editMessage ( int connection, char * buffer ) {

  printf ( " > " );

  bzero ( buffer, 256 );

  fgets ( buffer, 255, stdin );

  sendMessage ( connection, buffer );

}


void runLoop ( int connection ) {

  // Separate buffers should probably be used
  // for sending and receiving.

  char buffer [ 256 ];


  while ( true ) {

    // Let the user write and send something.

    editMessage ( connection, buffer );


    // Show what the server says in response.

    while ( receiveMessage ( connection, buffer ) )

      printf ( "%s\n", buffer );

  }


  // In the future, this should be done asynchronously.
  // When data's available, it should be displayed
  // and the interface should be redrawn.
  // NCurses might help for that.

}


void session ( char * domain, int port ) {

  // Start the connection to the server.

  int connection = startConnection ( domain, port );


  // Later this might involve reading, writing, or interacting,
  // depending on what's specified.

  runLoop ( connection );


  // For lack of a better way.

  endConnection ( connection );

}
