#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
    int t = uptime();
    printf("uptime: %d ticks\n", t);
    exit(0);
}
