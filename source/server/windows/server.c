#include <window_manager.h>


int __cdecl main(void) 
{
    WindowSocket socket_manager = new_WindowSocket();

    WindowParam * datum = (WindowParam *)calloc(1, sizeof(WindowParam));

    socket_manager.initiate_server(datum);
    socket_manager.listen(datum);
    socket_manager.accept(datum);



    freeaddrinfo(datum->result);
    // No longer need server socket
    closesocket(datum->ListenSocket);

    // Receive until the peer shuts down the connection
    do 
    {
        socket_manager.receive_from_client(datum);
        socket_manager.send_to_client(datum);
    } while (datum->iResult > 0);


    socket_manager.shutdown_server(datum);    // shutdown the connection since we're done
    socket_manager.close_server(datum);

    return 0;
}