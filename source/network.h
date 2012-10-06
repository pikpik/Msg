#if !defined (network_h)

# define network_h

int startConnection ( char *serverAddress, int port );

void sendMessage ( int connection, char *buffer );

int receiveMessage ( int connection, char *buffer );

int endConnection ( int connection );

#endif
