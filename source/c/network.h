// Included things

#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/fcntl.h>


// Functions

int openConnection ( char * domain, int port );

void sendMessage ( int connection, char * buffer );

void newMessage ( int connection, int events );

int receiveMessage ( int connection );