#!/bin/bash
for mainval in 1000 2000 3000 4000 5000 6000 7000 8000 9000
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
