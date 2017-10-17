#!/bin/bash
a=2334			#整型
let "a+=1"		#a = 2335
echo "a = $a"	
echo			#还是整型

b=${a/23/BB}	#将23替换成BB

echo "b = $b"	#b=BB
declare -i b
echo "b=$b"

let "b+=1"
echo "b = $b"
echo

c=BB34
echo "c=$c"
d=${c/BB/23}

echo "d = $d"
let "d = d + 1"
echo "d = $d"
echo

e=""
echo "e=$e"
let "e += 1"
echo "e = $e"
echo

echo "f = $f"
echo

echo "f = $f"
let "f += 1"
echo "f = $f"
echo

exit 0
