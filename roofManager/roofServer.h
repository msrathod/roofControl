/*
 *
 *  roofServer.h: Gets cmd from clients in roof server shared memory
 *                 
 */
#ifndef ROOF_SERVER_H
#define ROOF_SERVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <roofCommon.h>

struct shared_memory *shm_ptr;
sem_t *mutex_sem, *cmd_count_sem, *spool_signal_sem;
int fd_shm, fd_log;
unsigned char mycmd;

void error (char *msg);
void server_setup();
void server_run(unsigned char *pcmd);


#ifdef __cplusplus
}
#endif
#endif // ROOF_SERVER_H
