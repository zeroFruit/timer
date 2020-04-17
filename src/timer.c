#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "timer.h"

wheel_timer_t* init_wheel_timer(int wheel_size, int clock_tic_interval) {
  // get the memory for wheel timer, note that wheel_size, number of slots
  // are dynamically allotted. Each slot carries pointed to linked list
//  wheel_timer_t *wt = calloc(1, sizeof(wheel_timer_t) + wheel_size * sizeof(ll_t *));
//  wt->clock_tic_interval = clock_tic_interval;
//  wt->wheel_size = wheel_size;
//  wt->current_cycle_no = 0;
//  memset(&(wt->wheel_thread), 0, sizeof(wheel_timer_t));
//
//  int i = 0;
//  for (; i < wheel_size; ++i) {
//    wt->slots[i] = init_singly_ll();
//  }
//  return wt;
  printf("wheel size: %d, clock tic interval: %d", wheel_size, clock_tic_interval);
  return NULL;
}

wheel_timer_elem_t* register_app_event(
  wheel_timer_t *wt,
  app_call_back callback,
  void *arg,
  int arg_size,
  int time_interval,
  char is_recursive
) {
  // create a wheel timer element data structure to store the event
  wheel_timer_elem_t *wt_elem = calloc(1, sizeof(wheel_timer_elem_t));
  wt_elem->time_interval = time_interval;
  wt_elem->app_callback = callback;
  wt_elem->arg = calloc(1, arg_size);
  memcpy(wt_elem->arg, arg, arg_size);
  wt_elem->arg_size = arg_size;
  wt_elem->is_recurrence = is_recursive;

  // find the slot where the wt_elem needs to be placed.
  // insert the wt_elem in the slot's linked list
  // Calculate r and slot number

  return wt_elem;
}
