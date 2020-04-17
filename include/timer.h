#ifndef TIMER_H
#define TIMER_H

#include <pthread.h>

typedef struct _wheel_timer_elem_t wheel_timer_elem_t;
typedef void (*app_call_back)(void *arg, int sizeof_arg);

struct _wheel_timer_elem_t {
  int time_interval;
  int execute_cycle_no;
  app_call_back app_callback;
  void *arg;
  int arg_size;
  char is_recurrence;
};

typedef struct _wheel_timer_t {
  int current_clock_tic;
  int clock_tic_interval;
  int wheel_size;
  int current_cycle_no;
  pthread_t wheel_thread;
//  ll_t *slots[0];
} wheel_timer_t;

wheel_timer_t* init_wheel_timer(int wheel_size, int clock_tic_interval);

/* Gives thea absolute slot no since the time WT has started */
#define GET_WT_CURRENT_ABS_SLOT_NO(wt) ((wt->current_cycle_no * wt_wheel_size) + wt->current_clock_tic)

wheel_timer_elem_t* register_app_event(wheel_timer_t *wt, app_call_back callback, void *arg, int arg_size, int time_interval, char is_recursive);

void deregister_app_event(wheel_timer_t *wt, wheel_timer_elem_t *wt_elem);

void wt_elem_reschedule(wheel_timer_elem_t *wt_elem, int new_time_interval);

#endif /* TIMER_H */