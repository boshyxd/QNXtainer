# QNXtainer

A lightweight container management system for QNX that implements basic containerization concepts using POSIX-compliant interfaces.

## Overview

QNXtainer provides container creation, process isolation, resource management for containerized applications on QNX systems.

## Components

- Container Runtime: POSIX-compliant implementation for process isolation and resource control
- Container Management CLI: Command-line tools for container lifecycle management
- QNXtainer Studio: Qt-based management interface (future)
- Linux Tool Port: Simplified version of a Linux container tool (future)

## Building

```
make
```

## Usage

```
./qnxtainer create <container_name>
./qnxtainer start <container_name> <command>
./qnxtainer stop <container_name>
./qnxtainer destroy <container_name>
``` 