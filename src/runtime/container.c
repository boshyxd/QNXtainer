#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <errno.h>
#include <signal.h>
#include "../../include/container.h"
#include "../../include/fs_isolation.h"

static container_t containers[MAX_CONTAINERS];
static int container_count = 0;

container_t *container_find(const char *name) {
    for (int i = 0; i < container_count; i++) {
        if (strcmp(containers[i].name, name) == 0) {
            return &containers[i];
        }
    }
    return NULL;
}

int container_create(const char *name, const char *root_path) {
    if (container_count >= MAX_CONTAINERS) {l
        return -1;
    }
    
    if (container_find(name) != NULL) {
        return -1;
    }
    
    if (setup_root_directory(root_path) != 0) {
        return -1;
    }
    
    container_t *container = &containers[container_count++];
    strncpy(container->name, name, MAX_NAME_LEN - 1);
    container->name[MAX_NAME_LEN - 1] = '\0';
    
    strncpy(container->root_path, root_path, MAX_PATH_LEN - 1);
    container->root_path[MAX_PATH_LEN - 1] = '\0';
    
    container->state = CONTAINER_CREATED;
    container->pid = -1;
    container->mem_limit = 0;
    container->cpu_shares = 0;
    
    return 0;
}

int container_start(const char *name, char *const argv[]) {
    container_t *container = container_find(name);
    if (container == NULL || container->state != CONTAINER_CREATED) {
        return -1;
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        return -1;
    }
    
    if (pid == 0) {
        if (container->mem_limit > 0) {
            struct rlimit rlim;
            rlim.rlim_cur = rlim.rlim_max = container->mem_limit;
            setrlimit(RLIMIT_AS, &rlim);
        }
        
        if (enter_root_directory(container->root_path) != 0) {
            exit(EXIT_FAILURE);
        }        
        execvp(argv[0], argv);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    
    container->pid = pid;
    container->state = CONTAINER_RUNNING;
    
    setup_mount_namespace(pid);
    
    return 0;
}

int container_stop(const char *name) {
    container_t *container = container_find(name);
    if (container == NULL || container->state != CONTAINER_RUNNING) {
        return -1;
    }
    
    if (kill(container->pid, SIGTERM) == -1) {
        return -1;
    }
    
    int status;
    waitpid(container->pid, &status, 0);
    
    container->state = CONTAINER_STOPPED;
    return 0;
}

int container_destroy(const char *name) {
    container_t *container = container_find(name);
    if (container == NULL || container->state == CONTAINER_RUNNING) {
        return -1;
    }
    
    container->state = CONTAINER_DESTROYED;
    return 0;
}

int container_set_resources(const char *name, unsigned long mem_limit, unsigned int cpu_shares) {
    container_t *container = container_find(name);
    if (container == NULL) {
        return -1;
    }
    
    container->mem_limit = mem_limit;
    container->cpu_shares = cpu_shares;
    
    if (container->state == CONTAINER_RUNNING && mem_limit > 0) {
        struct rlimit rlim;
        rlim.rlim_cur = rlim.rlim_max = mem_limit;
        
        if (prlimit(container->pid, RLIMIT_AS, &rlim, NULL) == -1) {
            return -1;
        }
    }
    
    return 0;
} 