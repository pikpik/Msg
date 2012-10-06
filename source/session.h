#if !defined(session_h)

# define session_h

void editMessage ( int connection, char * buffer );

void runLoop ( int connection );

void session ( char * domain, int port );

#endif
