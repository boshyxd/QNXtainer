# QNXtainer Deployment Instructions

This document provides instructions for deploying and running QNXtainer on a QNX Raspberry Pi.

## Prerequisites

- QNX Raspberry Pi with QNX 7.0 or later
- Network connection to transfer files to the Raspberry Pi
- SSH access to the Raspberry Pi (or serial console)

## Deployment Steps

1. **Transfer the files to the QNX Raspberry Pi**

   Use SCP or another file transfer method to copy the following files to your QNX Raspberry Pi:
   
   ```
   bin/x86_64-debug/qnxtainer  -> /path/on/qnx/bin/qnxtainer
   test_container/             -> /path/on/qnx/test_container/
   run_test.sh                 -> /path/on/qnx/run_test.sh
   ```

2. **Set file permissions**

   On the QNX Raspberry Pi, run:
   
   ```bash
   chmod +x /path/on/qnx/bin/qnxtainer
   chmod +x /path/on/qnx/test_container/hello.sh
   chmod +x /path/on/qnx/run_test.sh
   ```

3. **Run the test script**

   ```bash
   cd /path/on/qnx
   ./run_test.sh
   ```

## Manual Testing

If you prefer to test the container manually, you can use the following commands:

```bash
# Create a container
./bin/qnxtainer create test_container1 ./test_container

# Start the container with a command
./bin/qnxtainer start test_container1 /hello.sh

# Stop the container
./bin/qnxtainer stop test_container1

# Destroy the container
./bin/qnxtainer destroy test_container1
```

## Troubleshooting

- If you encounter permission issues, ensure all scripts and binaries have executable permissions.
- If the container fails to start, check that the paths in the run_test.sh script match your actual file locations.
- For filesystem isolation issues, ensure your QNX version supports the necessary filesystem operations.

## Notes on Cross-Architecture Deployment

If you're building for a different architecture (e.g., ARM for Raspberry Pi), make sure to:

1. Build with the correct platform target:
   ```
   make BUILD_PROFILE=debug PLATFORM=armv7le all
   ```

2. Transfer the correct binary:
   ```
   bin/armv7le-debug/qnxtainer -> /path/on/qnx/bin/qnxtainer
   ``` 