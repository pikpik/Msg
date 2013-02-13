// Included things

#include "interface.h"

#include "network.h"
#include "events.h"
#include "terminal.h"
#include "helpers.h"
#include "irc.h"


// Global variables

string nickname;

string currentChannel;

/*

 I could also add logging and channel paging.
 
 But what's the point of this: a complete IRC client or a protocol utility?

int channelPosition = -1;

*/


// Functions

void startIRCSession ( void ) {
	
	char firstMessages [ 256 ];
	
	memset ( firstMessages, '\0', 256 );
	
	appendStringToStringToLimit ( "USER ", firstMessages, 255 );
	appendStringToStringToLimit ( nickname, firstMessages, 255 );
	appendStringToStringToLimit ( " * * :", firstMessages, 255 );
	appendStringToStringToLimit ( nickname, firstMessages, 255 );
	appendStringToStringToLimit ( "\n", firstMessages, 255 );
	
	appendStringToStringToLimit ( "NICK ", firstMessages, 255 );
	appendStringToStringToLimit ( nickname, firstMessages, 255 );
	appendStringToStringToLimit ( "\n", firstMessages, 255 );
	
	putMessageInOutbox ( firstMessages );
	
}


void interpretIRCCommand ( string message ) {
	
	string parsedMessage = message;
	
	string command = stringSeparatedFromString ( " \t", & parsedMessage );
	
	if ( ! command ) return;
	
	
	if ( sameStrings ( command, "/join" ) )
		
		IRCJoinCommand ( parsedMessage );
		
	else if ( sameStrings ( command, "/msg" ) )
		
		IRCMsgCommand ( parsedMessage );
		
	else
		
		verbatimIRCCommand ( message );
	
	
	clearMessage ();
	
}


void IRCJoinCommand ( string parsedMessage ) {
	
	string channel = stringSeparatedFromString ( " \t", & parsedMessage );
	
	if ( ! channel ) return;
	
	
	char joinMessage [ 256 ];
	
	memset ( joinMessage, '\0', 256 );
	
	appendStringToStringToLimit ( "JOIN ", joinMessage, 255 );
	appendStringToStringToLimit ( channel, joinMessage, 255 );
	
	putMessageInOutbox ( joinMessage );
	
}


void IRCMsgCommand ( string parsedMessage ) {
	
	string recipient = stringSeparatedFromString ( " \t", & parsedMessage );
	
	if ( ! recipient ) return;
	
	if ( ! parsedMessage ) return;
	
	addMessageToScreen ();
	
	sendPrivateIRCMessageToRecipient ( parsedMessage, recipient );
	
}


void verbatimIRCCommand ( string command ) {
	
	addMessageToScreen ();
	
	// Start just after the first "/" character.
	
	putMessageInOutbox ( ( command + 1 ) );
	
}


void IRCOnCommand ( string channel ) {
	
	currentChannel = channel;
	
}


void sendIRCMessage ( string message ) {

	sendPrivateIRCMessageToRecipient ( message, currentChannel );

}


void sendPrivateIRCMessageToRecipient ( string newMessage, string recipient ) {
	
	
	// Send the message.
	
	// Send: PRIVMSG (channel) :(message)
	
	char privateMessage [ 256 ];
	
	memset ( privateMessage, '\0', 256 );
	
	appendStringToStringToLimit ( "PRIVMSG ", privateMessage, 255 );
	appendStringToStringToLimit ( recipient, privateMessage, 255 );
	appendStringToStringToLimit ( " :", privateMessage, 255 );
	appendStringToStringToLimit ( newMessage, privateMessage, 255 );
	
	putMessageInOutbox ( privateMessage );
	
}