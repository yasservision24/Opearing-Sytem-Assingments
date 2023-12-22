#!/bin/bash

mkdir -p Result

while IFS=" " read -r a b operation; do
	if [ "$operation" = "xor" ];  then
		echo "$((a^b))" >> Result/output.txt
	elif [ "$operation" = "product" ]; then
		echo "$((a*b))" >> Result/output.txt
	elif [ "$operation" = "compare" ]; then
		if [ "$b" -gt "$a" ]; then
			echo "$b" >> Result/output.txt
		else
			echo "$a" >> Result/output.txt
		fi
	else
		echo  "Invalid Operation: $operation"
	fi
done < input.txt
