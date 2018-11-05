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

Schedule *newSchedule(Memory *mem);
ScheduleList* newList();
ScheduleList* listInsertStart(ScheduleList *scheduleList, Schedule *schedule);
ScheduleList* listInsertEnd(ScheduleList *scheduleList, Schedule *schedule);
ScheduleList* listRemove(ScheduleList *scheduleList);
ScheduleList* listInsertSorted(ScheduleList *scheduleList, Schedule *schedule);
ScheduleList* listUpdatePriority(ScheduleList *scheduleList, unsigned int clock);
Schedule *detachElement(ScheduleList **scheduleList, unsigned int targetId);
int moveBetweenLists(ScheduleList **from, ScheduleList **to, unsigned short status);
int moveElementBetweenLists(ScheduleList **from, ScheduleList **to, unsigned int id, unsigned short status);
unsigned int listCounter(ScheduleList* scheduleList);
int isEmpty(ScheduleList **scheduleList);

#endif //DATA_STRUCTURE_SCHEDULE_H
