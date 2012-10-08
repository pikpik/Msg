#include <iostream>

#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/fcntl.h>

#include "helpers.h"
#include "signals.h"
#include "session.h"
#include "network.h"


using namespace std;


int connection;

char inbox [ 256 ];


void startConnection ( char *serverAddress, int port ) {

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


  // Let's read from the "file," or socket, asynchronously.

  fcntl ( connection, F_SETOWN, ( int ) getpid ( ) );

  fcntl ( connection, F_SETFL, FASYNC | O_NONBLOCK );


  // Say that we'll listen for I/O messages (from the socket, hopefully).

  responseForSignal ( newMessage, SIGIO );

}


void sendMessage ( char * buffer ) {

  int result = write ( connection, buffer, strlen ( buffer ) );

  if ( result < 0 )

    error ( "Unable to send messages." );

}


void newMessage ( int signal ) {

  while ( receiveMessage () )

    showNewMessage ( inbox );

}


int receiveMessage ( void ) {

  bzero ( inbox, 256 );

  int result = read ( connection, inbox, 255 );

  /* Do we really need this anyway?
  if ( result < 0 )

    cout << "Unable to listen for messages (error code " << result << ")." << endl;
  */

  return result;

}


void endConnection ( void ) {

  close ( connection );

}
