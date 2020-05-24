#include "window_manager.h"

int initiate_server(WindowParam * param)
{

    param->ListenSocket = INVALID_SOCKET;
    param->ClientSocket = INVALID_SOCKET;
    param->result = NULL;
    char recvbuf[DEFAULT_BUFLEN];
    param->recvbuflen = DEFAULT_BUFLEN;
    
    // Initialize Winsock
    param->iResult = WSAStartup(MAKEWORD(2,2), &param->wsaData);
    if (param->iResult != 0) 
    {
        printf("WSAStartup failed with error: %d\n", param->iResult);
        return 1;
    }

    ZeroMemory(&param->hints, sizeof(param->hints));
    param->hints.ai_family = AF_INET;
    param->hints.ai_socktype = SOCK_STREAM;
    param->hints.ai_protocol = IPPROTO_TCP;
    param->hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    param->iResult = getaddrinfo(NULL, DEFAULT_PORT, &param->hints, &param->result);
    if ( param->iResult != 0 ) 
    {
        printf("getaddrinfo failed with error: %d\n", param->iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    param->ListenSocket = socket(param->result->ai_family, param->result->ai_socktype, param->result->ai_protocol);
    if (param->ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(param->result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    param->iResult = bind( param->ListenSocket, param->result->ai_addr, (int)param->result->ai_addrlen);
    if (param->iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(param->result);
        closesocket(param->ListenSocket);
        WSACleanup();
        return 1;
    }

    printf("Waiting For Connection ....\n");

    return 0;
}

int initiate_client(WindowParam * param)
{
    param->wsaData;
    param->ConnectSocket = INVALID_SOCKET;
    param->result = NULL,
    param->ptr = NULL,
    param->hints;
    param->recvbuf[DEFAULT_BUFLEN];
    param->iResult;
    param->recvbuflen = DEFAULT_BUFLEN;

    param->iResult = WSAStartup(MAKEWORD(2,2), &param->wsaData);
    if (param->iResult != 0) 
    {
        printf("WSAStartup failed with error: %d\n", param->iResult);
        return 1;
    }

    ZeroMemory( &param->hints, sizeof(param->hints) );
    param->hints.ai_family = AF_UNSPEC;
    param->hints.ai_socktype = SOCK_STREAM;
    param->hints.ai_protocol = IPPROTO_TCP;

    printf("Enter Host Address : ");
    scanf("%s", param->host_address);
    // Resolve the server address and port
    param->iResult = getaddrinfo(param->host_address, DEFAULT_PORT, &param->hints, &param->result);
    if ( param->iResult != 0 ) 
    {
        printf("getaddrinfo failed with error: %d\n", param->iResult);
        WSACleanup();
        return 1;
    }

    puts("Connecting to Server .....");

    return 0;
}

int listen_for_connection(WindowParam * param)
{
    param->iResult = listen(param->ListenSocket, SOMAXCONN);
    if (param->iResult == SOCKET_ERROR) 
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(param->ListenSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}

int accept_connection(WindowParam * param)
{
    param->ClientSocket = accept(param->ListenSocket, NULL, NULL);
    if (param->ClientSocket == INVALID_SOCKET) 
    {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(param->ListenSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}

int connect_client_to_server(WindowParam * param)
{
        for(param->ptr=param->result; param->ptr != NULL ;param->ptr=param->ptr->ai_next) 
        {

            // Create a SOCKET for connecting to server
            param->ConnectSocket = socket(param->ptr->ai_family, param->ptr->ai_socktype, param->ptr->ai_protocol);

            if (param->ConnectSocket == INVALID_SOCKET) 
            {
                printf("socket failed with error: %ld\n", WSAGetLastError());
                WSACleanup();
                return 1;
            }

            // Connect to server.
            param->iResult = connect( param->ConnectSocket, param->ptr->ai_addr, (int)param->ptr->ai_addrlen);
            if (param->iResult == SOCKET_ERROR) 
            {
                closesocket(param->ConnectSocket);
                param->ConnectSocket = INVALID_SOCKET;
                continue;
            }
            break;
        }
    return 0;
}

int send_data(WindowParam * param)
{
    char buffer[255];

    printf("ME : ");
    fflush(stdin);
    strcpy(buffer, "");
    fgets(buffer, 255, stdin);

    param->iResult = send( param->ConnectSocket, buffer, (int)strlen(buffer), 0 );
    if (param->iResult == SOCKET_ERROR) 
    {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(param->ConnectSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}

int receive_data(WindowParam * param)
{
    printf("Server : ");
    strcpy(param->recvbuf, "");

        param->iResult = recv(param->ConnectSocket, param->recvbuf, param->recvbuflen, 0);

        if ( param->iResult > 0 )
        {
            puts(param->recvbuf);
            return 0;
        }
        else if ( param->iResult == 0 )
        {
            printf("Connection closed\n");
        }else
        {
            printf("recv failed with error: %d\n", WSAGetLastError());
        }
}

int send_data_H(WindowParam * param)
{
    char buffer[255];

    printf("ME : ");
    fflush(stdin);
    strcpy(buffer, "");
    fgets(buffer, 255, stdin);

    param->iResult = send( param->ClientSocket, buffer, (int)strlen(buffer), 0 );
    if (param->iResult == SOCKET_ERROR) 
    {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(param->ClientSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}

int receive_data_H(WindowParam * param)
{
    printf("Client : ");
    strcpy(param->recvbuf, "");

    param->iResult = recv(param->ClientSocket, param->recvbuf, param->recvbuflen, 0);

    if ( param->iResult > 0 )
    {
        puts(param->recvbuf);
        return 0;
    }
    else if ( param->iResult == 0 )
    {
        printf("Connection closed\n");
    }else
    {
        printf("recv failed with error: %d\n", WSAGetLastError());
    }
}

int shutdown_connection(WindowParam * param)
{
    param->iResult = send( param->ConnectSocket, param->sendbuf, (int)strlen(param->sendbuf), 0 );
    if (param->iResult == SOCKET_ERROR) 
    {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(param->ConnectSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}

int shutdown_server(WindowParam * param)
{
    param->iResult = shutdown(param->ClientSocket, SD_SEND);
    if (param->iResult == SOCKET_ERROR) 
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(param->ClientSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}

int close_server(WindowParam * param)
{
    closesocket(param->ClientSocket);
    WSACleanup();
    if(param != NULL) free(param);
    return 0;
}

int close_client(WindowParam * param)
{
    closesocket(param->ConnectSocket);
    WSACleanup();
    if(param != NULL) free(param);

    return 0;
}


WindowSocket new_WindowSocket()
{
    WindowSocket socket;

    socket.accept = accept_connection;
    socket.close_client = close_client;
    socket.close_server = close_server;

    socket.connect = connect_client_to_server;
    socket.initiate_client = initiate_client;
    socket.initiate_server = initiate_server;

    socket.listen = listen_for_connection;
    socket.receive_from_host = receive_data;
    socket.send_to_host = send_data;

    socket.receive_from_client = receive_data_H;
    socket.send_to_client = send_data_H;

    socket.shutdown_client = shutdown_connection;
    socket.shutdown_server = shutdown_server;

    return socket;
}