#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: ./deploy.sh <qnx_ip_address> <target_directory>"
    echo "Example: ./deploy.sh 192.168.1.100 /home/qnx/qnxtainer"
    exit 1
fi

QNX_IP=$1
TARGET_DIR=$2

ssh qnx@$QNX_IP "mkdir -p $TARGET_DIR/bin $TARGET_DIR/test_container"

scp bin/x86_64-debug/qnxtainer qnx@$QNX_IP:$TARGET_DIR/bin/

scp test_container/hello.sh qnx@$QNX_IP:$TARGET_DIR/test_container/

scp run_test.sh qnx@$QNX_IP:$TARGET_DIR/

ssh qnx@$QNX_IP "chmod +x $TARGET_DIR/bin/qnxtainer $TARGET_DIR/test_container/hello.sh $TARGET_DIR/run_test.sh"

echo "Deployment completed. You can now run the test on your QNX device with:"
echo "ssh qnx@$QNX_IP \"cd $TARGET_DIR && ./run_test.sh\"" 