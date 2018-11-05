#ifndef SCHEDULE_H
#define SCHEDULE_H

typedef struct
{
    char* name;
    void* initialize;
    void* insert_OK;
    void* reorganize;
    void* scheduling;
    void* job_exit;
    void* algorithm_exit;
}SCHEDULING_ALGORITHM;


#endif