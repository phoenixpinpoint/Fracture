/**
 * @file pmprocess.h
 * @author Adam Guthrie
 * @brief 
 * 
 *  PMProcess stores basic data about a process.
 * 
 * @version 0.1
 * @date 2022-12-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef PMPROCESS_H
#define PMPROCESS_H

typedef enum {
    ERROR = -1,
    NEW = 0,
    ACTIVE = 1,
    EXITED = 2
} PMProcessStatus;

typedef struct PMProcess {
    void* pid;
    char* name;
    PMProcessStatus status;
    struct PMProcess* next;
} PMProcess;

#endif
