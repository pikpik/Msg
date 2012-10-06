#include <unistd.h>
#include <signal.h>


void responseForSignal ( void (* action) (int), int signal ) {

        struct sigaction signalResponse;


        // Have the responder ignore all signals.

        sigset_t ignoredSignals;

        sigfillset ( & ignoredSignals );


        // Get ready.

        // The responder should ignore all signals,
        // use the function,
        // and then start listening again.

        signalResponse.sa_handler = action;

        signalResponse.sa_mask = ignoredSignals;

        signalResponse.sa_flags = SA_RESTART;


        // Listen for the signal.

        sigaction ( signal, & signalResponse, NULL );

}
