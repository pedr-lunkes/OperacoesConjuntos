#!/bin/bash
A=$@

if [ ! -d "casos_teste" ]; then
    mkdir casos_teste
fi

if [ ! -f "c" ]; then
    gcc geraCaso.c -o c
fi

./c $A


if [ ! -d "resultados" ]; then
    mkdir resultados
fi

if [ ! -d "main" ]; then
    cd ..
    make clean
    make
    cd CASOS_TESTE
fi


for (( i = 1; i <= $A; i ++ )); do
    touch resultados/$i.out
    echo $i
    ./../main < casos_teste/$i.in > resultados/$i.out
done
