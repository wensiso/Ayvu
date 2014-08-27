Ayvu Protocol 1.0

C: Sender (Client)
S: Receiver (Server)

Literal - Literal
<var> Mandatory
[var] Optional
//Comments (do not send it!)

==== Session ====

1. Calling
	C:  INVITE <type> <Protocol Version> \r\n
		USER: <sender@_IP> \r\n
		HOST: host \r\n
		CALL-ID: <uuid>\r\n
		\r\n
		
	S: 	ACCEPT <type> <Protocol Version> \r\n
		USER: <receiver@_IP> \r\n
		MEDIA-HOST: host:port \r\n
		CALL-ID <uuid> \r\n
		\r\n
		
		=== or ====
		
		REJECT <type> <Protocol Version> \r\n
		USER: <sender@_IP> \r\n
		HOST: host \r\n
		CALL-ID <uuid> \r\n
		[CAUSE <Cause> \r\n]
		\r\n
	
	C: 	CALLING <type> <Protocol Version> \r\n
		USER: <sender@_IP> \r\n
		HOST: host \r\n
		CALL-ID <uuid> \r\n
		\r\n
		==== or ====
		CANCELLING <type> <Protocol Version> \r\n
		USER: <sender@_IP> \r\n
		HOST: host \r\n
		CALL-ID <uuid> \r\n
		\r\n

2. Finishing call (on calling)
	C:	FINISH <type> <Protocol Version> \r\n
		USER: <sender@_IP> \r\n
		HOST: host \r\n
		CALL-ID <uuid> \r\n
		\r\n
		
Type:
	Audio
	//Video

Cause:
	Calling (Calling someone)
	Talking (Talking with someone)
	Incomming (Receiving a call)
	Busy (Default)
	
==== DATA ====









	