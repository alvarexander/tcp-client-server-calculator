# TCP-Client-Server-Calculator
A networking program using the TCP protocol in the C language that works as a calculator between server and client.
To run the program on the same machine open two separate terminal windows.

Server: 
1. gcc server.c -o server
2. ./server

Client:
1. gcc client.c -o client
2. ./client 127.0.0.1
3. Then proceed to type in any expression without space such as: "15+5"
4. The answer will be sent from the server as: "Answer from the server:20".

Notes:
+ Plese enter your input without any spaces in between.
+ Please don't forget to add the local host IP 127.0.0.1 when running your client.
+ Typing in 0/0 will close the connection and end both programs.
+ The port used is 9898 and is closed when the program ends.
+ Entering just a number will yield a value of 0.
+ A null received on the server side indicates the users intent to end the program by typing in 0/0.
