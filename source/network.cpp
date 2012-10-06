#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "helpers.h"
#include "network.h"


using namespace std;


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


int endConnection ( int connection ) {

  return close ( connection );

}
