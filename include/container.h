#ifndef CONTAINER_H
#define CONTAINER_H

#include <sys/types.h>
#include <limits.h>
#include <signal.h>

#define MAX_CONTAINERS 64
#define MAX_NAME_LEN 64
#define MAX_PATH_LEN PATH_MAX

typedef enum {
    CONTAINER_CREATED,
    CONTAINER_RUNNING,
    CONTAINER_STOPPED,
    CONTAINER_DESTROYED
} container_state_t;

typedef struct {
    char name[MAX_NAME_LEN];
    pid_t pid;
    container_state_t state;
    char root_path[MAX_PATH_LEN];
    unsigned long mem_limit;
    unsigned int cpu_shares;
} container_t;

int container_create(const char *name, const char *root_path);
int container_start(const char *name, char *const argv[]);
int container_stop(const char *name);
int container_destroy(const char *name);
container_t *container_find(const char *name);
int container_set_resources(const char *name, unsigned long mem_limit, unsigned int cpu_shares);
int container_list(void);


#endif 