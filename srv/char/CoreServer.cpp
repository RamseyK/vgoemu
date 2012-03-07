//
//CoreSocket.cpp
//(C) SWGEmu 2006
//
//Main Socket Operations such as Starting, Sending, and Recv'ing.
//

#include "CoreServer.h"
#include "packetfunctions.h"
#include <stdio.h>

client_object oclient;


ServerSocket::ServerSocket( )
{
    Socket  = INVALID_SOCKET;
}


ServerSocket::~ServerSocket( )
{
}


//Server Init Function. Init winsock on windows. Called only on windows.
void ServerSocket::InitSocket (void) //Init socket, WSA Startup (windows only)
{
    WSADATA wsa;
    memset(&wsa, 0x0, sizeof(WSADATA));
    if(WSAStartup(MAKEWORD(2,0),&wsa) != 0x0)
    {
        printf("WSAStartup failed!\n");
    }
}





//The StartServer Function
//Used for Starting the server (Binding, Listening, etc.)
void ServerSocket::StartServer(unsigned short Port)
{

    Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if ( Socket==INVALID_SOCKET ) //If theres a problem :(  then report it :)
    {
        printf("Socket() fail\n");
    }
    mode = 0; //0 = Blocking, 1 = NonBlocking

    //Set the ioctl mode.
    ret = ioctlsocket(Socket, FIONBIO, &mode );

    if(ret < 0)
    { //If theres a problem, report it and then close the server.
        CloseSocket();
        Socket = INVALID_SOCKET;
        printf("Ioctl FIBIO (Blocking Mode) failed!\n");
    }
    memset(&ain, 0, sizeof(ain)); // Clear struct
    ain.sin_family = AF_INET;
    ain.sin_addr.s_addr = INADDR_ANY;
    ain.sin_port = htons(Port); //sets port

    // Bind the server socket
    if (bind(Socket, (struct sockaddr *)&ain, sizeof(ain)) < 0)
    {
        CloseSocket();
        Socket = INVALID_SOCKET;
        printf("Server Bind Failed!\n");
    }

    oclient.client_sequence = 0;
    oclient.server_sequence = 0;

    printf("Server Start Successful! Listening on port %d \n",(unsigned short)Port);
}






//The CloseSocket function.
//This should be called whenever shutting down the server.
//Closes the socket and runs wsacleanup for windows.
void ServerSocket::CloseSocket( void ) //Close Socket
{
    close(Socket); //Otherwise, close the socket
#ifdef WIN32
    //closesocket(Socket); //Closes Socket
    WSACleanup(); //The Clean up, not required but makes things much faster.
#endif

    Socket = INVALID_SOCKET; //Prepares it just incase the socket is to be started up again. used to catch errors on startup.
    printf("Server Closed Successfully!\n");
}






//The RecvLoop Function aka MainLoop
//Used for picking up incomming packets then passing them to the handler
void ServerSocket::RecvLoop()
{
    char Buffer[MAX_BUF]; //leik omfg fixed

    int clientlen = sizeof(cclient);
    //This loop will check for incomming packets, and pass them off to the handler.

    do
    {
        unsigned short len = 0;
        len = recvfrom(Socket, Buffer, MAX_BUF, 0, (struct sockaddr*)&cclient, &clientlen);
        //insert handlers heree~!
        HandlePacket(Buffer,len);
        //ServerSocket::UDPSendPacket(Buffer, sizeof(Buffer), Port);
    }
    while (1==1); //Keep going
}

void ServerSocket::HandlePacket(char *pData, unsigned short nLength)
{
    /*unsigned int *headerack = (unsigned int*)(pData+2);
    unsigned int *headerack2 = (unsigned int*)(pData+4);
    unsigned int *headerack3 = (unsigned int*)(pData+6);
    unsigned int *headerack4 = (unsigned int*)(pData+8);

    if(*headerack == 0x80) {
    pData+=2;
    printf("Handler: 80 header1\n");
    }

    if(*headerack == 0x00) {
    pData+=2;
    printf("Handler: 00 header1\n");
    }

    if(*headerack2 == 0x80) {
    pData+=2;
    printf("Handler: 80 header2\n");
    }

    if(*headerack3 == 0x80) {
    pData+=2;
    printf("Handler: 80 header3\n");
    }

    if(*headerack4 == 0x80) {
    pData+=2;
    printf("Handler: 80 header4\n");
    }*/


    unsigned char *header1 = (unsigned char*)(pData+3); //2
    unsigned char *header2 = (unsigned char*)(pData+5); //4
    unsigned char *header3 = (unsigned char*)(pData+7); //6
    unsigned char *header4 = (unsigned char*)(pData+9); //8
    unsigned char *header5 = (unsigned char*)(pData+11); //10
    unsigned char *header6 = (unsigned char*)(pData+13); //12
    unsigned char *header7 = (unsigned char*)(pData+15); //14
    unsigned char *header8 = (unsigned char*)(pData+17); //16
    unsigned char *header9 = (unsigned char*)(pData+19); //18
    unsigned char *header10 = (unsigned char*)(pData+21); //20
    unsigned char *header11 = (unsigned char*)(pData+23); //22
    unsigned char *header12 = (unsigned char*)(pData+25); //24
    unsigned char *header13 = (unsigned char*)(pData+17); //26

    int count = 0;

    if(*header1 == 0x80)
    {
        count = count + 2;
        
    if(*header2 == 0x00)
    {
        count = count + 0;
    }
    
    }

    if(*header2 == 0x80)
    {
        count = count + 2;
        
    if(*header3 == 0x00)
    {
        count = count + 0;
    }
    
    }

    if(*header3 == 0x80)
    {
            count = count + 2;        
            
    if(*header4 == 0x00)
    {
        count = count + 0;
    }
    
    }

    if(*header4 == 0x80)
    {
            count = count + 2;        
            
    if(*header5 == 0x00)
    {
        count = count + 0;
    }
    
    }
    
    
    if(*header5 == 0x80)
    {
            count = count + 2;        
            
    if(*header6 == 0x00)
    {
        count = count + 0;
    }
    
    }
    
    
    if(*header6 == 0x80)
    {
            count = count + 2;       
          
    if(*header7 == 0x00)
    {
        count = count + 0;
    }
    
    }
    
    
    if(*header7 == 0x80)
    {
            count = count + 2;
            
    if(*header8 == 0x00)
    {
        count = count + 0;
    }
    
    }    
    
    if(*header8 == 0x80)
    {
            count = count + 2;
            
    if(*header9 == 0x00)
    {
        count = count + 0;
    }
    
    }    
    
    if(*header9 == 0x80)
    {
            count = count + 2;
            
    if(*header10 == 0x00)
    {
        count = count + 0;
    }
    
    }    
    
    if(*header10 == 0x80)
    {
            count = count + 2;
            
    if(*header11 == 0x00)
    {
        count = count + 0;
    }
    
    }    
    
    if(*header11 == 0x80)
    {
            count = count + 2;
            
    if(*header12 == 0x00)
    {
        count = count + 0;
    }
    
    }    
    
    if(*header12 == 0x80)
    {
            count = count + 2;
            
    if(*header13 == 0x00)
    {
        count = count + 0;
    }
    
    }
    

    unsigned int *opcode = (unsigned int*)(pData+(count+4));
    
    count = 0;

    switch(*opcode)
    {
        //LOGIN CASE:
        case 0x61382002: //02 20 38 61 CMSG_LOGINREQ
        printf("Handler: 02 20 38 61 CMSG_LOGINREQ\n");
        send_LOGINRESP(this);
        break;

        case 0x3C560801: //01 08 56 3C CMSG_LOGININFO
        printf("Handler: 01 08 56 3C CMSG_LOGININFO\n");
        send_LOGININFORESP(this);
        oclient.client_sequence = *(char*)pData;
        ack_seq(this, oclient.client_sequence);
        break;

        case 0xB0B22002: //02 20 B2 B0 SERVERLIST
        //THIS ISNT THE RIGHT WAY TO ID OPCODES - LOOK INTO LATERRR
        printf("Handler: 02 20 B2 B0 SERVERLISTREQ\n");
        send_SERVLIST(this);
        oclient.client_sequence = *(char*)pData;
        ack_seq(this, oclient.client_sequence);
        break;

        //CHAR CASE:





        ///

        default:
        if(nLength > 6)
        {
            printf("Handler: Unknown opcode: ");
            hex_print((char*)opcode, 4);
            oclient.client_sequence = *(char*)pData;
            ack_seq(this, oclient.client_sequence);
            if(nLength > 512)
            {
                this->hex_print(pData, 512);
                printf("packet over 512 bytes recv'd, please log chk\n");
            }

            else
            {
                this->hex_print(pData, nLength);
            }

        } //nlength check
        break; //break default

    } //end switch opcode
} //end function

void ServerSocket::SendVGO(char *pData,unsigned short nLength)
{
    //IF ANYTHING special needs to be done with the packet later on , do it here
    UDPSendPacket(pData,nLength);
}


//The UDPSendPacket Function
//Used just for sending a udp packet
void ServerSocket::UDPSendPacket(char* Data, unsigned short len)
{
    //Example of usage: ServerSocket::UDPSendPacket(Buffer, 2, Port);
    int clientlen = sizeof(cclient);
    sendto(Socket, Data, len, 0, (struct sockaddr*)&cclient,clientlen);
}

void ServerSocket::hex_print(char* data, int length)
{
    for(int i = 0; i < length; i++)
    {
        printf("0x%02x ",(unsigned char)*(data+i));
    }
    printf("\n");
}

void ServerSocket::ascii_to_unicode(wchar_t *destination, char *source, int length)
{
    for(int i=0; i < length; i++)
        destination[i] = source[i];
}

void ServerSocket::unicode_to_ascii(char *destination, wchar_t *source, int length)
{
    for(int i=0; i < length; i++)
        destination[i] = source[i];
}
