#!/bin/bash
total_count=0

funcH()
{
    local dir="$1"
    count=0
    for file in "$dir"/*.h; do
        l_count=$(wc -l < "$file")
        ((count += l_count))
    done
    echo "$count"
}

funcCPP()
{
    local dir="$1"
    count=0
    for file in "$dir"/*.cpp; do
        l_count=$(wc -l < "$file")
        ((count += l_count))
    done
    echo "$count"
}

if ls "$1"/*.cpp 1> /dev/null 2>&1; then
    count=$(funcCPP "$1")
    ((total_count += count))
fi
if ls "$1"/*.h 1> /dev/null 2>&1; then
    count=$(funcH "$1")
    ((total_count += count))
fi

for dir in "$1"/*/; do
    if ls "$1"/*.cpp 1> /dev/null 2>&1; then
        count=$(funcCPP "$1")
        ((total_count += count))
    fi
    if ls "$1"/*.h 1> /dev/null 2>&1; then
        count=$(funcH "$1")
        ((total_count += count))
    fi
done

echo "$total_count"
