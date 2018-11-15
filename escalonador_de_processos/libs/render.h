#ifndef DATA_STRUCTURE_RENDER_H
#define DATA_STRUCTURE_RENDER_H

#include "pcb.h"
#include "schedule.h"
#include "memory.h"
#include "storage.h"

char* getStatus(int status, int id);
void renderElement(Schedule *schedule);
void renderScheduleList(ScheduleList *list);
void renderScreen(MemoryList *memoryList, StorageList* jobs, ScheduleList* ready, ScheduleList* blocked, StorageList* finished, ScheduleList* cpu, unsigned int clock,
                  unsigned int time, char* action);
void renderMemoryList(MemoryList *list);

#endif //DATA_STRUCTURE_RENDER_H
