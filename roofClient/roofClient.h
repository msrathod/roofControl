/*
 *
 *  roofClient.h: Write cmd to roof server shared memory
 *                 
 */
#ifndef ROOF_CLIENT_H
#define ROOF_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <roofCommon.h>

struct shared_memory *shm_ptr;
sem_t *mutex_sem, *cmd_count_sem, *spool_signal_sem;
int fd_shm;

void error (char *msg);
void client_setup();
void client_push_cmd(unsigned char ucmd);


#ifdef __cplusplus
}
#endif
#endif // ROOF_CLIENT_H
