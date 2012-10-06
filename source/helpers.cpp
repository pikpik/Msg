#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "helpers.h"


void error ( const char *msg ) {

  perror ( msg );

  exit ( 1 );

}
