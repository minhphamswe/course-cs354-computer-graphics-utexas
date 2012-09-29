#!/usr/bin/env bash

if [ ! -e ./billiards ]; then
    ln -s $(dirname 0)/src/project2/billiards
fi

./billiards
