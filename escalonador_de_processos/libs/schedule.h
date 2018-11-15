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
ScheduleList* newScheduleList();
ScheduleList* scheduleListInsertStart(ScheduleList *scheduleList, Schedule *schedule);
ScheduleList* scheduleListInsertEnd(ScheduleList *scheduleList, Schedule *schedule);
ScheduleList* listRemove(ScheduleList *scheduleList);
ScheduleList* scheduleListInsertSorted(ScheduleList *scheduleList, Schedule *schedule);
ScheduleList* scheduleListUpdatePriority(ScheduleList *scheduleList, unsigned int clock);
Schedule *detachScheduleElement(ScheduleList **scheduleList, unsigned int targetId);
int moveBetweenSchedules(ScheduleList **from, ScheduleList **to, unsigned short status);
int moveElementBetweenSchedules(ScheduleList **from, ScheduleList **to, unsigned int id, unsigned short status);
unsigned int scheduleListCounter(ScheduleList *scheduleList);
int isEmpty(ScheduleList **scheduleList);

#endif //DATA_STRUCTURE_SCHEDULE_H
