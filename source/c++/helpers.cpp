#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"


void error ( const char *msg ) {

  perror ( msg );

  exit ( 1 );

}
