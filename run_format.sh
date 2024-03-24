#!/bin/bash
find . -name BUILD -exec buildifier {} +
find . -regex ".*\.[hc]*" -exec clang-format -i {} +
