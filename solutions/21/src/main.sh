#!/bin/bash

prefix="new_"
suffix=".txt"
directory="../tests"

for file in "$directory"/*"$suffix"; do
  if [[ -f "$file" ]]; then
    mv "$file" "$directory/${prefix}$(basename "$file")"
  fi
done
