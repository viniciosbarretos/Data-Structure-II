#ifndef DATA_STRUCTURE_LIST_H
#define DATA_STRUCTURE_LIST_H

#include "schedule.h"

ScheduleList* newList();
ScheduleList* listInsertStart(ScheduleList *scheduleList, Schedule *schedule);
ScheduleList* listInsertEnd(ScheduleList *scheduleList, Schedule *schedule);
ScheduleList* listRemove(ScheduleList *scheduleList);
ScheduleList* listInsertSorted(ScheduleList *scheduleList, Schedule *schedule);
ScheduleList* listUpdatePriority(ScheduleList *scheduleList, unsigned int clock);
int moveBetweenLists(ScheduleList **from, ScheduleList **to, unsigned short status);
int moveElementBetweenLists(ScheduleList **from, ScheduleList **to, unsigned int id, unsigned short status);
unsigned int listCounter(ScheduleList* scheduleList);
int isEmpty(ScheduleList **scheduleList);


#endif //DATA_STRUCTURE_LIST_H
