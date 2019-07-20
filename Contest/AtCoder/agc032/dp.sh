#!/bin/bash
file="P2155"
for i in `seq 1 100`
#while true
do
	#./make >$file$i.in
	time ./$file <$file$i.in >$file$i.out
	#./$file-ri <$file.in >$file.ans
	if diff $file$i.out $file$i.ans
	then
		echo "AC"
	else
		echo "WA"
		exit 0
	fi
done
