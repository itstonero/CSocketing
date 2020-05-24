#ifndef WINDOW_MANAGER_MODEL
#define WINDOW_MANAGER_MODEL

typedef struct window_param
{

}WindowParam;

typedef struct window_manager
{
    int (*initiate_server)(WindowParam *);
    int (*initiate_client)(WindowParam *);

    int (*listen)(WindowParam *);
    int (*accept)(WindowParam *);
    int (*connect)(WindowParam *);

    int (*send)(WindowParam *);
    int (*receive)(WindowParam *);

    int (*close_server)(WindowParam *);
    int (*close_client)(WindowParam *);
}WindowSocket;

WindowSocket new_WindowSocket();

#endif