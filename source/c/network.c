// Included things

#include "helpers.h"
#include "events.h"
#include "network.h"


// Globals

int connection;


char inbox [ 256 ];


// Functions

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


	when ( connection, EventReadable | EventFailed, & newMessage );

}


void sendMessage ( char * buffer ) {

  int result = write ( connection, buffer, strlen ( buffer ) );

  if ( result < 0 )

    error ( "Unable to send messages." );

}


void newMessage ( int connection, int events ) {

  if ( events & EventReadable ) {
	  
    int response;


    while ( ( response = receiveMessage () ) > 0 )

      showNewMessage ( inbox );


    if ( response == 0 )

      waiting = 0;

  }

  if ( events & EventReadable ) {

    error ( "I couldn't get a message from the network." );

  }

}


int receiveMessage ( void ) {

  memset ( & inbox, 0, sizeof inbox );

  return read ( connection, inbox, 255 );

}


void endConnection ( void ) {

  close ( connection );

}
