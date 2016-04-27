#!/bin/sh

rm pipe.*
./barrier pipe 10 &
./client pipe 10 5
killall barrier