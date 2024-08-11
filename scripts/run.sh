#!/bin/sh
export LD_LIBRARY_PATH=bld/bin/sdl3:bld/bin/engine:bld/bin/game:$LD_LIBRARY_PATH
$1
