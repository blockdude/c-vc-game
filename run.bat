@ECHO off
SET PATH=tool\w64devkit\bin;lib\x86_64-w64-mingw32\bin;%PATH%
CALL build.bat
CALL build\bin\main.exe > out.txt | tail -f out.txt
