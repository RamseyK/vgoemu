//
//CoreSocket.h
//(C) SWGEmu 2006
//
//Header file for the serversocket & main.cpp source files.
//

#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#define MAX_BUF 512

//#include <windows.h>
#include <winsock2.h>
#define close closesocket


typedef struct client_object
{
unsigned char server_sequence;
unsigned char client_sequence;
int opup;
};

//The ServerSocket Class.
//Used for all the Server's Socket Functions.
class ServerSocket// : public CoreSocket
{
public:
	ServerSocket();
	~ServerSocket();

	SOCKET			Socket;				//Socket
    void InitSocket (void);
    void CloseSocket(void);
	void StartServer		(unsigned short Port);	//Server Start function
	void ServerMainLoop		( void );					// Mainloop
	void RecvLoop();
	void UDPSendPacket (char* Data, unsigned short len);
	struct sockaddr_in ain, cclient;
	void HandlePacket(char *pData, unsigned short nLength);
    void SendVGO(char *pData,unsigned short nLength);
    void ascii_to_unicode(wchar_t *destination, char *source, int length);
    void unicode_to_ascii(char *destination, wchar_t *source, int length);
    void hex_print(char* data, int length);
protected:
	int ret; //Used for blocking modes
	//For setting the blocking mode.
	unsigned long mode;
};

#endif

