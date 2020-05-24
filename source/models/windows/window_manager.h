#ifndef WINDOW_MANAGER_MODEL
#define WINDOW_MANAGER_MODEL

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

typedef struct window_param
{
    WSADATA wsaData;
    SOCKET ConnectSocket;
    struct addrinfo *result, *ptr, hints;
    char *sendbuf;
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    char host_address[20];

    SOCKET ListenSocket;
    SOCKET ClientSocket;

    int iSendResult;
    int recvbuflen;

}WindowParam;

typedef struct window_manager
{
    int (*initiate_server)(WindowParam *);
    int (*initiate_client)(WindowParam *);

    int (*listen)(WindowParam *);
    int (*accept)(WindowParam *);
    int (*connect)(WindowParam *);

    int (*shutdown_client)(WindowParam *);
    int (*shutdown_server)(WindowParam *);
    
    int (*send_to_host)(WindowParam *);
    int (*receive_from_host)(WindowParam *);

    int (*send_to_client)(WindowParam *);
    int (*receive_from_client)(WindowParam *);

    int (*close_server)(WindowParam *);
    int (*close_client)(WindowParam *);
}WindowSocket;

WindowSocket new_WindowSocket();

#endif