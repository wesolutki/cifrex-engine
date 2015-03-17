#!/bin/sh

SVR=./server/server.py
PY=python
if hash python2 2>/dev/null; then
    PY=python2
fi
$PY $SVR
