//
//Main.cpp
//(C) ramsey 2006
//
//The main part. Where everything is called.
//

#include <cstdio>
#include "CoreServer.h"



int main()
{
    printf("vgoemu Dummy Char Server\n\n");

    //Load the config
    ServerSocket Server;
    Server.InitSocket(); //Init WSA on windows only.
    Server.StartServer(10100); //The StartServer function
    Server.RecvLoop(); //The Recv Loop function.

    //If the RecvLoop stops, then close the server:
    Server.CloseSocket();
    return 0;
}


