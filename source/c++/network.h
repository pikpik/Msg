#if !defined (network_h)

# define network_h

void startConnection ( char *serverAddress, int port );

void sendMessage ( char * buffer );

void newMessage ( int signal );

int receiveMessage ( void );

void endConnection ( void );

#endif
