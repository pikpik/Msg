// Included things

#include "helpers.h"

// Global

extern string nickname;

// Functions

void startIRCSession ( void );

void interpretIRCCommand ( string message );

void IRCJoinCommand ( string parsedMessage );

void IRCMsgCommand ( string parsedMessage );

void verbatimIRCCommand ( string command );

void IRCOnCommand ( string channel );

void sendIRCMessage ( string message );

void sendPrivateIRCMessageToRecipient ( string newMessage, string recipient );