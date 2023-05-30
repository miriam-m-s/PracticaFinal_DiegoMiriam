
#include "SpaceServer.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>



int main(int argc, char **argv)
{

    SpaceServer es(argv[1], argv[2]);

    es.do_messages();

    return 0;
}