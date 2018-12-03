#!/bin/bash

if [ "$1" = "--extra" ]
then
    ./generate/generator.sh
fi

make tsp
make best

for f in in/*.in ; do
    filename=$(basename -- "$f")
    fn="${filename%.*}"
    ./tsp "$f" > "out/${fn}.out"
    ./tsp_best "$f" > "out/${fn}.best.out"
    perf=$(cat "ref/${fn}.ref")
    greedy=$(cat "out/${fn}.out")
    cristi=$(cat "out/${fn}.best.out")
    gperc=`echo "$greedy * 100 / $perf - 100" | bc`
    cperc=`echo "$cristi * 100 / $perf - 100" | bc`
    echo "Greedy found a path $gperc% longer"
    echo "Christofides algorithm found a path $cperc% longer"
done

make clean
if [ "$1" = "--extra" ]
then
    rm -f in/test9.in
    rm -f in/test10.in
fi