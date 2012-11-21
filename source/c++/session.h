#if !defined(session_h)

# define session_h

extern int waiting;

void editMessage ( int connection, char * buffer );

void showNewMessage ( char * inbox );

void runLoop ( int connection );

void session ( char * domain, int port );

#endif
