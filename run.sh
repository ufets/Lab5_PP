#!/bin/bash
for i in {1..4}
do
	mpiexec -n $i ./project
done
