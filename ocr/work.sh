#! /bin/bash
function qwq() {
	for file in `ls $1`
	do
		if [ -f "$1/$file.txt" ]; then
			continue
		fi
		extension="${file##*.}"
		if [ ! $extension = "jpeg" ]; then
			continue
		fi
		echo $1/$file
		tesseract $1/$file stdout -l chi_sim > $1/$file.txt
	done
}

qwq wyc
qwq gh
qwq wcx
qwq hjy
qwq lsq
