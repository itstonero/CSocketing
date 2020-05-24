#include <window_manager.h>

int main() 
{
    WindowSocket socket_manager = new_WindowSocket();
    
    WindowParam * datum = (WindowParam *)calloc(1, sizeof(WindowParam));

    socket_manager.initiate_client(datum);
    socket_manager.connect(datum);
    freeaddrinfo(datum->result);

    if (datum->ConnectSocket == INVALID_SOCKET) 
    {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }
    
    // socket_manager.shutdown(datum); // shutdown the connection since no more data will be sent

    do 
    {
        socket_manager.send_to_host(datum);
        
        socket_manager.receive_from_host(datum);

    } while(datum->iResult > 0 ); // Receive until the peer closes the connection

    socket_manager.close_client(datum); // cleanup

    return 0;
}