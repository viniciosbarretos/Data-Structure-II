#ifndef DATA_STRUCTURE_LIST_H
#define DATA_STRUCTURE_LIST_H

#include "schedule.h"

typedef struct Storage {
    PCB* pcb;
    struct Storage *prev, *next;
} Storage;

typedef struct StorageList {
   struct Storage *start, *end;
} StorageList;

Storage *newStorage(PCB *pcb);
StorageList* newStorageList();
StorageList* storageListInsertStart(StorageList *storageList, Storage *storage);
StorageList* storageListInsertSorted(StorageList *storageList, Storage *storage);
StorageList* storageListUpdatePriority(StorageList *storageList, unsigned int clock);
//int moveBetweenLists(ScheduleList **from, ScheduleList **to, unsigned short status);
//int moveElementBetweenLists(ScheduleList **from, ScheduleList **to, unsigned int id, unsigned short status);
//unsigned int listCounter(ScheduleList* scheduleList);
//int isEmpty(ScheduleList **scheduleList);
int moveFromScheduleToStorage(MemoryList **memory, ScheduleList **from, StorageList **to, unsigned int id, unsigned short status);
int moveFromStorageToSchedule(MemoryList **memory, StorageList **from, ScheduleList **to, unsigned int id, unsigned short status);


#endif //DATA_STRUCTURE_LIST_H
