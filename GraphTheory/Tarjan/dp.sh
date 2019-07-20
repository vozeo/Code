for i in `seq 1 10`
do
    ./P4171 <$i.in >P4171.out
    if diff P4171.out $i.out
    then
        echo "AC"
    else
        echo "WA"
        exit 0
    fi
done
