@ECHO off
SET PATH=tool\w64devkit\bin;%PATH%
START make.exe -f Makefile.win
