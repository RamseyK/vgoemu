#include "packetfunctions.h"
#include "packets.h"
#include "charpackets.h"
#include "CoreServer.h"
#include <cstdio>

extern client_object oclient;

void send_hardcode_pkt(ServerSocket *Server,char *pkt,unsigned short size)
{
     char *packet = new char [size];
     memcpy(packet,pkt,size);
     *(char*)(packet) = oclient.server_sequence+1;
     oclient.server_sequence = oclient.server_sequence+1;
     Server->SendVGO(packet,size);
     delete [] packet;
}


void ack_seq(ServerSocket *Server, char seq) {
     char *packet = new char [6];
     memcpy(packet,ackseq_segment,6);
     *(char*)(packet) = oclient.server_sequence+1;
     oclient.server_sequence = oclient.server_sequence+1;
     *(char*)(packet+2) = oclient.server_sequence - 1;
     *(char*)(packet+4) = oclient.client_sequence;
     Server->SendVGO(packet,6);
     delete [] packet;
}


//////////////////////
//LOGINSTUFF
//////////////////////

void send_LOGINRESP(ServerSocket *Server)
{
     char *packet = new char [sizeof(SMSG_LOGINRESP)];
     memcpy(packet,SMSG_LOGINRESP,sizeof(SMSG_LOGINRESP));
     Server->SendVGO(packet,sizeof(SMSG_LOGINRESP));
     delete [] packet;
}


void send_LOGININFORESP(ServerSocket *Server)
{
   send_hardcode_pkt(Server, SMSG_LOGININFORESP, sizeof(SMSG_LOGININFORESP));   
}

void send_SERVLIST(ServerSocket *Server)
{
     send_hardcode_pkt(Server, SMSG_SERVLIST, sizeof(SMSG_SERVLIST));
}



///////////////
//CHAR STUFF:
//////////////









