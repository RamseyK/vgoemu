#ifndef PACKETFUNCTIONS_H
#define PACKETFUNCTIONS_H

class ServerSocket;

void send_hardcode_pkt(ServerSocket *Server,char *pkt,unsigned short size);
void ack_seq(ServerSocket *Server, char seq);


//LOGIN FUNCTIONS:
void send_LOGINRESP(ServerSocket *Server);
void send_LOGININFORESP(ServerSocket *Server);
void send_SERVLIST(ServerSocket *Server);



//CHAR TRANS FUNCTIONS
void send_CHARWINDOWTEXT1_RESP(ServerSocket *Server);
void send_SERVERTRANSFER(ServerSocket *Server);

#endif
