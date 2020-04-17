#include <stdio.h>
#include <string.h>
#include "timer.h"

#define WHEEL_SIZE 10
#define WHEEL_TIMER_CLOCK_TIC_INTERVAL 1

void wrapper_print_hello(void *arg, int arg_size) {
  char *S = (char *) arg;
  printf("%s\n", S);
}

int main(int argc, char **argv) {
  WheelTimer *wt = new_wheel_timer(WHEEL_SIZE, WHEEL_TIMER_CLOCK_TIC_INTERVAL);
  start_wheel_timer(wt);
  WheelTimerElem *wt_elem = register_app_event(
    wt,
    wrapper_print_hello,
    "Hello Timer",
    strlen("Hello Timer"),
    5,
    1
  );
  scanf("\n");
  return 0;
}