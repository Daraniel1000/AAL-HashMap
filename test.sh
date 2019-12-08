#!/bin/bash
for mainval in 1000 10000 20000 30000 40000 50000 60000 70000 80000 90000
do
	./tgen $mainval;
	for val in {1..100}
	do
		./hashmap out.txt 0 out.txt;
	done;
	for val in {1..100}
	do
		./hashmap out.txt 1 out.txt;
	done;
done;
