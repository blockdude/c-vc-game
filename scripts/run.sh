#!/bin/sh
export LD_LIBRARY_PATH=bld/bin/sdl3:bld/bin/engine:$LD_LIBRARY_PATH
$1
