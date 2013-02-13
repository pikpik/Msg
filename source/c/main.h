// Included things

#include <stdio.h>
#include <stdbool.h>

#include "helpers.h"


// Begin

int main ( int argc, string argv [] );


// Functions

bool optionExists ( int argc, int number );

bool badString ( int argc, string argv [], int number );

bool useNicknameOption ( int argc, string argv [], int number, string * nickname );

bool useDomainOption ( int argc, string argv [], int number, string * domain );

bool usePortOption ( int argc, char * argv [], int number, string * port );

bool chatWithProtocolToServer ( int connection );