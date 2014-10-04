Ayvu Protocol 1.0

C: Sender (Client)
S: Receiver (Server)

Literal - Literal
<var> Mandatory
[var] Optional
//Comments (do not send it!)

= Session =

1. Calling

	=== Client ===
	
		INVITE <type> <Protocol Version> \r\n
		USER: <sender@_IP> \r\n
		HOST: host \r\n
		CALL-ID: <uuid>\r\n
		\r\n
		
	=== Server ===
	
		ACCEPT <type> <Protocol Version> \r\n
		USER: <receiver@_IP> \r\n
		HOST: host:port \r\n  //media host
		CALL-ID: <uuid> \r\n
		\r\n
		
		==== or ====
		
		REJECT <type> <Protocol Version> \r\n
		USER: <sender@_IP> \r\n
		HOST: host \r\n
		CALL-ID: <uuid> \r\n
		CAUSE: <Cause> \r\n
		\r\n
	
	=== Client ===
	
		CALLING <type> <Protocol Version> \r\n
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

	=== Client ===
	
		FINISH <type> <Protocol Version> \r\n
		USER: <sender@_IP> \r\n
		HOST: host \r\n
		CALL-ID <uuid> \r\n
		\r\n
		
Type:
	Audio
	Video

Cause (case insensitive)
	Calling (Calling someone)
	Talking (Talking with someone)
	Incomming (Receiving a call)
	Busy (Default)
	
= DATA =









	