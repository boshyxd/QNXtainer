# QNXtainer

A lightweight container management system for QNX that implements basic containerization concepts using POSIX-compliant interfaces.

## Overview

QNXtainer provides container creation, process isolation, and resource management for containerized applications on QNX systems. It's designed to work on QNX-powered devices including Raspberry Pi.

## Features

- Container lifecycle management (create, start, stop, destroy)
- Process isolation
- Resource constraints (memory limits, CPU shares)
- Filesystem isolation
- Simple command-line interface

## Building

### Prerequisites

- QNX Software Development Platform (SDP) 7.0 or later
- QNX Momentics IDE or QNX VSCode extension

### Build Commands

For x86_64 architecture:
```
make BUILD_PROFILE=debug PLATFORM=x86_64 all
```

For ARM architecture (e.g., Raspberry Pi):
```
make BUILD_PROFILE=debug PLATFORM=armv7le all
```

## Deployment to QNX Raspberry Pi

### Manual Deployment

1. Copy the binary to your QNX device:
   ```
   scp bin/armv7le-debug/qnxtainer qnx@<qnx-ip>:/path/on/qnx/bin/
   ```

2. Copy the test files:
   ```
   scp -r test_container qnx@<qnx-ip>:/path/on/qnx/
   scp run_test.sh qnx@<qnx-ip>:/path/on/qnx/
   ```

3. Set permissions:
   ```
   ssh qnx@<qnx-ip> "chmod +x /path/on/qnx/bin/qnxtainer /path/on/qnx/test_container/hello.sh /path/on/qnx/run_test.sh"
   ```

### Using the Deployment Script

We provide a deployment script to simplify the process:

```
./deploy.sh <qnx-ip> <target-directory>
```

Example:
```
./deploy.sh 192.168.1.100 /home/qnx/qnxtainer
```

## Usage

### Container Management Commands

```
./bin/qnxtainer create <container_name> <root_path>
./bin/qnxtainer start <container_name> <command>
./bin/qnxtainer stop <container_name>
./bin/qnxtainer destroy <container_name>
```

### Running the Test Script

```
cd /path/on/qnx
./run_test.sh
```

## Architecture

QNXtainer consists of the following components:

1. Container Runtime: Core functionality for container management
   - Process isolation using POSIX APIs
   - Resource constraints implementation
   - Filesystem isolation

2. CLI Interface: Command-line tools for container lifecycle management

## Limitations

- Limited network isolation compared to Linux containers
- Resource constraints depend on QNX-specific features
- Simplified filesystem isolation

## Current WIP

- Enhanced network isolation
- Volume mounting
- Container image management
- QNXtainer Studio: Qt-based management interface
- Linux Tool Port: Simplified version of a Linux container tool