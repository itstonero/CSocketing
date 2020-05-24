#include "window_manager.h"

int initiate_server(WindowParam * param)
{
    return 0;
}

int initiate_client(WindowParam * param)
{
    return 0;
}


int listen(WindowParam * param)
{
    return 0;
}

int accept(WindowParam * param)
{
    return 0;
}

int connect(WindowParam * param)
{
    return 0;
}


int send(WindowParam * param)
{
    return 0;
}

int receive(WindowParam * param)
{
    return 0;
}


int close_server(WindowParam * param)
{
    return 0;
}

int close_client(WindowParam * param)
{
    return 0;
}


WindowSocket new_WindowSocket()
{
    WindowSocket socket;

    socket.accept = accept;
    socket.close_client = close_client;
    socket.close_server = close_server;

    socket.connect = connect;
    socket.initiate_client = initiate_client;
    socket.initiate_server = initiate_server;

    socket.listen = listen;
    socket.receive = receive;
    socket.send = send;

    return socket;
}