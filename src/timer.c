#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <zconf.h>
#include "timer.h"

LinkedList **create_slot_list(int size) {
  LinkedList **slot_list = malloc(size * sizeof(LinkedList *));
  int index = 0;
  for (; index < size; ++index) {
    slot_list[index] = new_linked_list();
  }
  return slot_list;
}

WheelTimer* new_wheel_timer(int wheel_size, int clock_tic_interval) {
  WheelTimer *wt = malloc(sizeof(WheelTimer));
  wt->next_id = 0;
  wt->clock_tic_interval = clock_tic_interval;
  wt->wheel_size = wheel_size;
  wt->current_cycle_no = 0;
  memset(&(wt->wheel_thread), 0, sizeof(WheelTimer));
  wt->slots = create_slot_list(wheel_size);
  return wt;
}

WheelTimerElem *new_wheel_timer_elem(
  unsigned int id,
  int time_interval,
  app_call_back app_callback,
  void *arg,
  int arg_size,
  bool is_recurrence
) {
  WheelTimerElem *result = malloc(sizeof(WheelTimerElem));
  result->id = id;
  result->time_interval = time_interval;
  result->app_callback = app_callback;
  result->arg = calloc(1, arg_size);
  memcpy(result->arg, arg, arg_size);
  result->arg_size = arg_size;
  result->is_recurrence = is_recurrence;
  result->execute_cycle_no = UNDEFINED_EXECUTE_CYCLE_NO;
  return result;
}

WheelTimerElem *new_wheel_timer_elem_by_ref(WheelTimerElem *ref) {
  WheelTimerElem *result = malloc(sizeof(WheelTimerElem));
  result->id = ref->id;
  result->time_interval = ref->time_interval;
  result->execute_cycle_no = ref->execute_cycle_no;
  result->app_callback = ref->app_callback;
  result->arg = ref->arg;
  memcpy(result->arg, ref->arg, ref->arg_size);
  result->arg_size = ref->arg_size;
  result->is_recurrence = ref->is_recurrence;
  return result;
}

void add_slot_item(LinkedList *slots, WheelTimerElem *wt_elem) {
  if (slots->head == NULL) {
    push_first(slots, wt_elem);
    return;
  }
  int index = 0;
  Node *current = slots->head;
  while (current != NULL) {
    WheelTimerElem *current_item = current->item;
    if (wt_elem->execute_cycle_no > current_item->execute_cycle_no) {
      break;
    }
    current = current->next;
    index += 1;
  }
  add_by_index(slots, wt_elem, index);
}

void remove_slot_item(LinkedList *slots, WheelTimerElem *wt_elem) {
  int index = 0;
  Node *current = slots->head;
  while (current != NULL) {
    WheelTimerElem *current_item = current->item;
    if (wt_elem->id == current_item->id) {
      pop_by_index(slots, index);
      break;
    }
    if (wt_elem->execute_cycle_no > current_item->execute_cycle_no) {
      printf("cannot find slot item.\n");
      break;
    }
    current = current->next;
    index += 1;
  }
}

void update_slot_list(LinkedList **slot_list, WheelTimerElem *wt_elem, int wheel_size, int current_tic) {
  WheelTimerElem *target = wt_elem;
  LinkedList *current_tic_slots = slot_list[current_tic];
  if (wt_elem->execute_cycle_no != UNDEFINED_EXECUTE_CYCLE_NO) {
    target = new_wheel_timer_elem_by_ref(wt_elem);
    remove_slot_item(current_tic_slots, wt_elem);
  }

  bool is_next_cycle = (current_tic + target->time_interval) / wheel_size;
  if (is_next_cycle) {
    target->execute_cycle_no += 1;
  }

  int next_tic = (current_tic + target->time_interval) % wheel_size;
  LinkedList *next_tic_slots = slot_list[next_tic];
  add_slot_item(next_tic_slots, target);
}

bool is_time_to_fire_event(WheelTimer *wt, WheelTimerElem *wt_elem) {
  if (wt_elem->execute_cycle_no < wt->current_cycle_no) {
    return false;
  }
  return true;
}

void fire_events(WheelTimer *wt) {
  LinkedList **slot_list = wt->slots;
  LinkedList *current_tic_slots = slot_list[wt->current_clock_tic];
  if (current_tic_slots->head == NULL) {
    return;
  }
  WheelTimerElem *current = (WheelTimerElem *) pop_first(current_tic_slots);
  while (current != NULL) {
    if (!is_time_to_fire_event(wt, current)) {
      return;
    }
    (current->app_callback)(current->arg, current->arg_size);
    if (current->is_recurrence) {
      update_slot_list(slot_list, current, wt->wheel_size, wt->current_clock_tic);
    }
    current = (WheelTimerElem *) pop_first(current_tic_slots);
  }
}

_Noreturn void *wheel_fn(void *arg) {
  WheelTimer *wt = (WheelTimer *)arg;
  while (true) {
    sleep(wt->clock_tic_interval);

    fire_events(wt);

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
  bool is_recurrence
) {
  wt->next_id += 1;
  WheelTimerElem *wt_elem = new_wheel_timer_elem(
    wt->next_id,
    time_interval,
    callback,
    arg,
    arg_size,
    is_recurrence
  );

  update_slot_list(wt->slots, wt_elem, wt->wheel_size, wt->current_clock_tic);

  return wt_elem;
}
