#ifndef DATA_STRUCTURE_RENDER_H
#define DATA_STRUCTURE_RENDER_H

#include "pcb.h"
#include "schedule.h"
#include "memory.h"
#include "list.h"

char* getStatus(int status, int id);
void renderElement(Schedule *schedule);
void renderScheduleList(ScheduleList *list);
void renderScreen(ScheduleList* jobs, ScheduleList* ready, ScheduleList* blocked, ScheduleList* finished, ScheduleList* cpu, unsigned int clock,
                  unsigned int time, char* action);

#endif //DATA_STRUCTURE_RENDER_H
