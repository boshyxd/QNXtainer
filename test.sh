#!/bin/bash

make clean
make

mkdir -p test_container

cat > test_container/hello.sh << 'EOF'
echo "Hello from QNXtainer container!"
sleep 10
EOF

chmod +x test_container/hello.sh

./bin/qnxtainer create test_container1 ./test_container
./bin/qnxtainer start test_container1 /hello.sh

sleep 2

./bin/qnxtainer stop test_container1

./bin/qnxtainer destroy test_container1

echo "Test completed." 