#!/bin/bash
file="bread"
# for i in `seq 0 19`
while true
do
	./make >$file$i.in
	time ./C <$file$i.in >$file$i.out
	./$file-ri <$file.in >$file.ans
	if diff $file$i.out $file$i.ans
	then
		echo "AC"
	else
		echo "WA"
		# exit 0
	fi
done
