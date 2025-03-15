#ifndef FS_ISOLATION_H
#define FS_ISOLATION_H

#include <sys/types.h>

int setup_root_directory(const char *root_path);
int enter_root_directory(const char *root_path);
int setup_mount_namespace(pid_t pid);

#endif 