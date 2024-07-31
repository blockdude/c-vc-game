#!/bin/sh
export LD_LIBRARY_PATH=bld/bin/sdl3:bld/bin/vce:$LD_LIBRARY_PATH
$1
