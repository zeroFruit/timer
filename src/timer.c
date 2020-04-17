#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <zconf.h>
#include "timer.h"

WheelTimer* new_wheel_timer(int wheel_size, int clock_tic_interval) {
  // get the memory for wheel timer, note that wheel_size, number of slots
  // are dynamically allotted. Each slot carries pointed to linked list
  WheelTimer *wt = calloc(1, sizeof(WheelTimer) + wheel_size * sizeof(LinkedList *));
  wt->clock_tic_interval = clock_tic_interval;
  wt->wheel_size = wheel_size;
  wt->current_cycle_no = 0;
  memset(&(wt->wheel_thread), 0, sizeof(WheelTimer));

  int i = 0;
  for (; i < wheel_size; ++i) {
    wt->ll = new_linked_list();
  }
  return wt;
}

_Noreturn void *wheel_fn(void *arg) {
  WheelTimer *wt = (WheelTimer *)arg;
  while (1) {
    sleep(wt->clock_tic_interval);
    LinkedList *slot_list = wt->ll; // get the linked list of events in the slot

    // TODO: traverse over slot list, and fire up events which match the firing criteria
    // re-position the events if they need to be fired again periodically. This included
    // calculate the new slot of the events

    wt->current_clock_tic += 1;
    if (wt->current_clock_tic == wt->wheel_size) {
      wt->current_clock_tic = 0;
      wt->current_cycle_no += 1;
    }
  }
}

void start_wheel_timer(WheelTimer *wt) {
  pthread_t *thread = wt->wheel_thread;
  if (pthread_create(thread, NULL, wheel_fn, (void *) wt)) {
    perror("wheel timer thread starting failed, exiting...\n");
  }
}

WheelTimerElem* register_app_event(
  WheelTimer *wt,
  app_call_back callback,
  void *arg,
  int arg_size,
  int time_interval,
  char is_recursive
) {
  // create a wheel timer element data structure to store the event
  WheelTimerElem *wt_elem = calloc(1, sizeof(WheelTimerElem));
  wt_elem->time_interval = time_interval;
  wt_elem->app_callback = callback;
  wt_elem->arg = calloc(1, arg_size);
  memcpy(wt_elem->arg, arg, arg_size);
  wt_elem->arg_size = arg_size;
  wt_elem->is_recurrence = is_recursive;

  // TODO: find the slot where the wt_elem needs to be placed.
  // insert the wt_elem in the slot's linked list
  // Calculate r and slot number

  return wt_elem;
}
