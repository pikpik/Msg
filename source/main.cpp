#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;

void error ( const char *msg ) {

  perror ( msg );

  exit ( 1 );

}


int startConnection ( char *serverAddress, int port ) {

  int connection;

  struct sockaddr_in serverIPAddress;

  struct hostent *server;


  connection = socket ( AF_INET, SOCK_STREAM, 0 );

  if ( connection < 0 )

    error ( "Unable to start a connection." );


  server = gethostbyname ( serverAddress );

  if ( server == NULL )

    error ( "Unable to find specified server." );


  bzero (

    ( char * ) &serverIPAddress,

    sizeof ( serverIPAddress )

  );

  bcopy (

    ( char * ) server->h_addr,

    ( char * ) &serverIPAddress.sin_addr.s_addr,

    server->h_length

  );


  serverIPAddress.sin_family = AF_INET;

  serverIPAddress.sin_port = htons ( port );


  int result;

  if (

    result = connect (

      connection,

      ( struct sockaddr * ) &serverIPAddress,

      sizeof ( serverIPAddress )

    ) < 0

  )

    error ( "Unable to connect to the server." );


  return connection;

}


void sendMessage ( int connection, char *buffer ) {

  int result = write ( connection, buffer, strlen ( buffer ) );

  if ( result < 0 )

    error ( "Unable to send messages." );

}


int receiveMessage ( int connection, char *buffer ) {

  bzero ( buffer, 256 );

  int result = read ( connection, buffer, 255 );

  if ( result < 0 )

    cout << "Unable to listen for messages." << endl;

  return result;

}


void editMessage ( int connection, char *buffer ) {

  printf ( " > " );

  bzero ( buffer, 256 );

  fgets ( buffer, 255, stdin );

  sendMessage ( connection, buffer );

}


void manageActivity ( int connection ) {

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


void showUsage ( char *name ) {

  fprintf ( stderr, "Usage: %s hostname port\n", name );

  exit ( 0 );

}



int main ( int argc, char *argv[] ) {

  // I'd like to switch printf's to C++ idioms.
  // cout << "Hello World!" << endl;


  // Are the program name, domain, and port set?

  if ( argc < 3 )

    showUsage ( argv [ 0 ] );


  // Let's get the options.

  char *domain = argv [ 1 ];

  int port = atoi ( argv [ 2 ] );


  // Start the connection to the server.

  int connection = startConnection ( domain, port );

  // Later this might involve reading, writing, or interacting,
  // depending on what's specified.

  manageActivity ( connection );

  // For lack of a better way.

  close ( connection );


  return 0;

}
