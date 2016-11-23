#include <stdio.h>
#include "ev_loop.h"
#include "ev_type.h"
#include <time.h>
#include <stdlib.h>

ev_loop_t * loop = NULL;

void *cb_stdin1(ev_loop_t *loop, int fd, EV_TYPE events);
void *cb_timer1(ev_loop_t *loop, struct ev_timer *timer);

clock_t b;

#define NUM 5000000
int main() 
{
    loop = ev_create_loop();

    ev_io_init(loop, 100, 1);
    ev_io_register(loop, 0, EV_READ, cb_stdin1, NULL);
    
    ev_timer_init(loop, 10);
    int i;
    b = clock();
    for (i=0; i<NUM; i++)
        ev_timer_register(loop, 0.00000001*(rand()%NUM), cb_timer1, 0, NULL);
    
    printf("%f\n", 1.0 * (clock() - b)/CLOCKS_PER_SEC);
    sleep(10);
    printf("begin...\n");
    ev_run_loop(loop);
    return 0;
}

void *cb_stdin1(ev_loop_t *loop, int fd, EV_TYPE events) {
    printf("You have data to read\n");
    return NULL;
}
void *cb_timer1(ev_loop_t *loop, struct ev_timer *timer) {
    static int cnt = 0;
    cnt ++;
    if (cnt == 1) {
        b = clock();
    }
    if (cnt == NUM) {
        printf("%f\n", 1.0*(clock() - b)/CLOCKS_PER_SEC);
    }
    return NULL;
}
