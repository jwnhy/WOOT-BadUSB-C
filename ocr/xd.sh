#! /bin/bash
function qwq() {
    mkdir $1
    ffmpeg -i $1.mkv -r 5 $1/%05d.jpeg
}

qwq wyc
qwq gh
qwq wcx
qwq hjy
qwq lsq


