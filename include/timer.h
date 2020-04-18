#ifndef TIMER_H
#define TIMER_H

#include <pthread.h>
#include <stdbool.h>
#include "linkedlist.h"

typedef void (*app_call_back)(void *arg, int sizeof_arg);

typedef struct WheelTimerElem_t {
  unsigned int id;
  int time_interval;
  int execute_cycle_no;
  app_call_back app_callback;
  void *arg;
  int arg_size;
  bool is_recurrence;
} WheelTimerElem;

#define UNDEFINED_EXECUTE_CYCLE_NO -1

typedef struct WheelTimer_t {
  unsigned int next_id;
  int current_clock_tic;
  int clock_tic_interval;
  int wheel_size;
  int current_cycle_no;
  pthread_t *wheel_thread;
  LinkedList **slots; // dynamically allocated by wheel_size
} WheelTimer;

WheelTimer* new_wheel_timer(int wheel_size, int clock_tic_interval);

/* Gives thea absolute slot no since the time WT has started */
#define GET_WT_CURRENT_ABS_SLOT_NO(wt) ((wt->current_cycle_no * wt_wheel_size) + wt->current_clock_tic)

void fire_events(WheelTimer *wt);

void start_wheel_timer(WheelTimer *wt);

WheelTimerElem* register_app_event(WheelTimer *wt, app_call_back callback, void *arg, int arg_size, int time_interval, bool is_recurrence);

void deregister_app_event(WheelTimer *wt, WheelTimerElem *wt_elem);

void wt_elem_reschedule(WheelTimerElem *wt_elem, int new_time_interval);

#endif /* TIMER_H */