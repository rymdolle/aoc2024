#!/bin/sh

input=input.txt
match=$(head -1 $input | sed -e "s/, /|/g" -e "s/^/(/" -e "s/$/)+/")
part1=0
while read -r line; do
    if echo $line | grep -x -E $match > /dev/null; then
        part1=$(($part1 + 1))
    fi
done < <(tail -n +3 $input)

echo $part1
