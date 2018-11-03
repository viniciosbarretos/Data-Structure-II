//
// Created by vino on 11/2/2018.
//
#include <stdlib.h>
#include "memory.h"
#ifndef DATA_STRUCTURE_SCHEDULE_H
#define DATA_STRUCTURE_SCHEDULE_H

typedef struct Schedule {
    struct Memory *memory;
    struct Schedule *next, *prev;
} Schedule;

typedef struct ScheduleList {
    struct Schedule *start;
    struct Schedule *end;
} ScheduleList;

#endif //DATA_STRUCTURE_SCHEDULE_H
