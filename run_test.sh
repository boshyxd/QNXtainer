#!/bin/sh

chmod +x ./test_container/hello.sh

./bin/qnxtainer create test_container1 ./test_container

./bin/qnxtainer start test_container1 /hello.sh

sleep 12

./bin/qnxtainer stop test_container1

./bin/qnxtainer destroy test_container1

echo "Test completed." 