#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd $DIR

APP_NAME="MuExpDriver"

if [ "$1" = "clean" ]; then
   rm -rf *.o *.a $APPNAME $APPNAME.prc *.bin
   exit
fi

declare -a FILES=("muExpDriver" "patcher" "globals" "gui" "traps" "config" "debug")
CFLAGS="-palmos4 -O3"

if [ "$1" = "debug" ]; then
   CFLAGS="$CFLAGS -DDEBUG -g"
fi

for I in "${FILES[@]}"; do
   m68k-palmos-gcc $CFLAGS -c $I.c -o $I.o
done
m68k-palmos-gcc -o $APP_NAME *.o

# if possible generate icon trees
if type "MakePalmBitmap" &> /dev/null; then
   MakePalmBitmap icon ./appIcon.svg ./
fi

pilrc $APP_NAME.rcp
build-prc $APP_NAME.def $APP_NAME *.bin
