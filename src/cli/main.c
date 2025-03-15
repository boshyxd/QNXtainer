#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../include/container.h"

void print_usage() {
    printf("Usage: qnxtainer <command> [options]\n\n");
    printf("Commands:\n");
    printf("  create <name> <root_path>     Create a new container\n");
    printf("  start <name> <command>        Start a container with the specified command\n");
    printf("  stop <name>                   Stop a running container\n");
    printf("  destroy <name>                Destroy a container\n");
    printf("  set-resources <name> <mem_limit> <cpu_shares>  Set resource limits for a container\n");
}

int cmd_create(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Error: Missing container name or root path\n");
        return 1;
    }
    
    if (container_create(argv[2], argv[3]) != 0) {
        fprintf(stderr, "Error: Failed to create container\n");
        return 1;
    }
    
    printf("Container '%s' created successfully\n", argv[2]);
    return 0;
}

int cmd_start(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Error: Missing container name or command\n");
        return 1;
    }
    
    if (container_start(argv[2], &argv[3]) != 0) {
        fprintf(stderr, "Error: Failed to start container\n");
        return 1;
    }
    
    printf("Container '%s' started successfully\n", argv[2]);
    return 0;
}

int cmd_stop(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Error: Missing container name\n");
        return 1;
    }
    
    if (container_stop(argv[2]) != 0) {
        fprintf(stderr, "Error: Failed to stop container\n");
        return 1;
    }
    
    printf("Container '%s' stopped successfully\n", argv[2]);
    return 0;
}

int cmd_destroy(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Error: Missing container name\n");
        return 1;
    }
    
    if (container_destroy(argv[2]) != 0) {
        fprintf(stderr, "Error: Failed to destroy container\n");
        return 1;
    }
    
    printf("Container '%s' destroyed successfully\n", argv[2]);
    return 0;
}

int cmd_set_resources(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr, "Error: Missing container name or resource limits\n");
        return 1;
    }
    
    unsigned long mem_limit = strtoul(argv[3], NULL, 10);
    unsigned int cpu_shares = (unsigned int)strtoul(argv[4], NULL, 10);
    
    if (container_set_resources(argv[2], mem_limit, cpu_shares) != 0) {
        fprintf(stderr, "Error: Failed to set resource limits\n");
        return 1;
    }
    
    printf("Resource limits for container '%s' set successfully\n", argv[2]);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }
    
    if (strcmp(argv[1], "create") == 0) {
        return cmd_create(argc, argv);
    } else if (strcmp(argv[1], "start") == 0) {
        return cmd_start(argc, argv);
    } else if (strcmp(argv[1], "stop") == 0) {
        return cmd_stop(argc, argv);
    } else if (strcmp(argv[1], "destroy") == 0) {
        return cmd_destroy(argc, argv);
    } else if (strcmp(argv[1], "set-resources") == 0) {
        return cmd_set_resources(argc, argv);
    } else {
        fprintf(stderr, "Error: Unknown command '%s'\n", argv[1]);
        print_usage();
        return 1;
    }
    
    return 0;
} 