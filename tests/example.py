#!/bin/python
import libpycifrex

v1 = libpycifrex.Vex("(?P<v1>.*strcpy.*)")
vs = [v1]
e=libpycifrex.Engine(vs, "../repos/",[".h",".c"])
print(e.search())
