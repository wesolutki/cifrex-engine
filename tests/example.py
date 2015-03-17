#!/bin/python
import libpycifrex

v1 = libpycifrex.Vex("(?P<v1>.*strcpy.*)")
vs = [v1]
e=libpycifrex.Engine(vs)
print(e.search("../repos/",[".h",".c"]))
