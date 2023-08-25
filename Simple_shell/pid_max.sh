#!/bin/bash
pid_max=$(cat /proc/sys/kernel/pid_max)
echo "MAX PID VALUE: $pid_max"
