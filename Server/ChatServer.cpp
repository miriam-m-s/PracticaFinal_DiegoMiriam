#include "Chat.h"


int l(int argc, char **argv)
{
    ChatServer es(argv[1], argv[2]);

    es.do_messages();

    return 0;
}
