#!/bin/bash
f="a"
while true
do
    ./make >$f.in
    ./force <$f.in >$f.ans
    ./ri <$f.in >$f.out
    if diff $f.ans $f.out
    then
        echo "AC"
    else
        echo "WA"
        exit 0
    fi
done
