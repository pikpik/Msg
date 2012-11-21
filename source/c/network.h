// Included things

#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/fcntl.h>


// Functions

void startConnection ( char *serverAddress, int port );

void sendMessage ( char * buffer );

void newMessage ( int signal );

int receiveMessage ( void );

void endConnection ( void );