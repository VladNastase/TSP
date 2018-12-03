#!/bin/bash
make;
./gen fnl4461.tsp > ../in/test9.in;
./gen d15112.tsp > ../in/test10.in;
echo "182566" > ../ref/test9.ref
echo "1573084" > ../ref/test10.ref
make clean;