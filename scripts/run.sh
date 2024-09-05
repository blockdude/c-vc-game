#!/bin/sh
export LD_LIBRARY_PATH=bld/bin/sdl3:bld/bin/lib:bld/bin/game:$LD_LIBRARY_PATH
mangohud --dlsym $1
