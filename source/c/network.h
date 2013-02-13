// Included things

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/fcntl.h>

#include "helpers.h"


// Functions

int openConnection ( string domain, string port );

void onNetworkMessage ( int connection, int events );

void putMessageInOutbox ( char * message );

void sendMessage ( int connection );

int receiveMessage ( int connection );