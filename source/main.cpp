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


void showUsage ( char * name ) {

  fprintf ( stderr, "Usage: %s host port\n", name );

  exit ( 0 );

}


int main ( int argc, char * argv [] ) {

  // Are the program name, domain, and port set?

  if ( argc < 3 )

    showUsage ( argv [ 0 ] );


  // Let's get the options.

  char * domain = argv [ 1 ];

  int port = atoi ( argv [ 2 ] );


  // Start the connection to the server.

  session ( domain, port );


  return 0;

}
